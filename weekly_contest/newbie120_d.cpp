#include <iostream>
#include <vector>

int binary_search(int num1, int num2) {
    int low = 0;
    int high = 32;
    int exponent;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (num1 * (1 << mid) >= num2) {
            exponent = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return exponent;
}

void solve() {
    int size1;
    int size2;
    std::cin >> size1 >> size2;
    std::vector<int> nums1(size1);
    std::vector<int> nums2(size2);
    for (int& num : nums1) {
        std::cin >> num;
    }
    for (int& num : nums2) {
        std::cin >> num;
    }

    if (size1 > size2) {
        std::cout << -1 << '\n';
        return;
    }
    int index1 = 0;
    int index2 = 0;
    int result = -1;
    while (index2 < size2) {
        if (nums1[index1] != nums2[index2]) {
            std::cout << -1 << '\n';
            return;
        }
        int start1 = index1;
        int start2 = index2;
        while (index1 < size1 - 1 && nums1[index1] == nums1[index1 + 1]) {
            ++index1;
        }
        while (index2 < size2 - 1 && nums2[index2] == nums2[index2 + 1]) {
            ++index2;
        }
        int offset1 = index1 - start1 + 1;
        int offset2 = index2 - start2 + 1;
        if (offset1 > offset2) {
            std::cout << -1 << '\n';
            return;
        }
        result = std::max(result, binary_search(offset1, offset2));
        ++index1;
        ++index2;
        if (index1 >= size1 && index2 < size2) {
            std::cout << -1 << '\n';
            return;
        }
    }
    std::cout << result << '\n';
}

int main() {
    int total_cases;
    std::cin >> total_cases;

    while (total_cases > 0) {
        --total_cases;
        solve();
    }

    return 0;
}