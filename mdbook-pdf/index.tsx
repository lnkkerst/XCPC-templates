#!/usr/bin/env bun

import { join } from "node:path";
import ReactPDF, {
  Page,
  Text,
  View,
  Document,
  StyleSheet,
  Font,
} from "@react-pdf/renderer";
import getPort from "get-port";
import { PDFArray, PDFDict, PDFDocument, PDFName, PDFPageLeaf } from "pdf-lib";
import { chromium } from "playwright";
import { z } from "zod";
import type { RenderContext } from "./types/RenderContext";
import type { Book } from "./types/Book";
import type { BookItem } from "./types/BookItem";
import { merge } from "lodash-es";
import { Fragment } from "react/jsx-runtime";

type OutlineItem = {
  title: string;
  page: number;
  subItems: OutlineItem[];
};

type OutlineCategory = {
  partTitle: string | null;
  items: OutlineItem[];
  page: number | null;
};

type TocPageProps = {
  width: number;
  height: number;
  toc: OutlineCategory[];
  metadata?: {
    title?: string;
    author?: string;
  };
};

type HeaderLink = {
  name: string;
  page: number;
};

const PrintOptionsSchema = z.object({
  displayHeaderFooter: z.boolean().optional(),
  footerTemplate: z.string().optional(),
  format: z.string().optional(),
  headerTemplate: z.string().optional(),
  height: z.union([z.string(), z.number()]).optional(),
  landscape: z.boolean().optional(),
  margin: z
    .object({
      top: z.union([z.string(), z.number()]).optional(),
      right: z.union([z.string(), z.number()]).optional(),
      bottom: z.union([z.string(), z.number()]).optional(),
      left: z.union([z.string(), z.number()]).optional(),
    })
    .optional(),
  outline: z.boolean().optional(),
  pageRanges: z.string().optional(),
  path: z.string().optional(),
  preferCSSPageSize: z.boolean().optional(),
  printBackground: z.boolean().optional(),
  scale: z.number().optional(),
  tagged: z.boolean().optional(),
  width: z.union([z.string(), z.number()]).optional(),
});

const OptionsSchema = z.object({
  print: PrintOptionsSchema.optional(),
  toc: z
    .object({
      font: z.string().optional(),
      margin: PrintOptionsSchema.shape.margin,
      width: z.number().optional(),
      height: z.number().optional(),
      fontSize: z.string().optional(),
    })
    .optional(),
});

type Options = z.infer<typeof OptionsSchema>;

const defaultOptions: Options = {
  print: {
    outline: true,
    format: "A4",
    margin: {
      top: "0.5in",
      bottom: "0.5in",
      left: "0.4in",
      right: "0.4in",
    },
    scale: 0.8,
    displayHeaderFooter: true,
    headerTemplate: /* HTML */ `
      <h2
        style="text-align: center; font-size: 10px; width: 100%; position: relative"
      >
        <span class="title"></span>
      </h2>
    `,
    footerTemplate: /* HTML */ `
      <p
        style="text-align: center; font-size: 10px; width: 100%; position: relative"
      >
        <span class="pageNumber"></span>
        /
        <span class="totalPages"></span>
      </p>
    `,
  },
  toc: {
    font: "https://cdn.jsdelivr.net/npm/@openfonts/noto-sans-sc_chinese-simplified@1.44.9/files/noto-sans-sc-chinese-simplified-400.woff",
    fontSize: "8pt",
    margin: {
      top: "0.4in",
      bottom: "0.4in",
      left: "0.4in",
      right: "0.4in",
    },
  },
};

async function createFileServer(base: string) {
  const port = await getPort();
  return Bun.serve({
    fetch(req) {
      let path = new URL(req.url).pathname;
      path = join(base, path);
      if (path.endsWith("/")) {
        path += "index.html";
      }
      const file = Bun.file(path);
      return new Response(file);
    },
    error() {
      return new Response("404", { status: 404 });
    },
    port,
  });
}

function extractOutlines(book: Book, oriLinks: HeaderLink[]) {
  const links = [...oriLinks];
  function resolveItems(items: BookItem[]) {
    let partTitle: string | null = null;
    let category: OutlineCategory[] = [];
    let current: OutlineItem[] = [];
    items.forEach(item => {
      if (item === "Separator") {
        return;
      }
      if ("PartTitle" in item) {
        category.push({
          partTitle,
          items: current,
          page: current[0].page!,
        });
        current = [];
        partTitle = item.PartTitle;
      }
      if ("Chapter" in item) {
        const chapter = item.Chapter;
        if (links.length === 0) {
          throw new Error("Links and outlines not match.");
        }
        current.push({
          title: chapter.name,
          page: links.shift()!.page,
          subItems: resolveItems(chapter.sub_items)
            .map(category => category.items)
            .flat(1),
        });
      }
    });
    if (current.length !== 0) {
      category.push({ partTitle, items: current, page: current[0].page! });
    }
    return category;
  }

  const outlines = resolveItems(book.sections);
  if (links.length !== 0) {
    throw new Error("Links and outlines not match.");
  }
  return outlines;
}

