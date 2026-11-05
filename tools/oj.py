#!/usr/bin/env python3
"""Bundle and compile solutions in workspace/ (the oj tasks of mise.toml).

Subcommands:

- ``build [--debug] [SRC]``: bundle SRC into main.cpp and compile it, using the
  precompiled bits/stdc++.h when it matches.
- ``pch``: create the precompiled bits/stdc++.h in workspace/.pch.
- ``random-check [SRC]``: build SRC, then build and run checker/test.cpp.

Paths other than the library and the PCH are relative to the current
directory, which mise sets to workspace/.  The design is documented in
docs/current/toolchain.md.
"""

from __future__ import annotations

import argparse
import re
import resource
import shutil
import subprocess
import sys
from collections.abc import Sequence
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LIB = ROOT / "lib"
PCH = ROOT / "workspace" / ".pch"
PCH_HEADER = PCH / "bits" / "stdc++.h"
PCH_GCH = PCH / "bits" / "stdc++.h.gch"
PCH_FLAGS = PCH / "flags"

CXX = "g++-15"
# The PCH is used only when it was built with the same flags, so keep them here.
CXX_FLAGS = [
    # Macros defined by the judges this repository targets.
    "-DNOMINMAX",
    "-DONLINE_JUDGE",
    "-DOR_PROTO_DLL=",
    "-DPROTOBUF_USE_DLLS",
    "-DUSE_BOP",
    "-DUSE_CBC",
    "-DUSE_CLP",
    "-DUSE_GLOP",
    "-DUSE_LP_PARSER",
    "-DUSE_MATH_OPT",
    "-DUSE_PDLP",
    "-DUSE_SCIP",
    "-Wall",
    "-Wextra",
    "-fconstexpr-depth=1024",
    "-fconstexpr-loop-limit=524288",
    "-fconstexpr-ops-limit=2097152",
    "-march=native",
    "-pthread",
    "-std=gnu++23",
    "-fopenmp",
]
RELEASE_FLAGS = ["-O2", "-ftrivial-auto-var-init=zero"]
DEBUG_FLAGS = ["-O1", "-g", "-fsanitize=address,undefined", "-D_GLIBCXX_DEBUG"]
LINK_FLAGS = ["-Wl,--as-needed"]

STDCXX_INCLUDE = re.compile(r"^#include <bits/stdc\+\+\.h>")
OPTIMIZE_PRAGMA = re.compile(r"^#pragma GCC optimize\((.*)\)")


class TaskError(Exception):
    """A failure whose message is shown to the user."""


def run(cmd: Sequence[str | Path], **kwargs) -> subprocess.CompletedProcess:
    """Run cmd, raising TaskError with its exit status on failure."""
    result = subprocess.run([str(c) for c in cmd], check=False, **kwargs)
    if result.returncode != 0:
        if result.stderr:  # captured output (oj-bundle logs) is shown only on failure
            sys.stderr.write(result.stderr)
        raise TaskError(
            f"{Path(str(cmd[0])).name} が失敗しました（終了コード {result.returncode}）"
        )
    return result


# --- source transformations ------------------------------------------------


def clean_bundled(text: str) -> str:
    """Drop #line, #pragma once and blank lines from oj-bundle output."""
    lines = (
        line
        for line in text.splitlines()
        if line and not line.startswith("#line ") and not line.startswith("#pragma once")
    )
    return "".join(f"{line}\n" for line in lines)


def _preamble(source: str) -> list[str]:
    """Lines before ``#include <bits/stdc++.h>`` (all lines if it is absent)."""
    lines = source.splitlines()
    for i, line in enumerate(lines):
        if STDCXX_INCLUDE.match(line):
            return lines[:i]
    return lines


def optimize_option_to_flag(option: str) -> str:
    """Map a ``#pragma GCC optimize`` option to the flag GCC treats it as."""
    if option.startswith("-"):
        return option
    if option.startswith("O"):
        return f"-{option}"
    return f"-f{option}"


def pragma_flags(source: str) -> list[str]:
    """Flags equivalent to the optimize pragmas before ``#include <bits/stdc++.h>``.

    GCC rejects the PCH when such pragmas precede the include, so build passes
    them as flags instead (e.g. ``"Ofast"`` -> ``-Ofast``, ``"unroll-loops"`` ->
    ``-funroll-loops``).
    """
    flags = []
    for line in _preamble(source):
        if match := OPTIMIZE_PRAGMA.match(line):
            for option in match.group(1).split(","):
                option = option.strip().strip('"').strip()
                if option:
                    flags.append(optimize_option_to_flag(option))
    return flags


