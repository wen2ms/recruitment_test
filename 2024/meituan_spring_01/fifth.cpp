#include <cmath>
#include <iostream>
#include <vector>

int main() {
    int n, k;

    std::cin >> n >> k;

    std::vector<long long> input_numbers(n + 1);
    std::vector<long long> prefix_products(n + 1, 1);

    for (int i = 1; i <= n; ++i) {
        std::cin >> input_numbers[i];

        prefix_products[i] = prefix_products[i - 1] * input_numbers[i];
    }

    int plans_count = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            long long product = prefix_products[n] / prefix_products[j] * prefix_products[i - 1];


            if (product % (long long)std::pow(10, k) == 0) {
                ++plans_count;
            }
        }
    }

    std::cout << plans_count << std::endl;

    return 0;
}