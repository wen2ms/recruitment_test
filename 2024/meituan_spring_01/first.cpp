#include <iostream>
#include <vector>
#include <string>

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> matrix(n + 1, std::vector<int>(n + 1));
    std::vector<std::vector<int>> prefix_2d(n + 1, std::vector<int>(n + 1));

    for (int i = 1; i <= n; ++i) {
        std::string row;

        std::cin >> row;
        for (int j = 0; j < n; ++j) {
            prefix_2d[i][j + 1] = prefix_2d[i][j] + prefix_2d[i - 1][j + 1] - prefix_2d[i - 1][j] + row[j]
                                  - '0';
        }
    }

    for (int i = 1; i <= n; ++i) {
        int count = 0;
        for (int j = 1; j <= n - i + 1; ++j) {
            for (int k = 1; k <= n - i + 1; ++k) {
                int sum = prefix_2d[j + i - 1][k + i - 1] - prefix_2d[j - 1][k + i - 1]
                          - prefix_2d[j + i - 1][k - 1] + prefix_2d[j - 1][k - 1];
                if(sum * 2 == i * i) {
                    count++;
                }
            } 
        }
        std::cout << count << std::endl;
    }

    return 0;
}