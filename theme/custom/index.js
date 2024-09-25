async function loadRemoteJS(src) {
  return new Promise((resolve, reject) => {
    const script = document.createElement("script");
    script.src = src;
    script.type = "text/javascript";
    script.addEventListener("load", resolve);
    script.addEventListener("error", reject);
    document.body.appendChild(script);
  });
}

async function loadMermaid() {
  await loadRemoteJS(
    "https://fastly.jsdelivr.net/npm/mermaid@11/dist/mermaid.min.js",
  );
  mermaid.initialize({ startOnLoad: true });
}

function printBreakPageOption() {
  if (!window.location.pathname.endsWith("print.html")) {
    return;
  }

  const navRight = document.querySelector(".right-buttons");
  const checkboxClass = "close-page-break";
  const checkbox = document.createElement("label");
  checkbox.innerHTML = `
    <input type="checkbox" class="${checkboxClass}"/>关闭分页</span>
  `;
  navRight.prepend(checkbox);
  const el = checkbox.querySelector(`.${checkboxClass}`);

  function removePrintBreakPage() {
    document
      .querySelectorAll(
        'div[style="break-before: page; page-break-before: always;"]',
      )
      .forEach(el => el.remove());
  }

  let value = JSON.parse(localStorage.getItem(checkboxClass) ?? "true");
  if (value) {
    removePrintBreakPage();
  }

  el.checked = value;
  el.addEventListener("change", () => {
    value = el.checked;
    localStorage.setItem(checkboxClass, JSON.stringify(value));
    window.location.reload();
  });
}

function generateRandomString(length) {
  const chars = "abcdefghijklmnopqrstuvwxyz0123456789";
  let result = "";
  for (let i = 0; i < length; i++) {
    const randomIndex = Math.floor(Math.random() * chars.length);
    result += chars[randomIndex];
  }
  return result;
}

async function makeAnchorsUnique() {
  const elements = document.querySelectorAll("[id]");
  elements.forEach(el => {
    const links = document.querySelectorAll(`a[href='#${el.id}']`);
    if (links.length === 0) {
      return;
    }
    const prefix = generateRandomString(10);
    const newId = `${prefix}-${el.id}`;
    el.id = newId;
    links.forEach(link => {
      link.href = `#${newId}`;
    });
  });
}

function addPDFDownloadButton() {
  const navRight = document.querySelector(".right-buttons");
  const el = document.createElement("div");
  el.innerHTML = /* HTML */ `
    <a href="/output.pdf" title="Download PDF" aria-label="Download PDF">
      <i id="pdf-download-button" class="fa fa-book"></i>
    </a>
  `;
  navRight.prepend(el.querySelector("a"));
}

(async () => {
  loadMermaid();
  if (window.location.pathname.endsWith("print.html")) {
    makeAnchorsUnique();
  }
  addPDFDownloadButton();
})();
