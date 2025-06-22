// bench_cpp.cpp
// g++ -O3 -std=c++23 -o bench_cpp.exe test.cpp
#include <windows.h>
#include <cstdint>
#include <iostream>

int main() {
    LARGE_INTEGER freq, start, end;

    if (!QueryPerformanceFrequency(&freq)) {
        std::cerr << "Failed to query performance frequency\n";
        return 1;
    }

    int64_t warmup = 0;
    int64_t warmupNoise = 0;

    // Warmup loop with noise sampling
    for (int64_t i = 0; i < 1000000; ++i) {
        if (i % 1000000001 == 0) {
            LARGE_INTEGER temp;
            QueryPerformanceCounter(&temp);
            warmupNoise ^= temp.QuadPart;
        }
        warmup += i;
    }

    int64_t noise = 0;
    int64_t x = warmup ^ warmupNoise;

    QueryPerformanceCounter(&start);

    for (int64_t i = 0; i < 1000000000; ++i) {
        if (i % 1000000001 == 0) {
            LARGE_INTEGER temp;
            QueryPerformanceCounter(&temp);
            noise ^= temp.QuadPart;
        }
        x += i;
    }

    QueryPerformanceCounter(&end);

    x ^= noise;

    double elapsedMs = (static_cast<double>(end.QuadPart - start.QuadPart) * 1000.0) / freq.QuadPart;

    std::cout << "Result: " << x << "\n";
    std::cout << "Elapsed: " << elapsedMs << " ms\n";
    std::cout << "Ops/ms: " << (1000000.0 / elapsedMs) << "\n";

    return 0;
}