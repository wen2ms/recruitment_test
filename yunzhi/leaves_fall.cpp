#include <iostream>

int main() {
    int n, m, p, q;

    std::cin >> n >> m >> p >> q;

    int num_month = 0;
    while (n > 0) {
        num_month++;

        int current_month = (num_month - 1) % 12 + 1;
        if (current_month >= p && current_month < p + q) {
            n -= 2 * m;
        } else {
            n -= m;
        }
    }

    std::cout << num_month << std::endl;

    return 0;
}