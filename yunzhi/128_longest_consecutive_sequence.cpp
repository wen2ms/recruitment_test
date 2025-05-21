#include <iostream>
#include <unordered_set>
#include <vector>

int longest_consecutive(std::vector<int>& nums) {
    int n = nums.size();
    std::unordered_set<int> nums_set(nums.begin(), nums.end());

    int max_length = 0;
    for (auto it = nums_set.begin(); it != nums_set.end(); ++it) {
        if (nums_set.find(*it - 1) == nums_set.end()) {
            int current_length = 1;
            while (nums_set.find(*it + current_length) != nums_set.end()) {
                ++current_length;
            }

            max_length = std::max(max_length, current_length);
        }
    }

    return max_length;
}

int main() {
    std::vector<int> case_1 = {100, 4, 200, 1, 3, 2};
    std::vector<int> case_2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    std::vector<int> case_3 = {1, 0, 1, 2};

    std::cout << longest_consecutive(case_1) << std::endl;

    std::cout << longest_consecutive(case_2) << std::endl;

    std::cout << longest_consecutive(case_3) << std::endl;

    return 0;
}