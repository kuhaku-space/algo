// 生成した索引（型・関数・ヘッダ）を読み込み、上部の検索窓で絞り込む。
(() => {
  const input = document.getElementById("reference-search-input");
  const list = document.getElementById("reference-search-results");
  if (!input || !list) return;

  const baseUrl = new URL(document.querySelector('link[rel="stylesheet"]').href)
    .href.replace(/assets\/css\/reference\.css.*$/, "");
  const kindLabels = {
    header: "ヘッダ",
    class: "クラス",
    concept: "コンセプト",
    alias: "エイリアス",
    function: "関数",
    operator: "演算子",
    variable: "変数",
  };

  let entries = null;
  let active = -1;

  const load = async () => {
    if (entries) return entries;
    const response = await fetch(`${baseUrl}assets/reference-index.json`);
    entries = await response.json();
    return entries;
  };

  const score = (entry, query) => {
    const name = entry.name.toLowerCase();
    if (name === query) return 0;
    if (name.startsWith(query)) return 1;
    if (name.includes(query)) return 2;
    if (entry.header.toLowerCase().includes(query)) return 3;
    if ((entry.title || "").toLowerCase().includes(query)) return 4;
    return -1;
  };

  const render = (matches) => {
    list.innerHTML = "";
    active = -1;
    if (matches.length === 0) {
      list.hidden = true;
      return;
    }
    for (const entry of matches) {
      const item = document.createElement("li");
      const link = document.createElement("a");
      link.href = `${baseUrl}reference/${entry.url}`;
      link.innerHTML =
        `<span class="result-kind">${kindLabels[entry.kind] || entry.kind}</span>` +
        `<span class="result-name"></span>` +
        `<span class="result-header"></span>`;
      link.querySelector(".result-name").textContent = entry.name;
      link.querySelector(".result-header").textContent = entry.title || entry.header;
      item.appendChild(link);
      list.appendChild(item);
    }
    list.hidden = false;
  };

  const search = async () => {
    const query = input.value.trim().toLowerCase();
    if (query.length === 0) {
      list.hidden = true;
      return;
    }
    const data = await load();
    const matches = data
      .map((entry) => [score(entry, query), entry])
      .filter(([value]) => value >= 0)
      .sort((a, b) => a[0] - b[0] || a[1].name.length - b[1].name.length)
      .slice(0, 30)
      .map(([, entry]) => entry);
    render(matches);
  };

  const move = (delta) => {
    const items = [...list.children];
    if (items.length === 0) return;
    if (active >= 0) items[active].classList.remove("is-active");
    active = (active + delta + items.length) % items.length;
    items[active].classList.add("is-active");
    items[active].scrollIntoView({ block: "nearest" });
  };

  input.addEventListener("input", search);
  input.addEventListener("focus", load);
  input.addEventListener("keydown", (event) => {
    if (event.key === "ArrowDown") { event.preventDefault(); move(1); }
    else if (event.key === "ArrowUp") { event.preventDefault(); move(-1); }
    else if (event.key === "Enter" && active >= 0) {
      event.preventDefault();
      list.children[active].querySelector("a").click();
    } else if (event.key === "Escape") { list.hidden = true; input.blur(); }
  });
  document.addEventListener("click", (event) => {
    if (!list.contains(event.target) && event.target !== input) list.hidden = true;
  });
  document.addEventListener("keydown", (event) => {
    if (event.key === "/" && document.activeElement !== input) {
      event.preventDefault();
      input.focus();
    }
  });
})();