def strip_preamble_pragmas(source: str) -> str:
    """Blank the optimize pragmas before ``#include <bits/stdc++.h>``.

    The lines are emptied rather than removed so line numbers stay the same.
    """
    lines = source.splitlines()
    preamble_len = len(_preamble(source))
    for i in range(preamble_len):
        if OPTIMIZE_PRAGMA.match(lines[i]):
            lines[i] = ""
    return "".join(f"{line}\n" for line in lines)


# --- external tools --------------------------------------------------------


def bundle(src: Path) -> str:
    if not src.is_file():
        raise TaskError(f"{src} が見つかりません")
    result = run(["oj-bundle", "-I", LIB, src], capture_output=True, text=True)
    return clean_bundled(result.stdout)


def compile_cxx(
    args: Sequence[str | Path],
    *,
    debug: bool = False,
    cwd: Path | None = None,
    stdin: str | None = None,
) -> None:
    """Compile and link with the shared flags; args come last to override them."""
    opt_flags = DEBUG_FLAGS if debug else RELEASE_FLAGS
    run([CXX, *CXX_FLAGS, *opt_flags, *LINK_FLAGS, *args], cwd=cwd, input=stdin, text=True)


def raise_stack_limit() -> None:
    """Raise the stack limit as far as allowed; child processes inherit it.

    Deeply recursive solutions would otherwise crash locally only.
    """
    _, hard = resource.getrlimit(resource.RLIMIT_STACK)
    resource.setrlimit(resource.RLIMIT_STACK, (hard, hard))


def pch_matches(flags: Sequence[str]) -> bool:
    if not PCH_GCH.is_file() or not PCH_FLAGS.is_file():
        return False
    return PCH_FLAGS.read_text().split() == list(flags)


# --- subcommands -----------------------------------------------------------


def build(src: Path, *, debug: bool = False) -> None:
    source = bundle(src)
    main = Path("main.cpp")
    main.write_text(source)
    flags = pragma_flags(source)
    if not debug and pch_matches(flags):
        # main.cpp is submitted as is; the compiler reads a copy without the
        # pragmas, with #line keeping diagnostics pointing at main.cpp.
        stdin = '#line 1 "main.cpp"\n' + strip_preamble_pragmas(source)
        compile_cxx(["-I", PCH, "-Winvalid-pch", *flags, "-x", "c++", "-"], stdin=stdin)
    else:
        compile_cxx([main], debug=debug)


def find_stdcxx_header() -> Path:
    result = subprocess.run(
        [CXX, "-std=gnu++23", "-x", "c++", "-H", "-fsyntax-only", "-"],
        input="#include <bits/stdc++.h>\n",
        capture_output=True,
        text=True,
        check=False,
    )
    first = result.stderr.splitlines()[:1]
    header = Path(first[0].split()[1]) if first and len(first[0].split()) > 1 else None
    if header is None or not header.is_file():
        raise TaskError("bits/stdc++.h が見つかりません")
    return header


def pch() -> None:
    # Use the template's pragmas; build uses the PCH only when they match.
    flags = pragma_flags(bundle(Path("template/template.cpp")))
    header = find_stdcxx_header()
    PCH_FLAGS.unlink(missing_ok=True)
    # Keep the plain header beside the PCH so it is read when the PCH is rejected.
    PCH_HEADER.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(header, PCH_HEADER)
    run([CXX, *CXX_FLAGS, *RELEASE_FLAGS, *flags, "-x", "c++-header", PCH_HEADER, "-o", PCH_GCH])
    PCH_FLAGS.write_text(" ".join(flags) + "\n")
    print(f"PCH を作成しました: {PCH}（optimize pragma 由来のフラグ: {' '.join(flags) or 'なし'}）")


def random_check(src: Path) -> None:
    Path("main.cpp").write_text(bundle(src))
    compile_cxx(["main.cpp"])
    checker = Path("checker")
    test_dir = checker / "test"
    test_dir.mkdir(parents=True, exist_ok=True)
    (test_dir / "main.cpp").write_text(bundle(checker / "test.cpp"))
    compile_cxx(["main.cpp"], cwd=test_dir)
    raise_stack_limit()
    run(["./a.out"], cwd=test_dir)


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = parser.add_subparsers(dest="command", required=True)
    p_build = sub.add_parser("build")
    p_build.add_argument("--debug", action="store_true")
    p_build.add_argument("src", nargs="?", default="a.cpp", type=Path)
    sub.add_parser("pch")
    p_rc = sub.add_parser("random-check")
    p_rc.add_argument("src", nargs="?", default="a.cpp", type=Path)
    args = parser.parse_args(argv)
    try:
        if args.command == "build":
            build(args.src, debug=args.debug)
        elif args.command == "pch":
            pch()
        else:
            random_check(args.src)
    except TaskError as e:
        print(e, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
