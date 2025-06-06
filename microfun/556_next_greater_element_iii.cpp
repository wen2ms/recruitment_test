#include <iostream>
#include <limits>
#include <string>

class Solution {
  public:
    int nextGreaterElement(int n) {
        std::string str = std::to_string(n);
        int i = str.size() - 1;

        while (i > 0 && str[i - 1] >= str[i]) {
            --i;
        }

        if (i == 0) {
            return -1;
        }

        int j = str.size() - 1;

        while (j > 0 && str[j] <= str[i - 1]) {
            --j;
        }

        std::swap(str[j], str[i - 1]);
        std::reverse(str.begin() + i, str.end());

        long long new_n = std::stoll(str);

        return new_n <= std::numeric_limits<int>::max() ? new_n : -1;
    }
};

int main() {
    Solution solution;

    std::cout << solution.nextGreaterElement(12) << std::endl;

    std::cout << solution.nextGreaterElement(21) << std::endl;

    return 0;
}