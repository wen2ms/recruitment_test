#include <iostream>
#include <vector>

int GetMaxRound(int a, int b) {
    std::vector<std::vector<int>> competitions_count(a + 1, std::vector<int>(b + 1));

    for (int i = 0; i <= a; ++i) {
        for (int j = 0; j <= b; ++j) {
            if (i > 0 && j > 0) {
                competitions_count[i][j] = std::max(competitions_count[i][j], competitions_count[i - 1][j - 1] + 1);
            }
            if (i >= 3) {
                competitions_count[i][j] = std::max(competitions_count[i][j], competitions_count[i - 3][j] + 1);
            }
            if (j >= 3) {
                competitions_count[i][j] = std::max(competitions_count[i][j], competitions_count[i][j - 3] + 1);
            }
        }
    }
    return (competitions_count[a][b] == 0 ? -1 : competitions_count[a][b]);
}

int main() {
    std::cout << GetMaxRound(3, 3) << '\n';
    std::cout << GetMaxRound(1, 0) << '\n';

    return 0;
}