#include <iostream>
#include <unordered_map>
#include <vector>

// 数组中所有只出现一次的元素的和

int main() {
    std::vector<int> nums = {1, 2, 2, 3, 4, 4, 5};

    std::unordered_map<int, int> counts;

    for (int num : nums) {
        ++counts[num];
    }

    int sum = 0;

    for (const auto& [num, count] : counts) {
        if (count == 1) {
            sum += num;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}