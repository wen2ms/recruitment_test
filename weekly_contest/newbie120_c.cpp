#include <iostream>

int main() {
    int total_cases;
    std::cin >> total_cases;
    while (total_cases > 0) {
        --total_cases;
        int len;
        std::cin >> len;
        if ((len & 1) == 1) {
            for (int i = 1; i < len; ++i) {
                std::cout << i << ' ';
            }
            std::cout << len << '\n';
        } else {
            if (len == 2) {
                std::cout << -1 << '\n';
            } else {
                std::cout << 1 << ' ' << 3 << ' ' << 2;
                for (int i = 4; i <= len; ++i) {
                    std::cout << ' ' << i;
                }
                std::cout << '\n';
            }
        }
    }

    return 0;
}