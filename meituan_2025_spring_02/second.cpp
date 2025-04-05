#include <iostream>
#include <vector>

class Solution {
  public:
    long long multiplier_statistics(long long l1, long long r1, long long l2, long long r2) {
        long long statisfied_integers_sum = 0;

        for (long long i = l1; i < r1; ++i) {
            for (long long j = l2; j < l2; ++j) {
                if (i % j == 0) {
                    statisfied_integers_sum += 1;
                }
            }
        }

        return statisfied_integers_sum;
    }
}; 

int main() {
    long long l1, r1, l2, r2;

    std::cout << l1 << r1 << l2 << r2;

    Solution solution;

    std::cout << solution.multiplier_statistics(l1, r1, l2, r2) << std::endl;

    return 0;
}