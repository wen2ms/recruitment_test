#include <iostream>
#include <vector>

// 计算组合数

long long combinations(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }

    if (k > n - k) {
        k = n - k;
    }

    long long number_combinations = 1;

    for (int i = 1; i <= k; ++i) {
        number_combinations *= n - i + 1;

        number_combinations /= i;
    }

    return number_combinations;
}

int main() {
    std::cout << combinations(5, 2) << std::endl;

    std::cout << combinations(10, 3) << std::endl;

    return 0;
}