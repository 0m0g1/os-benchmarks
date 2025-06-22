import ctypes

qpc = ctypes.windll.kernel32.QueryPerformanceCounter
qpf = ctypes.windll.kernel32.QueryPerformanceFrequency

freq = ctypes.c_int64()
qpf(ctypes.byref(freq))

warmup = 0
warmup_noise = 0
for i in range(100_000):  # smaller warmup loop
    if i % 1_000_000_001 == 0:
        tmp = ctypes.c_int64()
        qpc(ctypes.byref(tmp))
        warmup_noise ^= tmp.value
    warmup += i

x = warmup ^ warmup_noise
noise = 0

start = ctypes.c_int64()
qpc(ctypes.byref(start))

for i in range(10_000_000):  # main benchmark loop (10 million iterations)
    if i % 1_000_000_001 == 0:
        tmp = ctypes.c_int64()
        qpc(ctypes.byref(tmp))
        noise ^= tmp.value
    x += i

end = ctypes.c_int64()
qpc(ctypes.byref(end))

x ^= noise

elapsed_ms = (end.value - start.value) * 1000.0 / freq.value
ops_per_ms = 10_000_000 / elapsed_ms

print(f"Result: {x}")
print(f"Elapsed: {elapsed_ms:.4f} ms")
print(f"Ops/ms: {ops_per_ms:.1f}")
