import subprocess
import sys
import tempfile
import time
from pathlib import Path

# 同じディレクトリ(tools)内のモジュールを確実にインポートする
sys.path.append(str(Path(__file__).resolve().parent))
from generate import generate_test_case

# === 設定項目 ===
MY_SOL_SRC = Path("./workspace/main.cpp")
REF_SOL_SRC = Path("./workspace/correct.cpp")


def compile_cpp(source, output):
    """C++ファイルをコンパイルする"""
    print(f"Compiling {source}...")
    res = subprocess.run(
        ["g++", "-std=c++23", "-O3", str(source), "-o", str(output)],
        capture_output=True,
        text=True,
    )
    if res.returncode != 0:
        print(f"Compilation Error ({source}):")
        print(res.stderr)
        sys.exit(1)


def run_exe(exe_path, input_data):
    """バイナリを実行して結果を返す"""
    try:
        res = subprocess.run(
            [str(exe_path)], input=input_data, capture_output=True, text=True, timeout=5
        )
        if res.returncode != 0:
            return f"RUNTIME ERROR\n{res.stderr}"
        return res.stdout.strip()
    except subprocess.TimeoutExpired:
        return "TIME LIMIT EXCEEDED"


def main():
    with tempfile.TemporaryDirectory() as tmpdir:
        tmp_path = Path(tmpdir)
        my_sol_exe = tmp_path / "my_solution"
        ref_sol_exe = tmp_path / "correct_solution"

        # 1. コンパイル
        compile_cpp(MY_SOL_SRC, my_sol_exe)
        compile_cpp(REF_SOL_SRC, ref_sol_exe)

        num_tests = 0
        total_time = 0.0
        print("Starting random check...")

        try:
            while True:
                num_tests += 1
                # デバッグしやすいように小さな制約から開始したい場合は引数を設定する
                input_data = generate_test_case(n_limit=10)

                ans_ref = run_exe(ref_sol_exe, input_data)

                start_time = time.time()
                ans_my = run_exe(my_sol_exe, input_data)
                elapsed_time = time.time() - start_time
                total_time += elapsed_time

                if ans_ref == ans_my:
                    avg_time = total_time / num_tests
                    print(f"Test {num_tests}: OK (avg: {avg_time:.4f}s)", end="\r")
                else:
                    print(f"\nTest {num_tests}: FAILED")
                    print("--- Input ---")
                    print(input_data)
                    print("--- Expected (correct.cpp) ---")
                    print(ans_ref)
                    print("--- Found (main.cpp) ---")
                    print(ans_my)

                    with open("error_input.txt", "w") as f:
                        f.write(input_data)
                    print("\nInput saved to error_input.txt")
                    break
        except KeyboardInterrupt:
            print("\nTesting stopped by user.")


if __name__ == "__main__":
    main()
