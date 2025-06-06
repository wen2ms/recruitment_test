#include <iostream>
#include <vector>

class Solution {
  public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> all_combinations;

        std::vector<int> current_combination;

        generate_all_combinations(all_combinations, 0, current_combination, 0, candidates, target);

        return all_combinations;
    }

  private:
    void generate_all_combinations(std::vector<std::vector<int>>& all_combinations, int current_index,
                                   std::vector<int>& current_combination, int current_sum, const std::vector<int>& candidates,
                                   const int target) {
        if (current_sum == target) {
            all_combinations.push_back(current_combination);
            return;
        }

        if (current_sum > target || current_index >= candidates.size()) {
            return;
        }

        current_combination.push_back(candidates[current_index]);

        generate_all_combinations(all_combinations, current_index, current_combination, current_sum + candidates[current_index],
                                  candidates, target);

        current_combination.pop_back();

        generate_all_combinations(all_combinations, current_index + 1, current_combination, current_sum, candidates, target);
    }
};

void print_vector(const std::vector<std::vector<int>>& items) {
    for (int i = 0; i < items.size(); ++i) {
        for (int j = 0; j < items[i].size(); ++j) {
            std::cout << items[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> case_1 = {2, 3, 6, 7};
    std::vector<int> case_2 = {2, 3, 5};
    std::vector<int> case_3 = {2};

    Solution solution;

    print_vector(solution.combinationSum(case_1, 7));

    print_vector(solution.combinationSum(case_2, 8));

    print_vector(solution.combinationSum(case_3, 1));

    return 0;
}