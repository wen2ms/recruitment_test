#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int find_closing_bracket(const std::string& str, int start, char open, char close) {
    int level = 0;
    int len = str.length();
    for (int i = start; i < len; ++i) {
        if (str[i] == open) {
            ++level;
        }
        if (str[i] == close) {
            --level;
        }
        if (level == 0) {
            return i;
        }
    }
    return -1;
}

std::unordered_map<std::string, int> solve(const std::string& str,
                                           std::unordered_map<std::string, std::unordered_map<std::string, int>>& memo) {
    auto iter = memo.find(str);
    if (iter != memo.end()) {
        return iter->second;
    }
    std::unordered_map<std::string, int> counts;
    int pos = 0;
    int len = str.length();
    while (pos < len) {
        if (std::isspace(str[pos]) != 0) {
            ++pos;
            continue;
        }

        if (std::isalpha(str[pos]) != 0) {
            std::string keyword;
            while (pos < len && (std::isalpha(str[pos]) != 0)) {
                keyword += str[pos];
                ++pos;
            }
            ++counts[keyword];
        } else if (str[pos] == '{') {
            int end = find_closing_bracket(str, pos, '{', '}');
            std::string content = str.substr(pos + 1, end - pos - 1);
            std::vector<std::string> options;
            int left = 0;
            int level = 0;
            for (int right = 0; right < content.length(); ++right) {
                if (content[right] == '{' || content[right] == '[') {
                    ++level;
                } else if (content[right] == '}' || content[right] == ']') {
                    --level;
                } else if (content[right] == '|' && level == 0) {
                    options.push_back(content.substr(left, right - left));
                    left = right + 1;
                }
            }
            options.push_back(content.substr(left));

            if (!options.empty()) {
                std::vector<std::unordered_map<std::string, int>> options_counts;
                options_counts.reserve(options.size());
                for (const std::string& option : options) {
                    options_counts.push_back(solve(option, memo));
                }
                for (const auto& [key, val] : options_counts[0]) {
                    if (val > 0) {
                        bool in_all = true;
                        for (int i = 1; i < options_counts.size(); ++i) {
                            if (options_counts[i].find(key) == options_counts[i].end()) {
                                in_all = false;
                                break;
                            }
                        }
                        if (in_all) {
                            ++counts[key];
                        }
                    }
                }
            }
            pos = end + 1;
        } else if (str[pos] == '[') {
            pos = find_closing_bracket(str, pos, '[', ']') + 1;
        } else {
            ++pos;
        }
    }
    memo[str] = counts;
    return memo[str];
}

int main() {
    std::string str;
    std::getline(std::cin, str);
    std::vector<std::string> fixed_keywords;
    int level = 0;
    int pos = 0;
    int len = str.length();
    while (pos < len) {
        if (std::isspace(str[pos]) != 0) {
            ++pos;
            continue;
        }
        if (str[pos] == '{' || str[pos] == '[') {
            ++level;
            ++pos;
        } else if (str[pos] == '}' || str[pos] == ']') {
            --level;
            ++pos;
        } else if (std::isalpha(str[pos]) != 0 && level == 0) {
            std::string keyword;
            while (pos < len && (std::isalpha(str[pos]) != 0)) {
                keyword += str[pos];
                ++pos;
            }
            fixed_keywords.push_back(keyword);
        } else {
            ++pos;
        }
    }
    std::unordered_map<std::string, std::unordered_map<std::string, int>> memo;
    std::unordered_map<std::string, int> total_counts = solve(str, memo);

    for (int i = 0; i < fixed_keywords.size(); ++i) {
        std::cout << fixed_keywords[i] << (i == fixed_keywords.size() - 1 ? '\n' : ' ');
    }
    for (int i = 0; i < fixed_keywords.size(); ++i) {
        auto iter = total_counts.find(fixed_keywords[i]);
        if (iter != total_counts.end()) {
            std::cout << iter->second;
        } else {
            std::cout << 0;
        }

        std::cout << (i == fixed_keywords.size() - 1 ? '\n' : ' ');
    }

    return 0;
}