#include <iostream>
#include <vector>

// 降序的子数组最大元素和
// 给你一个正整数组成的数组nums，返回nums中一个降序子数组的最大可能元素和。
// 输入
// [50,10,20,30,5,10]
// 输出
// 60
// 说明
// [50,10]是元素和最大的降序子数组，最大元素和为60。

int main() {
    std::vector<int> nums = {50, 30, 20};

    int n = nums.size();
    int maximum_desc_sum = nums[0];
    int curr_sum = nums[0];

    for (int i = 1; i < n; ++i) {
        if (nums[i] < nums[i - 1]) {
            curr_sum += nums[i];
        } else {
            maximum_desc_sum = std::max(maximum_desc_sum, curr_sum);
            curr_sum = nums[i];
        }
    }

    maximum_desc_sum = std::max(maximum_desc_sum, curr_sum);

    std::cout << maximum_desc_sum << std::endl;

    return 0;
}