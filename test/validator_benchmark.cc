#include <benchmark/benchmark.h>

#include "validator/validator.h"

static void BenchmarkValidator(benchmark::State& state) {
    for (auto _ : state) {
    }
}

BENCHMARK(BenchmarkValidator);
