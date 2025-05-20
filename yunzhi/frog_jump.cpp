#include <iostream>
#include <vector>

// 有一只青蛙，一次可以跳1、2、...、n级台阶，要求这个青蛙要跳到n及台阶一共有多少种跳法

int main() {
    int n;

    std::cin >> n;

    std::vector<int> methods_count(n + 1, 0);

    methods_count[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            methods_count[i] += methods_count[j];
        }
    }

    std::cout << methods_count[n] << std::endl;

    return 0;
}