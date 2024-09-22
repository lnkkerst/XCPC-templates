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

(async () => {
  loadMermaid();
})();
