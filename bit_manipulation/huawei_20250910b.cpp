#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int64_t parse_id(const std::string& str) {
    int64_t result = 0;
    std::stringstream stream(str);
    std::string segment;
    while (std::getline(stream, segment, '-')) {
        result = (result << 8) + std::stoll(segment, nullptr, 16);
    }
    return result;
}

int main() {
    int num_of_rules;
    std::cin >> num_of_rules;
    std::vector<std::pair<int64_t, int>> rules(num_of_rules);
    for (auto& [rule_id, range] : rules) {
        std::string rule_str;
        std::cin >> rule_str;
        int slash_pos = rule_str.find('/');

        std::string id_str = rule_str.substr(0, slash_pos);
        range = std::stoi(rule_str.substr(slash_pos + 1));
        rule_id = parse_id(id_str);
    }

    int num_of_ids;
    std::cin >> num_of_ids;
    while (num_of_ids > 0) {
        --num_of_ids;
        std::string agent_id_str;
        std::cin >> agent_id_str;
        int64_t agent_id = parse_id(agent_id_str);
        bool valid = false;
        for (const auto& [rule_id, range] : rules) {
            if (range == 0) {
                valid = true;
                break;
            }
            if ((agent_id >> (48 - range)) == (rule_id >> (48 - range))) {
                valid = true;
                break;
            }
        }

        std::cout << (valid ? "YES" : "NO") << '\n';
    }

    return 0;
}