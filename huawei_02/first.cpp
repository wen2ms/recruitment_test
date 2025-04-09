#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

int main()
{    
    int n;
    
    std::cin >> n;
    std::map<std::string, std::string> input_versions;
    
    for (int i = 0; i < n; ++i) {
        std::string current_verison, prev_version;
        std::cin >> current_verison >> prev_version;

        input_versions.insert({current_verison, prev_version});
    }

    std::map<std::string, int> iterator_counts;
    for (auto it = input_versions.begin(); it != input_versions.end(); ++it) {
        if (it->second == "NA") {
            iterator_counts.insert({it->first, 0});
        } else {
            iterator_counts.insert({it->first, 1});
        }
    }

    for (auto it = input_versions.begin(); it != input_versions.end(); ++it) {
        std::string key = it->second;
        while (key != "NA") {
            iterator_counts[it->first] += iterator_counts[key];
            key = input_versions[key];
        }
    }

    int max_count = -1;
    std::vector<std::string> result;
    for (auto it = iterator_counts.begin(); it != iterator_counts.end(); ++it) {
        if (it->second > max_count) {
            max_count = it->second;
        }
    }

    for (auto it = iterator_counts.begin(); it != iterator_counts.end(); ++it) {
        if (it->second == max_count) {
            result.push_back(it->first);
        }
    }

    if (result.size() == 1) {
        std::cout << result[0] << std::endl;
    } else {
        for (int i = 0; i < result.size() - 1; ++i) {
            std::cout << result[i] << ' ';
        }

        std::cout << result.back() << std::endl;
    }

    return 0;
}
