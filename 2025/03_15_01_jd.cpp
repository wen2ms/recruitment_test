#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
  public:
    int optimize_deletor(std::vector<int>& integers, int integers_count) {
        std::sort(integers.begin(), integers.end());

        int deleted_max = integers[integers_count - 2] - integers[0];
        int deleted_min = integers[integers_count - 1] - integers[1];

        return std::min(deleted_max, deleted_min);
    }
};

int main() {
    int case_count;

    std::cin >> case_count;
    for (int i = 0; i < case_count; ++i) {
        int integers_count;
        std::vector<int> integers;

        std::cin >> integers_count;
        for (int j = 0; j < integers_count; ++j) {
            int input_integer;

            std::cin >> input_integer;
            integers.push_back(input_integer);
        }

        Solution solution;

        std::cout << solution.optimize_deletor(integers, integers_count) << std::endl;
    }

    return 0;
}