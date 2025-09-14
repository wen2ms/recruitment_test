#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

int main() {
    int count1;
    int count2;
    std::cin >> count1 >> count2;
    std::vector<int> nums1(count1);
    std::unordered_set<int> set1;
    for (int& num : nums1) {
        std::cin >> num;
        set1.insert(num);
    }
    std::sort(nums1.begin(), nums1.end());
    std::unordered_set<int> candidates;
    for (const int num : nums1) {
        if (num > 1 && !set1.contains(num - 1)) {
            candidates.insert(num - 1);
        }
    }
    for (const int num : nums1) {
        if (num < count1 + count2 && !set1.contains(num + 1)) {
            for (int candidate : candidates) {
                if (candidate != num + 1 && candidate + 1 != num) {
                    std::cout << num << ' ' << candidate + 1 << ' ' << num + 1 << ' ' << candidate << '\n';
                    return 0;
                }
            }
        }
    }
    std::cout << -1 << '\n';

    return 0;
}