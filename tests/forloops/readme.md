# OS Language Microbenchmark

This repository contains microbenchmark scripts used to test and compare the performance of a simple `for` loop across multiple programming languages.

## Benchmark Task

Increment a variable `x` by `i` in a loop that runs 1,000,000,000 times:

```text
x += i
```

## Methodology

* Each test uses high-resolution timers (e.g., `QueryPerformanceCounter` on Windows).
* All implementations perform a warmup loop to stabilize CPU performance.
* Outputs include total elapsed time and calculated operations per millisecond (Ops/ms).

## Results (Ops/ms)

| Language          | Ops/ms |
| ----------------- | -----: |
| **OS (AOT)**      | 1850.4 |
| **OS (JIT)**      | 1810.4 |
| C++               | 1437.4 |
| C                 | 1424.6 |
| Rust              | 1210.0 |
| Go                |  580.0 |
| Java              |  321.3 |
| JavaScript (Node) |    8.8 |
| Python            |    1.5 |

> Note: This is a **microbenchmark**. Real-world performance will vary.

## Chart

![For Loop Benchmark Chart](benchmark_chart.png)

## Usage

Clone the repo and run the corresponding benchmark files for each language.
Make sure all dependencies and compilers/runtimes are installed.

### Example (Rust):

```bash
cargo build --release
./target/release/bench_rust
```

### Example (C):

```bash
gcc -O3 -o bench_c test.c
./bench_c
```

## File Structure

```
/benchmarks
  test.c
  test.cpp
  test.rs
  test.go
  test.java
  test.py
  test.js
  test.os       # OS AOT
  test_jit.os   # OS JIT
  for_loop_benchmark_chart_os.png
```

## License

MIT License
