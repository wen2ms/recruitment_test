#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n, x, y;

    std::cin >> n >> x >> y;

    std::vector<int> scores(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> scores[i];
    }

    int m = 2000;
    bool exists_m = false;

    std::sort(scores.begin(), scores.end());

    for (int i = 0; i < scores.size(); ++i) {
        if (scores.size() - i - 1 >= x && scores.size() - i - 1 <= y && i + 1 >= x && i + 1 <= y) {
            m = std::min(scores[i], m);

            exists_m = true;
        }
    }

    if (exists_m) {
        std::cout << m << std::endl;
    } else {
        std::cout << -1 << std::endl;
    }

    return 0;
}