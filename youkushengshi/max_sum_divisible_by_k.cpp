#include <iostream>
#include <vector>

// 给定一个数组 A 和一个整数 K，从数组中选择任意多个元素（至少一个），使它们的和是 K 的倍数，并且这个和尽可能大。输出这个最大值。
// 数组：A = [3, 1, 4, 1, 5, 9]
// K = 3
// 最大和为 24（3+1+4+1+5+9+1）是 3 的倍数

int main() {
    int n;

    std::cin >> n;

    std::vector<int> nums(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }

    int k;

    std::cin >> k;

    std::vector<int> max_sum_remainder(k, -1);

    max_sum_remainder[0] = 0;

    for (int num : nums) {
        std::vector<int> tmp = max_sum_remainder;
        for (int r = 0; r < k; ++r) {
            if (max_sum_remainder[r] != -1) {
                int new_r = (r + num) % k;
                tmp[new_r] = std::max(tmp[new_r], max_sum_remainder[r] + num);
            }
        }

        max_sum_remainder = tmp;
    }

    std::cout << max_sum_remainder[0] << std::endl;

    return 0;
}