#include <iostream>

// 输入n、m、p、q，n为一颗树上的叶子数，m为每月掉落的叶子数，p为大风期开始的月数，q为大风期持续的月数，大风期期间叶子掉落数为每月2*m，输出叶子全部掉落需要多少月。

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