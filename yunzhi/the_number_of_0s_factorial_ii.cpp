#include <iostream>

// 给一个数求阶乘，阶乘之后求有几个0

int main() {
    int n;

    std::cin >> n;

    long long factorial = 1;
    for (int i = 2; i <= n; ++i) {
        factorial *= i;
    }

    int num_zeros = 0;
    while (factorial > 0) {
        if (factorial % 10 == 0) {
            num_zeros++;
        }

        factorial /= 10;
    }

    std::cout << num_zeros << std::endl;

    return 0;
}