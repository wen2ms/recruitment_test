#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <vector>

int main() {
    int rows_count;
    int cols_count;
    std::cin >> rows_count >> cols_count;
    std::vector<std::vector<char>> grid(rows_count, std::vector<char>(cols_count));
    int source_row;
    int source_col;
    int destination_row;
    int destination_col;
    std::vector<std::pair<int, int>> gates;
    for (int i = 0; i < rows_count; ++i) {
        for (int j = 0; j < cols_count; ++j) {
            std::cin >> grid[i][j];
            if (grid[i][j] == 'S') {
                source_row = i;
                source_col = j;
            }
            if (grid[i][j] == 'E') {
                destination_row = i;
                destination_col = j;
            }
            if (grid[i][j] == '2') {
                gates.emplace_back(i, j);
            }
        }
    }

    std::map<std::pair<int, int>, std::pair<int, int>> gate_pairs;
    for (int i = 0; i < gates.size(); i += 2) {
        gate_pairs[gates[i]] = gates[i + 1];
        gate_pairs[gates[i + 1]] = gates[i];
    }

    std::vector<std::vector<int>> distances(rows_count, std::vector<int>(cols_count, std::numeric_limits<int>::max()));
    std::deque<std::vector<int>> deque;
    distances[source_row][source_col] = 0;
    deque.push_back({0, source_row, source_col});
    const std::vector<std::pair<int, int>> kDirections = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    while (!deque.empty()) {
        int distance = deque.front()[0];
        int row = deque.front()[1];
        int col = deque.front()[2];
        deque.pop_front();

        if (distance > distances[row][col]) {
            continue;
        }

        if (row == destination_row && col == destination_col) {
            std::cout << distance << '\n';
            return 0;
        }
        for (const auto& [row_offset, col_offset] : kDirections) {
            int new_row = row + row_offset;
            int new_col = col + col_offset;
            if (new_row >= 0 && new_row < rows_count && new_col >= 0 && new_col < cols_count && grid[new_row][new_col] != '1') {
                if (distances[row][col] + 1 < distances[new_row][new_col]) {
                    distances[new_row][new_col] = distances[row][col] + 1;
                    deque.push_back({distances[new_row][new_col], new_row, new_col});
                }
            }
        }

        if (grid[row][col] == '2') {
            const auto [gate_row, gate_col] = gate_pairs[{row, col}];
            if (distances[row][col] < distances[gate_row][gate_col]) {
                distances[gate_row][gate_col] = distances[row][col];
                deque.push_front({distances[gate_row][gate_col], gate_row, gate_col});
            }
        }
    }
    std::cout << -1 << '\n';

    return 0;
}