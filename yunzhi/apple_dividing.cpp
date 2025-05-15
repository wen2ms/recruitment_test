#include <iostream>
#include <vector>

// 有 m 个苹果，n 个小孩，每个小孩至少一个苹果, 相邻编号的孩子（如编号 i 和 i+1）苹果数目差距 ≤ 1； 小明编号为k
// 要使他分到最多的苹果。

int sum_side(int x, int len) {
    if (len <= x - 1) {
        return (x - 1 + x - len) * len / 2;
    } else {
        return (x - 1) * x / 2 + (len - (x - 1));
    }
}

int main() {
    int m, n, k;
    std::cin >> m >> n >> k;

    int left = 1, right = m, max_count = 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (mid + sum_side(mid, k - 1) + sum_side(mid, n - k) <= m) {
            max_count = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    std::cout << max_count << std::endl;

    return 0;
}