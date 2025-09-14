#include <iostream>

int main() {
    int total_cases;
    std::cin >> total_cases;
    while (total_cases > 0) {
        --total_cases;
        int num;
        std::cin >> num;
        std::cout << num << '\n';
    }

    return 0;
}