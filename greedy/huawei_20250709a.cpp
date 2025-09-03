#include <iostream>
#include <vector>

int main() {
    int count;
    std::cin >> count;

    std::vector<int> nums(count);
    for (int& num : nums) {
        std::cin >> num;
    }

    int result = 0;
    for (int i = 0; i < count; ++i) {
        if (nums[i] == 1) {
            bool left_has = (i > 0 && nums[i - 1] == 2);
            bool right_has = (i < count - 1 && nums[i + 1] == 2);
            if (!left_has && !right_has) {
                if (i < count - 1 && nums[i + 1] == 0) {
                    ++result;
                    nums[i + 1] = 2;
                } else if (i > 0 && nums[i - 1] == 0) {
                    ++result;
                    nums[i - 1] = 2;
                } else {
                    std::cout << -1 << '\n';
                    return 0;
                }
            }
        }
    }

    std::cout << result << '\n';

    return 0;
}