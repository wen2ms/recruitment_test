#include <iostream>
#include <string>

class Solution {
  public:
    int maximumSwap(int num) {
        std::string str = std::to_string(num);
        int n = str.size();

        int max_pos = -1, max_digit = -1;
        int left_pos = -1, right_pos = -1;

        for (int i = n - 1; i >= 0; --i) {
            if (str[i] > max_digit) {
                max_digit = str[i];
                max_pos = i;

                continue;
            }

            if (str[i] < max_digit) {
                left_pos = i;
                right_pos = max_pos;
            }
        }

        if (left_pos == -1) {
            return num;
        }

        std::swap(str[left_pos], str[right_pos]);

        return std::stoi(str);
    }
};

int main() {
    Solution solution;

    std::cout << solution.maximumSwap(2736) << std::endl;

    std::cout << solution.maximumSwap(9973) << std::endl;

    return 0;
}