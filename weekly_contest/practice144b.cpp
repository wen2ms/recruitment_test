#include <iostream>

int digit_sum(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int main() {
    int total_cases;
    std::cin >> total_cases;
    while (total_cases > 0) {
        --total_cases;
        int left;
        int right;
        std::cin >> left >> right;
        int count = 0;
        int target = -1;
        for (int i = left; i <= right; ++i) {
            if (digit_sum(i) % 13 == 0) {
                ++count;
                if (count == 2) {
                    target = i;
                    break;
                }
            }
        }
        std::cout << target << '\n';
    }

    return 0;
}