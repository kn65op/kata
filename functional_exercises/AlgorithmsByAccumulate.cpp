#include <algorithm>
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

#include "benchmark/benchmark.h"

constexpr auto M = 10000;
constexpr double M_double = M;
std::vector<double> numbers(M, M_double);

auto eq = [](auto d) { return d == M_double; };

static void any_of_std(benchmark::State& state)
{
    for (auto _ : state)
        std::any_of(numbers.begin(), numbers.end(), eq);
}

static void any_of_accumulate(benchmark::State& state)
{
    for (auto _ : state)
        std::accumulate(numbers.begin(), numbers.end(), false,
                        [&](const auto& ac, const auto& val) {
                            return ac ? ac : ac || eq(val);
                        });
}

static void all_of_std(benchmark::State& state)
{
    for (auto _ : state)
        std::all_of(numbers.begin(), numbers.end(), eq);
}

static void all_of_accumulate(benchmark::State& state)
{
    for (auto _ : state)
        std::accumulate(numbers.begin(), numbers.end(), false,
                        [&](const auto& ac, const auto& val) {
                            return ac ? ac : ac || eq(val);
                        });
}

template <typename It>
inline bool all_of_one(It begin, It end)
{
    while (begin != end && eq(*begin))
        ++begin;
    return begin == end;
}

template <typename It>
bool all_of_two(It begin, It end)
{
    return end == std::find_if_not(begin, end, eq);
}

static void all_of_own(benchmark::State& state)
{
    for (auto _ : state)
        all_of_one(numbers.cbegin(), numbers.cend());
}

static void all_of_own_find(benchmark::State& state)
{
    for (auto _ : state)
        all_of_two(numbers.begin(), numbers.end());
}

BENCHMARK(all_of_std);
BENCHMARK(all_of_accumulate);
BENCHMARK(all_of_own);
BENCHMARK(all_of_own_find);
BENCHMARK(any_of_std);
BENCHMARK(any_of_accumulate);

BENCHMARK_MAIN();
