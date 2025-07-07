#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

class Solution {
  public:
    int findRadius(std::vector<int>& houses, std::vector<int>& heaters) {
        std::sort(houses.begin(), houses.end());
        std::sort(heaters.begin(), heaters.end());

        int m = houses.size();
        int n = heaters.size();
        std::vector<int> distances(m, std::numeric_limits<int>::max());

        int i = 0;
        int j = 0;
        while (i < m && j < n) {
            if (houses[i] <= heaters[j]) {
                distances[i] = heaters[j] - houses[i];

                ++i;
            } else {
                ++j;
            }
        }

        i = m - 1;
        j = n - 1;
        while (i >= 0 && j >= 0) {
            if (houses[i] >= heaters[j]) {
                distances[i] = std::min(distances[i], houses[i] - heaters[j]);

                --i;
            } else {
                --j;
            }
        }

        return *std::max_element(distances.begin(), distances.end());
    }
};

int main() {
    std::vector<int> case_1_houses = {1, 2, 3};
    std::vector<int> case_1_heaters = {2};

    std::vector<int> case_2_houses = {1, 2, 3, 4};
    std::vector<int> case_2_heaters = {1, 4};

    std::vector<int> case_3_houses = {1, 5};
    std::vector<int> case_3_heaters = {2};

    Solution solution;

    std::cout << solution.findRadius(case_1_houses, case_1_heaters) << std::endl;

    std::cout << solution.findRadius(case_2_houses, case_2_heaters) << std::endl;

    std::cout << solution.findRadius(case_3_houses, case_3_heaters) << std::endl;

    return 0;
}