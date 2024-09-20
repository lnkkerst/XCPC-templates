async function loadMermaid() {
  return new Promise((resolve, reject) => {
    const script = document.createElement("script");
    script.src =
      "https://fastly.jsdelivr.net/npm/mermaid@11/dist/mermaid.min.js";
    script.type = "text/javascript";
    script.addEventListener("load", () => {
      mermaid.initialize({ startOnLoad: true });
      resolve();
    });
    script.addEventListener("error", reject);
    document.body.appendChild(script);
  });
}

(async () => {
  loadMermaid();
})();
