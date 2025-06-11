#include <iostream>
#include <vector>

class Solution {
  public:
    int integerBreak(int n) {
        std::vector<int> max_products(n + 1, 0);

        max_products[1] = 1;

        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                max_products[i] = std::max(max_products[i], std::max(j * (i - j), j * max_products[i - j]));
            }
        }

        return max_products[n];
    }
};

int main() {
    Solution solution;

    std::cout << solution.integerBreak(2) << std::endl;

    std::cout << solution.integerBreak(10) << std::endl;

    return 0;
}