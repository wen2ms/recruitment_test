#include <string.h>

#include <iostream>

// 计算将红（R）、黄（Y）、蓝（B）三种颜色的球放入一个长度为 n
// 的序列中，使得任何连续的三个球都不能构成红黄蓝三种颜色的某种排列（即不允许出现红、黄、蓝三种颜色各一次且不重复的连续三元组）。

int main() {
    int n;

    std::cin >> n;

    if (n == 1) {
        std::cout << 3 << std::endl;
        
        return 0;
    }


    int last_two_ball[n + 1][3][3];

    memset(last_two_ball, 0, sizeof(last_two_ball));

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            last_two_ball[2][i][j] = 1;
        }
    }

    for (int t = 3; t <= n; ++t) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 3; ++k) {
                    if (i == j || j == k || i == k) {
                        last_two_ball[t][j][k] += last_two_ball[t - 1][i][j];
                    }
                }
            }
        }
    }

    int total = 0;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            total += last_two_ball[n][i][j];    
        }
    }

    std::cout << total << std::endl;

    return 0;
}