#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Solution {
  public:
    std::vector<int> grayCode(int n) {
        std::vector<int> codes;
        int size = 1 << n;

        for (int i = 0; i < size; ++i) {
            codes.push_back(i ^ (i >> 1));
        }

        return codes;
    }
};

void print_nums(const std::vector<int>& nums) {
    for (int num : nums) {
        std::cout << num << ' ';
    }
    std::cout << std::endl;
}

int main() {
    Solution solution;

    print_nums(solution.grayCode(2));

    print_nums(solution.grayCode(1));

    return 0;
}