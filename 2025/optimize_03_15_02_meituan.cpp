#include <iostream>
#include <vector>

class Solution {
  public:
    long long multiplier_statistics(long long l1, long long r1, long long l2, long long r2) {
        long long satisfied_integers_sum = 0;

        long long left = l2;
        while (left <= r2) {
            long long k1 = r1 / left;
            long long k2 = (l1 - 1) / left;
            long long multipliers_count = k1 - k2;

            long long k1_high = (k1 == 0) ? r2 : r1 / k1;
            long long k2_high = (k2 == 0) ? r2 : (l1 - 1) / k2;
            long long right = std::min({r2, k1_high, k2_high});

            satisfied_integers_sum += multipliers_count * (right - left + 1);

            left = right + 1;
        }

        return satisfied_integers_sum;
    }
}; 

int main() {
    long long l1, r1, l2, r2;

    std::cin >> l1 >> r1 >> l2 >> r2;

    Solution solution;

    std::cout << solution.multiplier_statistics(l1, r1, l2, r2) << std::endl;

    return 0;
}