#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::pair<int, int>> parse_ranges_str(const std::string& ranges_str) {
    std::vector<std::pair<int, int>> ranges;
    std::stringstream stream(ranges_str);
    std::string segment;
    while (std::getline(stream, segment, ',')) {
        int dash_pos = segment.find('-');
        if (dash_pos != std::string::npos) {
            int start = std::stoi(segment.substr(0, dash_pos));
            int end = std::stoi(segment.substr(dash_pos + 1));
            ranges.emplace_back(start, end);
        } else {
            int value = std::stoi(segment);
            ranges.emplace_back(value, value);
        }
    }
    return ranges;
}

void merge_intervals(std::vector<std::pair<int, int>>& intervals) {
    if (intervals.empty()) {
        return;
    }
    std::sort(intervals.begin(), intervals.end());
    std::vector<std::pair<int, int>> merged;
    merged.push_back(intervals[0]);
    int size = intervals.size();
    for (int i = 1; i < size; ++i) {
        const auto& [start, end] = intervals[i];
        if (start <= merged.back().second + 1) {
            merged.back().second = std::max(merged.back().second, end);
        } else {
            merged.push_back(intervals[i]);
        }
    }
    intervals = merged;
}

int main() {
    int size;
    std::cin >> size;
    std::string line;
    std::getline(std::cin, line);
    std::vector<std::pair<int, int>> enabled_intervals;
    for (int i = 0; i < size; ++i) {
        std::getline(std::cin, line);
        std::stringstream stream(line);
        std::string type;
        std::string keyword;
        std::string ranges_str;
        stream >> type;
        if (type == "undo") {
            stream >> keyword >> ranges_str;
        } else {
            stream >> ranges_str;
        }
        std::vector<std::pair<int, int>> ranges = parse_ranges_str(ranges_str);

        if (type == "algorithm") {
            enabled_intervals.insert(enabled_intervals.end(), ranges.begin(), ranges.end());
            merge_intervals(enabled_intervals);
        } else {
            std::vector<std::pair<int, int>> next_enabled;
            for (const auto& enabled : enabled_intervals) {
                std::vector<std::pair<int, int>> pieces;
                pieces.push_back(enabled);

                for (const auto& undo : ranges) {
                    std::vector<std::pair<int, int>> new_pieces;
                    for (const auto& piece : pieces) {
                        if (piece.second < undo.first || piece.first > undo.second) {
                            new_pieces.push_back(piece);
                            continue;
                        }
                        if (piece.first < undo.first) {
                            new_pieces.emplace_back(piece.first, undo.first - 1);
                        }
                        if (piece.second > undo.second) {
                            new_pieces.emplace_back(undo.second + 1, piece.second);
                        }
                    }
                    pieces = new_pieces;
                }
                next_enabled.insert(next_enabled.end(), pieces.begin(), pieces.end());
            }
            enabled_intervals = next_enabled;
            merge_intervals(enabled_intervals);
        }
    }

    if (!enabled_intervals.empty()) {
        for (int i = 0; i < enabled_intervals.size(); ++i) {
            if (enabled_intervals[i].first == enabled_intervals[i].second) {
                std::cout << enabled_intervals[i].first;
            } else {
                std::cout << enabled_intervals[i].first << '-' << enabled_intervals[i].second;
            }
            if (i < enabled_intervals.size() - 1) {
                std::cout << ',';
            }
        }
        std::cout << '\n';
    }

    return 0;
}