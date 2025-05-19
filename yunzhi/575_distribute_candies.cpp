#include <iostream>
#include <unordered_set>
#include <vector>

class Solution {
  public:
    int distributeCandies(std::vector<int>& candyType) {
        std::unordered_set<int> candy_set(candyType.begin(), candyType.end());

        return std::min(candy_set.size(), candyType.size() / 2);
    }
};

int main() {
    std::vector<int> case_1 = {1, 1, 2, 2, 3, 3};
    std::vector<int> case_2 = {1, 1, 2, 3};
    std::vector<int> case_3 = {6, 6, 6, 6};

    Solution solution;

    std::cout << solution.distributeCandies(case_1) << std::endl;

    std::cout << solution.distributeCandies(case_2) << std::endl;

    std::cout << solution.distributeCandies(case_3) << std::endl;

    return 0;
}