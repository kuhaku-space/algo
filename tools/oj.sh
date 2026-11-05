# shellcheck shell=bash
# mise.toml の workspace/ 用タスク（build / pch / random-check など）が source する共通処理。
# 設計の理由は docs/current/toolchain.md の「workspace/ のタスク設計」を参照。

OJ_ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
OJ_LIB="$OJ_ROOT/lib"
# shellcheck disable=SC2034  # source 元のタスクが使う
OJ_PCH="$OJ_ROOT/workspace/.pch"

# コンパイルフラグ。PCH はこれと同じフラグでないと使われないので一箇所にまとめる。
OJ_CXX_FLAGS=(
  -DNOMINMAX -DONLINE_JUDGE -DOR_PROTO_DLL= -DPROTOBUF_USE_DLLS -DUSE_BOP -DUSE_CBC -DUSE_CLP
  -DUSE_GLOP -DUSE_LP_PARSER -DUSE_MATH_OPT -DUSE_PDLP -DUSE_SCIP
  -Wall -Wextra
  -fconstexpr-depth=1024 -fconstexpr-loop-limit=524288 -fconstexpr-ops-limit=2097152
  -march=native -pthread -std=gnu++23 -fopenmp
)
OJ_CXX_RELEASE_FLAGS=(-O2 -ftrivial-auto-var-init=zero)
# shellcheck disable=SC2054  # -fsanitize= のカンマは区切りではない
OJ_CXX_DEBUG_FLAGS=(-O1 -g -fsanitize=address,undefined -D_GLIBCXX_DEBUG)

# $1 を lib/ で bundle して標準出力に出す。
oj_bundle() {
  oj-bundle -I "$OJ_LIB" "$1" 2>/dev/null \
    | grep -v "^#line " | grep -v "^#pragma once" | tr -s "\n"
}

# 標準入力のソースで bits/stdc++.h の include より前にある #pragma GCC optimize を同じ意味の
# フラグにする（GCC と同じく "O3" は -O3、"unroll-loops" は -funroll-loops と読む）。
oj_pragma_flags() {
  local opts opt flags=()
  IFS=, read -ra opts < <(sed -n '/^#include <bits\/stdc++\.h>/q; s/^#pragma GCC optimize("\(.*\)")$/\1/p' | paste -sd,)
  for opt in "${opts[@]}"; do
    case "$opt" in
      -*) flags+=("$opt") ;;
      O*) flags+=("-$opt") ;;
      *) flags+=("-f$opt") ;;
    esac
  done
  echo "${flags[*]}"
}

# 共通フラグでコンパイル・リンクする。OJ_DEBUG=true ならデバッグ用フラグにする。
# 引数は最後に置き、-O などを上書きできるようにする。
oj_compile() {
  local opt_args=("${OJ_CXX_RELEASE_FLAGS[@]}")
  [[ "${OJ_DEBUG:-}" == "true" ]] && opt_args=("${OJ_CXX_DEBUG_FLAGS[@]}")
  g++-15 "${OJ_CXX_FLAGS[@]}" "${opt_args[@]}" -Wl,--as-needed "$@"
}

# 再帰の深い解法がローカルでだけ SIGSEGV しないようスタックを広げる（子に継承される）。
oj_raise_stack_limit() {
  ulimit -s unlimited 2>/dev/null || ulimit -s 1048576
}
