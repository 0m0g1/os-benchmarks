// High-resolution benchmark in Node.js using BigInt and process.hrtime.bigint()

let warmup = 0n;
let warmupNoise = 0n;

// Warmup phase to stabilize the JIT
for (let i = 0n; i < 1_000_000n; i++) {
    if (i % 1_000_000_001n === 0n) {
        warmupNoise ^= process.hrtime.bigint();
    }
    warmup += i;
}

let x = warmup ^ warmupNoise;
let noise = 0n;

const start = process.hrtime.bigint();

// Main benchmark loop
for (let i = 0n; i < 1_000_000_000n; i++) {
    if (i % 1_000_000_001n === 0n) {
        noise ^= process.hrtime.bigint();
    }
    x += i;
}

const end = process.hrtime.bigint();

x ^= noise;

const elapsedNs = end - start;
const elapsedMs = Number(elapsedNs) / 1_000_000;

console.log(`Result: ${x}`);
console.log(`Elapsed: ${elapsedMs.toFixed(4)} ms`);
console.log(`Ops/ms: ${(1_000_000.0 / elapsedMs).toFixed(1)}`);
