#include <iostream>
#include <string>
#include <vector>

class Solution {
  public:
    int minDistance(std::string word1, std::string word2) {
        const int m = word1.size();
        const int n = word2.size();

        std::vector<std::vector<int>> minimum_operations(m + 1, std::vector<int>(n + 1));

        for (int i = 1; i <= m; ++i) {
            minimum_operations[i][0] = i;
        }

        for (int i = 1; i <= n; ++i) {
            minimum_operations[0][i] = i;
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    minimum_operations[i][j] = minimum_operations[i - 1][j - 1];
                } else {
                    minimum_operations[i][j] =
                        std::min({minimum_operations[i - 1][j - 1], minimum_operations[i - 1][j], minimum_operations[i][j - 1]}) +
                        1;
                }
            }
        }

        return minimum_operations[m][n];
    }
};

int main() {
    Solution solution;

    std::cout << solution.minDistance("horse", "ros") << std::endl;

    std::cout << solution.minDistance("intention", "execution") << std::endl;

    return 0;
}