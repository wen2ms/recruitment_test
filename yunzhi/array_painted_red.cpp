#include <iostream>
#include <vector>

// 数组涂红
// 输入一个整数数组，小红每次涂红其中的几个数，求未涂红的数的和。
// 第一行的两个数 n，k 分别表示数组长度和涂红的个数，第二行为整数数组，第三行为涂红的序号（从 1 开始）。
// 例如，输入：
// 5 2
// 2 5 1 8 4
// 1 3
// 输出：17
// 解释：第 1 个和第 3 个数涂红，则不涂红的数的和为 5 + 8 + 4 = 17。

int main() {
    int n, k;

    std::cin >> n >> k;

    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }

    std::vector<bool> is_red(n, false);
    for (int i = 0; i < k; ++i) {
        int index;
        std::cin >> index;
        is_red[index - 1] = true;
    }

    int sum = 0;
    for (int i = 0; i < n; ++i) {
        if (!is_red[i]) {
            sum += nums[i];
        }
    }

    std::cout << sum << std::endl;

    return 0;
}