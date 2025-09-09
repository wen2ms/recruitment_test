#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int num_of_tasks;
    int num_of_segments;
    std::cin >> num_of_tasks >> num_of_segments;
    std::vector<int> tasks(num_of_tasks);
    for (int& task : tasks) {
        std::cin >> task;
    }
    std::vector<int> prefix_sum(num_of_tasks + 1);
    for (int i = 1; i <= num_of_tasks; ++i) {
        prefix_sum[i] = tasks[i - 1] + prefix_sum[i - 1];
    }
    std::vector<std::vector<int>> min_squares(num_of_tasks + 1, std::vector<int>(num_of_segments + 1, -1));
    std::vector<std::vector<int>> path(num_of_tasks + 1, std::vector<int>(num_of_segments + 1));
    min_squares[0][0] = 0;
    for (int j = 1; j <= num_of_segments; ++j) {
        for (int i = j; i <= num_of_tasks; ++i) {
            for (int k = j - 1; k < i; ++k) {
                if (min_squares[k][j - 1] == -1) {
                    continue;
                }
                int cost = prefix_sum[i] - prefix_sum[k];
                int value = min_squares[k][j - 1] + cost * cost;
                if (min_squares[i][j] == -1 || value < min_squares[i][j]) {
                    min_squares[i][j] = value;
                    path[i][j] = k;
                }
            }
        }
    }
    std::vector<int> result;
    int current = num_of_tasks;
    for (int i = num_of_segments; i > 0; --i) {
        int prev = path[current][i];
        result.push_back(current - prev);
        current = prev;
    }
    std::reverse(result.begin(), result.end());
    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i] << " \n"[i == result.size() - 1 ? 1 : 0];
    }

    return 0;
}