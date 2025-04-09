#include <iostream>
#include <vector>

int main() {
    int n;

    std::cin >> n;
    while (n != 0) {
        int total = 0;
        while (n >= 3) {
            total += n / 3;
            n = n % 3 + n / 3;
        }

        if (n == 2) {
            total++;
        }

        std::cout << total << std::endl;

        std::cin >> n;
    }

    return 0;
}