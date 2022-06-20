#include <benchmark/benchmark.h>

static void BenchmarkValidator(benchmark::State& state) {
    for (auto _ : state) {
    }
}

BENCHMARK(BenchmarkValidator);
