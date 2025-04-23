

#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <algorithm>
#include <chrono>

// Linear Congruential Generator
class LCG {
public:
    LCG(uint32_t seed, uint32_t a = 1664525, uint32_t c = 1013904223, uint32_t m = (1u << 32))
        : value(seed), a(a), c(c), m(m) {}

    uint32_t operator()() {
        value = (a * value + c) % m;
        return value;
    }

private:
    uint32_t value, a, c, m;
};

double max_subarray_sum(const std::vector<int>& random_numbers) {
    double max_sum = std::numeric_limits<double>::lowest();
    for (size_t i = 0; i < random_numbers.size(); ++i) {
        double current_sum = 0;
        for (size_t j = i; j < random_numbers.size(); ++j) {
            current_sum += random_numbers[j];
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
    }
    return max_sum;
}

double total_max_subarray_sum(size_t n, uint32_t initial_seed, int min_val, int max_val) {
    double total_sum = 0;
    LCG lcg_gen(initial_seed);
    for (int i = 0; i < 20; ++i) {
        std::vector<int> random_numbers(n);
        for (size_t j = 0; j < n; ++j) {
            random_numbers[j] = (lcg_gen() % (max_val - min_val + 1)) + min_val;
        }
        total_sum += max_subarray_sum(random_numbers);
    }
    return total_sum;
}

int main() {
    const size_t n = 10000;
    const uint32_t initial_seed = 42;
    const int min_val = -10;
    const int max_val = 10;

    auto start_time = std::chrono::high_resolution_clock::now();
    double result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << "Total Maximum Subarray Sum (20 runs): " << result << std::endl;
    std::cout << "Execution Time: " << std::chrono::duration<double>(end_time - start_time).count() << " seconds" << std::endl;

    return 0;
}