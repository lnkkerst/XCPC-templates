// This file was generated by [ts-rs](https://github.com/Aleph-Alpha/ts-rs). Do not edit this file manually.
import type { BookItem } from "./BookItem";
import type { SectionNumber } from "./SectionNumber";

/**
 * The representation of a "chapter", usually mapping to a single file on
 * disk however it may contain multiple sub-chapters.
 */
export type Chapter = {
  /**
   * The chapter's name.
   */
  name: string;
  /**
   * The chapter's contents.
   */
  content: string;
  /**
   * The chapter's section number, if it has one.
   */
  number: SectionNumber | null;
  /**
   * Nested items.
   */
  sub_items: Array<BookItem>;
  /**
   * The chapter's location, relative to the `SUMMARY.md` file.
   *
   * **Note**: After the index preprocessor runs, any README files will be
   * modified to be `index.md`. If you need access to the actual filename
   * on disk, use [`Chapter::source_path`] instead.
   *
   * This is `None` for a draft chapter.
   */
  path: string | null;
  /**
   * The chapter's source file, relative to the `SUMMARY.md` file.
   *
   * **Note**: Beware that README files will internally be treated as
   * `index.md` via the [`Chapter::path`] field. The `source_path` field
   * exists if you need access to the true file path.
   *
   * This is `None` for a draft chapter.
   */
  source_path: string | null;
  /**
   * An ordered list of the names of each chapter above this one in the hierarchy.
   */
  parent_names: Array<string>;
};
