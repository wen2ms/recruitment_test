#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int compute_edit_distance(const std::string& str1, const std::string& str2) {
    int len1 = str1.length();
    int len2 = str2.length();
    std::vector<std::vector<int>> distances(len1 + 1, std::vector<int>(len2 + 1));
    for (int i = 1; i <= len1; ++i) {
        distances[i][0] = i;
    }
    for (int i = 1; i <= len2; ++i) {
        distances[0][i] = i;
    }
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                distances[i][j] = distances[i - 1][j - 1];
            } else {
                distances[i][j] = std::min({distances[i - 1][j - 1], distances[i - 1][j], distances[i][j - 1]}) + 1;
            }
        }
    }
    return distances[len1][len2];
}

int main() {
    int limit;
    int size;
    std::cin >> limit >> size;
    std::vector<std::string> strs(size);
    for (std::string& str : strs) {
        std::cin >> str;
    }
    std::string target;
    std::cin >> target;

    for (const std::string& str : strs) {
        if (str == target) {
            std::cout << target << '\n';
            return 0;
        }
    }

    std::vector<std::pair<int, std::string>> edit_distances;
    for (int i = 0; i < size; ++i) {
        int edit_distance = compute_edit_distance(strs[i], target);
        if (edit_distance <= limit) {
            edit_distances.emplace_back(edit_distance, strs[i]);
        }
    }
    std::sort(edit_distances.begin(), edit_distances.end());
    if (edit_distances.empty()) {
        std::cout << "None" << '\n';
    } else {
        std::cout << edit_distances[0].second;
        for (int i = 1; i < edit_distances.size(); ++i) {
            std::cout << ' ' << edit_distances[i].second;
        }
        std::cout << '\n';
    }

    return 0;
}