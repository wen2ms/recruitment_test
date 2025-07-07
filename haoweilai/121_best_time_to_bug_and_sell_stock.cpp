#include <iostream>
#include <vector>

class Solution {
  public:
    int maxProfit(std::vector<int>& prices) {
        int price_buy = prices[0];
        int profit = 0;

        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] < price_buy) {
                price_buy = prices[i];
            } else if (prices[i] - price_buy > profit) {
                profit = prices[i] - price_buy;
            }
        }

        return profit;
    }
};

int main() {
    std::vector<int> case_1 = {7, 1, 5, 3, 6, 4};
    std::vector<int> case_2 = {7, 6, 4, 3, 1};

    Solution solution;

    std::cout << solution.maxProfit(case_1) << std::endl;

    std::cout << solution.maxProfit(case_2) << std::endl;

    return 0;
}