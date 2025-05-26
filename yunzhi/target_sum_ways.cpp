#include <iostream>
#include <vector>

// 给定一个数组和一个目标值 S，给数组中的每个数添加 + 或 - 号，使最终表达式的结果等于 S，问有多少种不同的添加方式

int find_target_sum_ways(const std::vector<int>& nums, int s) {
    int total = 0;
    for (int i = 0; i < nums.size(); ++i) {
        total += nums[i];
    }

    if ((s + total) % 2 != 0 || total < std::abs(s)) {
        return 0;
    }

    int target = (s + total) / 2;

    std::vector<int> sum_ways(target + 1, 0);

    sum_ways[0] = 1;
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = target; j >= nums[i]; --j) {
            sum_ways[j] += sum_ways[j - nums[i]];
        }
    }

    return sum_ways[target];
}

int main() {
    std::cout << find_target_sum_ways({1, 1, 1, 1, 1}, 3) << std::endl;

    return 0;
}