#include <iostream>

// 给一个数求阶乘，阶乘之后求有几个0

int main() {
    int n;

    std::cin >> n;

    int num_zeros = 0;
    while (n >= 5) {
        num_zeros += n / 5;
        n /= 5;
    }

    std::cout << num_zeros << std::endl;

    return 0;
}