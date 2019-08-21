#include <algorithm>
#include <execution>
#include <iostream>
#include <vector>

#include "benchmark/benchmark.h"

constexpr auto N = 80000;
std::vector<double> numbers_big(N, N);
std::vector<double> toCheck_big(N, N);

constexpr auto M = 1000;
std::vector<double> numbers_small(M, M);
std::vector<double> toCheck_small(M, M);

template <typename Policy, typename Seq>
void test_algorithm(Policy policy, const Seq& numbers, const Seq& toCheck)
{
    std::count_if(policy, numbers.begin(), numbers.end(), [&](const auto& el) {
        return std::count_if(
                   policy, toCheck.begin(), toCheck.end(),
                   [&](const auto& check) { return el * 2.3 < check < N; }) < N;
    });
}

static void seq_algorithm_big(benchmark::State& state)
{
    for (auto _ : state)
        test_algorithm(std::execution::seq, numbers_big, toCheck_big);
}

static void par_algorithm_big(benchmark::State& state)
{
    for (auto _ : state)
        test_algorithm(std::execution::par, numbers_big, toCheck_big);
}

static void unseq_algorithm_big(benchmark::State& state)
{
    for (auto _ : state)
        test_algorithm(std::execution::unseq, numbers_big, toCheck_big);
}

static void parunseq_algorithm_big(benchmark::State& state)
{
    for (auto _ : state)
        test_algorithm(std::execution::par_unseq, numbers_big, toCheck_big);
}

static void seq_algorithm_small(benchmark::State& state)
{
    for (auto _ : state)
        test_algorithm(std::execution::seq, numbers_small, toCheck_small);
}

static void par_algorithm_small(benchmark::State& state)
{
    for (auto _ : state)
        test_algorithm(std::execution::par, numbers_small, toCheck_small);
}

static void unseq_algorithm_small(benchmark::State& state)
{
    for (auto _ : state)
        test_algorithm(std::execution::unseq, numbers_small, toCheck_small);
}

static void parunseq_algorithm_small(benchmark::State& state)
{
    for (auto _ : state)
        test_algorithm(std::execution::par_unseq, numbers_small, toCheck_small);
}

BENCHMARK(seq_algorithm_big);
BENCHMARK(par_algorithm_big);
BENCHMARK(unseq_algorithm_big);
BENCHMARK(parunseq_algorithm_big);
BENCHMARK(seq_algorithm_small);
BENCHMARK(par_algorithm_small);
BENCHMARK(unseq_algorithm_small);
BENCHMARK(parunseq_algorithm_small);

BENCHMARK_MAIN();
