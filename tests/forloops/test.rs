use std::hint::black_box;

#[link(name = "kernel32")]
extern "system" {
    fn QueryPerformanceCounter(lpPerformanceCount: *mut i64) -> i32;
    fn QueryPerformanceFrequency(lpFrequency: *mut i64) -> i32;
}

fn main() {
    let mut freq: i64 = 0;
    let mut start: i64 = 0;
    let mut end: i64 = 0;

    let mut warmup: i64 = 0;
    let mut warmup_noise: i64 = 0;

    unsafe {
        QueryPerformanceFrequency(&mut freq);

        // Warmup loop
        for i in 0..1_000_000i64 {
            if i % 1_000_000_001 == 0 {
                let mut temp = 0;
                QueryPerformanceCounter(&mut temp);
                warmup_noise ^= temp;
            }
            warmup += i;
        }

        let mut noise: i64 = 0;
        let mut x: i64 = warmup ^ warmup_noise;

        QueryPerformanceCounter(&mut start);

        // Main benchmark loop with black_box to prevent optimization
        for i in 0..1_000_000_000i64 {
            if i % 1_000_000_001 == 0 {
                let mut temp = 0;
                QueryPerformanceCounter(&mut temp);
                noise ^= temp;
            }
            x += black_box(i); // Prevent the compiler from optimizing this away
        }

        QueryPerformanceCounter(&mut end);
        x ^= noise;

        // Use black_box on the final result to ensure it's not optimized away
        black_box(x);

        let elapsed_ms = (end - start) as f64 * 1000.0 / freq as f64;

        println!("Result: {}", x);
        println!("Elapsed: {:.4} ms", elapsed_ms);
        println!("Ops/ms: {:.1}", 1_000_000.0 / elapsed_ms);
    }
}