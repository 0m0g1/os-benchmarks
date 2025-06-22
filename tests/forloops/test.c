// bench_c.c
// gcc -O3 -o bench_c.exe test.c
#include <windows.h>
#include <stdint.h>
#include <stdio.h>

int main() {
    LARGE_INTEGER freq, start, end;

    // Get timer frequency
    if (!QueryPerformanceFrequency(&freq)) {
        fprintf(stderr, "QueryPerformanceFrequency failed\n");
        return 1;
    }

    // Warmup loop with noise
    int64_t warmup = 0, warmupNoise = 0;
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

    // Benchmark loop
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

    double elapsedMs = (end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;

    printf("Result: %lld\n", x);
    printf("Elapsed: %.4f ms\n", elapsedMs);
    printf("Ops/ms: %.1f\n", 1000000.0 / elapsedMs);

    return 0;
}