#include <algorithm>
#include <iostream>
#include <vector>

// 有一个蛇长度为l，一个数组里面是苹果高度，l大于苹果高度就能吃，吃完l+1，求最后蛇的长度

int main() {
    int l, n;

    std::cin >> l >> n;

    std::vector<int> apple_height;

    int tmp = -1;
    for (int i = 0; i < n; ++i) {
        std::cin >> tmp;
        apple_height.push_back(tmp);
    }

    std::sort(apple_height.begin(), apple_height.end());

    for (int i = 0; i < apple_height.size(); ++i) {
        if (apple_height[i] < l) {
            l++;
        } else {
            break;
        }
    }

    std::cout << l << std::endl;

    return 0;
}