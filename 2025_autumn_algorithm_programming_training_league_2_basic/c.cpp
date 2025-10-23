#include <array>
#include <cstdint>
#include <iostream>

const int kMod = 1e9 + 1011;

int64_t fast_pow(int64_t base, int64_t exp) {
    int64_t result = 1;
    while (exp > 0) {
        if ((exp & 1) == 1) {
            result = result * base % kMod;
        }
        base = (base * base) % kMod;
        exp >>= 1;
    }
    return result;
}

int main() {
    int total_cases;
    std::cin >> total_cases;
    while (total_cases > 0) {
        --total_cases;
        std::array<int64_t, 7> nums;
        for (int64_t& num : nums) {
            std::cin >> num;
        }
        int64_t sum = fast_pow(nums[0], nums[3]) + fast_pow(nums[1], nums[4]) + +fast_pow(nums[2], nums[5]);
        if (sum != nums[6]) {
            std::cout << "No" << '\n';
        } else {
            std::cout << "Yes" << '\n';
        }
    }

    return 0;
}