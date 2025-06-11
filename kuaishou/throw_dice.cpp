#include <iostream>
#include <vector>

// 丢 n 次 6 面骰子，点数和为 k 的概率是多少？

int main() {
    int n, k;

    std::cin >> n >> k;

    double probability = 0;

    if (k < n || k > 6 * n) {
        std::cout << 0 << std::endl;

        return 0;
    }

    std::vector<std::vector<long long>> combinations(n + 1, std::vector<long long>(k + 1, 0));

    combinations[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= std::min(k, 6 * i); ++j) {
            for (int face = 1; face <= 6; ++face) {
                if (j - face >= 0) {
                    combinations[i][j] += combinations[i - 1][j - face];
                }
            }
        }
    }

    long long total = std::pow(6, n);

    probability = static_cast<double>(combinations[n][k]) / total;

    std::cout << probability << std::endl;

    return 0;
}