#include <iostream>
#include <unordered_map>
#include <vector>

// 在数组中找到一对 (i, j)（i < j），使得 A[i] ≡ A[j] mod m，并且 j - i 最大。

int main() {
    std::vector<int> nums = {3, 1, 7, 5, 11};
    int m = 4;

    std::unordered_map<int, int> remainder_index;
    int maximum_length = -1;

    for (int i = 0; i < nums.size(); ++i) {
        int r = nums[i] % m;
        auto it = remainder_index.find(r);

        if (it != remainder_index.end()) {
            maximum_length = std::max(maximum_length, i - it->second);
        } else {
            remainder_index.insert(std::pair(r, i));
        }
    }

    std::cout << maximum_length << std::endl;

    return 0;
}
