#include <iostream>

int main() {
    int total_cases;
    std::cin >> total_cases;
    while (total_cases > 0) {
        --total_cases;
        int num;
        std::cin >> num;
        if (num == 1 || num == 2 || num == 3) {
            std::cout << -1 << '\n';
            continue;
        }
        if (num % 2 == 1) {
            std::cout << 1 << '\n';
        } else {
            std::cout << 2 << '\n';
        }
    }
    return 0;
}