export async function extractDests(pdf: PDFDocument) {
  const pages = pdf.getPages();
  const catalog = pdf.catalog;
  const dests = catalog.lookup(PDFName.of("Dests"), PDFDict);

  return dests.entries().map<HeaderLink>(([pdfName, arr]) => {
    const name = pdfName.decodeText();

    let ref = (arr as PDFArray).lookup(0, PDFDict) as PDFPageLeaf;
    const page = pages.findIndex(page => page.node === ref) + 1;

    return { name, page };
  });
}

async function generatePDF(opts?: Options["print"]) {
  const server = await createFileServer("../html");
  const url = `${server.url.toString()}print.html`;

  const browser = await chromium.launch();
  const page = await browser.newPage();
  await page.goto(url, { waitUntil: "networkidle" });
  const buffer = await page.pdf(opts);

  const headers = (
    await Promise.all(
      (await page.$$("h1>a.header")).map(header => header.getAttribute("href")),
    )
  ).filter(i => !!i) as string[];

  await browser.close();
  server.stop();

  const file = new Uint8Array(buffer);
  const doc = await PDFDocument.load(file);

  const indexInHeaders = (i: string) =>
    headers.findIndex(header => header.startsWith(`#${i.split("-")[0]}`));

  const links = (await extractDests(doc))
    .filter(i => indexInHeaders(i.name) !== -1)
    .sort((a, b) => indexInHeaders(a.name) - indexInHeaders(b.name));

  await Bun.write("output.pdf", new Uint8Array(buffer));

  return { buffer, links, doc };
}

async function generateToc(outlines: OutlineCategory[], opts: Options["toc"]) {
  Font.register({
    family: "default",
    src: opts!.font!,
  });

  const styles = StyleSheet.create({
    page: {
      flexDirection: "column",
      gap: "4px",
      fontFamily: "default",
      fontSize: opts?.fontSize,
      paddingTop: opts?.margin?.top,
      paddingBottom: opts?.margin?.bottom,
      paddingLeft: opts?.margin?.left,
      paddingRight: opts?.margin?.right,
    },
    section: {
      flexDirection: "row",
      alignItems: "center",
    },
    text: {
      textAlign: "center",
    },
    line: {
      flex: 1,
      borderTop: "1px dashed black",
      margin: "0 10px",
    },
  });

  function TocItem({
    title,
    page,
    paddingLeft,
  }: {
    title: string | null;
    page: number | null;
    paddingLeft?: string | number;
  }) {
    return (
      <View style={{ ...styles.section, paddingLeft }}>
        <Text style={styles.text}>{title}</Text>
        <View style={styles.line}></View>
        <Text style={styles.text}>{page}</Text>
      </View>
    );
  }

  function RecursiveTocItems({
    items,
    paddingLeft,
    showPaddingLeft,
  }: {
    items: OutlineItem[];
    paddingLeft?: number | string;
    showPaddingLeft?: boolean;
  }) {
    return (
      <View style={{ paddingLeft: showPaddingLeft ? paddingLeft : undefined }}>
        {items.map(item => (
          <Fragment key={item.title}>
            <TocItem title={item.title} page={item.page}></TocItem>
            {item.subItems.length !== 0 && (
              <RecursiveTocItems
                items={item.subItems}
                paddingLeft={paddingLeft}
                showPaddingLeft
              ></RecursiveTocItems>
            )}
          </Fragment>
        ))}
      </View>
    );
  }

  function TocPage({ width, height, toc, metadata }: TocPageProps) {
    return (
      <Document title={metadata?.title} author={metadata?.author}>
        <Page
          size={{
            width,
            height,
          }}
          style={styles.page}
        >
          {toc.map(category => (
            <Fragment key={JSON.stringify(category.partTitle)}>
              {category.partTitle && (
                <TocItem
                  title={category.partTitle}
                  page={category.items[0].page}
                ></TocItem>
              )}
              <RecursiveTocItems
                items={category.items}
                paddingLeft={"12pt"}
                showPaddingLeft={!!category.partTitle}
              ></RecursiveTocItems>
            </Fragment>
          ))}
        </Page>
      </Document>
    );
  }

  await ReactPDF.renderToFile(
    <TocPage
      width={opts!.width!}
      height={opts!.height!}
      toc={outlines}
    ></TocPage>,
    "toc.pdf",
  );
}

async function mergePDF(...pdfs: string[]) {
  const [main, ...rest] = pdfs;
  const doc = await PDFDocument.load(await Bun.file(main).arrayBuffer());
  for (const pdf of rest) {
    const cur = await PDFDocument.load(await Bun.file(pdf).arrayBuffer());
    const pages = await doc.copyPages(cur, cur.getPageIndices());
    for (const page of pages) {
      doc.addPage(page);
    }
  }
  return doc.save();
}

async function main() {
  const ctx = JSON.parse(await Bun.stdin.text()) as RenderContext;
  const opts = merge(
    {},
    defaultOptions,
    OptionsSchema.parse((ctx.config as any)?.output?.["pdf"]),
  );
  opts.toc = merge({}, { margin: opts.toc?.margin }, opts.toc);

  const { links, doc } = await generatePDF(opts.print);
  const outlines = extractOutlines(ctx.book, links);

  const { width, height } = doc.getPage(1).getSize();
  opts.toc = merge({}, { width, height }, opts.toc);
  await generateToc(outlines, opts.toc);

  const final = await mergePDF("toc.pdf", "output.pdf");

  await Bun.write("output-toc.pdf", final);
}

main();
