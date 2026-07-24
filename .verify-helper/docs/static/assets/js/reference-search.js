(() => {
  const input = document.getElementById("reference-search-input");
  if (!input) return;

  const categories = [...document.querySelectorAll(".reference-category")];
  const entries = categories.flatMap((category) =>
    [...category.querySelectorAll("li[data-search]")].map((item) => ({
      category,
      item,
      search: item.dataset.search.normalize("NFKC").toLocaleLowerCase("ja"),
    }))
  );
  const status = document.getElementById("reference-search-status");

  const update = () => {
    const query = input.value.trim().normalize("NFKC").toLocaleLowerCase("ja");
    let visible = 0;
    for (const entry of entries) {
      const matched = !query || entry.search.includes(query);
      entry.item.hidden = !matched;
      if (matched) visible++;
    }
    for (const category of categories) {
      category.hidden = !category.querySelector("li[data-search]:not([hidden])");
    }
    status.textContent = query ? `${visible}件見つかりました` : `${entries.length}ヘッダ`;
  };

  input.addEventListener("input", update);
  document.addEventListener("keydown", (event) => {
    if (event.key === "/" && document.activeElement !== input) {
      event.preventDefault();
      input.focus();
    }
    if (event.key === "Escape" && document.activeElement === input) {
      input.value = "";
      update();
      input.blur();
    }
  });
  update();
})();
