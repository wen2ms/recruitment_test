#include <array>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct PathInfo {
    std::vector<std::array<int, 3>> scores;
    std::vector<std::pair<int, int>> path;
    bool operator<(const PathInfo& other) const {
        return scores < other.scores;
    }
};

void parse_line_to_set(const std::string& line, std::set<int>& set) {
    std::stringstream stream(line);
    int num;
    while (stream >> num) {
        set.insert(num);
    }
}

void parse_ley_lines(const std::string& line, std::set<std::pair<int, int>>& container) {
    if (line == "0") {
        return;
    }
    std::stringstream stream(line);
    std::string pair_str;
    while (stream >> pair_str) {
        int dash_pos = pair_str.find('-');
        int start = std::stoi(pair_str.substr(0, dash_pos));
        int end = std::stoi(pair_str.substr(dash_pos + 1));
        container.emplace(std::min(start, end), std::max(start, end));
    }
}

void parse_bridges(const std::string& line, std::map<int, std::vector<int>>& container) {
    if (line == "0") {
        return;
    }
    std::stringstream stream(line);
    std::string pair_str;
    while (stream >> pair_str) {
        int dash_pos = pair_str.find('-');
        int start = std::stoi(pair_str.substr(0, dash_pos));
        int end = std::stoi(pair_str.substr(dash_pos + 1));
        container[start].push_back(end);
    }
}

std::array<int, 3> calculate_score(int in_port, int out_port, const std::set<std::pair<int, int>>& leys) {
    int is_new = 1;
    if (leys.contains({std::min(in_port, out_port), std::max(in_port, out_port)})) {
        is_new = 0;
    }
    return {{is_new, in_port + out_port, in_port}};
}

int main() {
    int num_of_stones;
    std::string line;
    std::getline(std::cin, line);
    num_of_stones = std::stoi(line);

    std::vector<std::set<int>> inscriptions(num_of_stones);
    std::vector<std::set<std::pair<int, int>>> ley_lines(num_of_stones);
    std::vector<std::set<int>> occupied_ports(num_of_stones);
    std::vector<std::map<int, std::vector<int>>> bridges(num_of_stones - 1);

    for (int i = 0; i < num_of_stones; ++i) {
        std::getline(std::cin, line);
        parse_line_to_set(line, inscriptions[i]);
        std::getline(std::cin, line);
        std::set<std::pair<int, int>> current_leys;
        parse_ley_lines(line, current_leys);
        ley_lines[i] = current_leys;
        for (const std::pair<int, int> ley : current_leys) {
            occupied_ports[i].insert(ley.first);
            occupied_ports[i].insert(ley.second);
        }
        if (i < num_of_stones - 1) {
            std::getline(std::cin, line);
            parse_bridges(line, bridges[i]);
        }
    }

    std::vector<std::map<int, PathInfo>> best_paths(num_of_stones);

    for (int out_port : inscriptions[0]) {
        std::optional<PathInfo> best_path;
        for (int in_port : inscriptions[0]) {
            if (in_port == out_port) {
                continue;
            }
            bool is_existing = ley_lines[0].contains({std::min(in_port, out_port), std::max(in_port, out_port)});
            if (!is_existing && (occupied_ports[0].contains(in_port) || occupied_ports[0].contains(out_port))) {
                continue;
            }
            std::array<int, 3> score = calculate_score(in_port, out_port, ley_lines[0]);
            PathInfo current_path{.scores = {score}, .path = {{in_port, out_port}}};
            if (!best_path.has_value() || current_path < best_path) {
                best_path = current_path;
            }
        }
        if (best_path.has_value()) {
            best_paths[0][out_port] = best_path.value();
        }
    }

    for (int i = 1; i < num_of_stones; ++i) {
        std::map<int, PathInfo> best_arrival;
        for (const auto& [prev_out_port, prev_info] : best_paths[i - 1]) {
            if (bridges[i - 1].contains(prev_out_port)) {
                for (int current_in : bridges[i - 1].at(prev_out_port)) {
                    if (inscriptions[i].contains(current_in)) {
                        if (!best_arrival.contains(current_in) || prev_info < best_arrival.at(current_in)) {
                            best_arrival[current_in] = prev_info;
                        }
                    }
                }
            }
        }

        for (int out_port : inscriptions[i]) {
            std::optional<PathInfo> best_port_for_out;
            for (const auto& [in_port, arrival_port] : best_arrival) {
                if (in_port == out_port) {
                    continue;
                }
                bool is_existing = ley_lines[i].contains({std::min(in_port, out_port), std::max(in_port, out_port)});
                if (!is_existing && (occupied_ports[i].contains(in_port) || occupied_ports[i].contains(out_port))) {
                    continue;
                }

                PathInfo candidate_port = arrival_port;
                candidate_port.scores.push_back(calculate_score(in_port, out_port, ley_lines[i]));
                candidate_port.path.emplace_back(in_port, out_port);

                if (!best_port_for_out.has_value() || candidate_port < best_port_for_out.value()) {
                    best_port_for_out = candidate_port;
                }
            }
            if (best_port_for_out.has_value()) {
                best_paths[i][out_port] = best_port_for_out.value();
            }
        }
    }

    std::optional<PathInfo> final_best_port;
    if (!best_paths[num_of_stones - 1].empty()) {
        for (const auto& [out_port, port_info] : best_paths[num_of_stones - 1]) {
            if (!final_best_port.has_value() || port_info < final_best_port.value()) {
                final_best_port = port_info;
            }
        }
    }
    if (final_best_port.has_value()) {
        std::vector<std::pair<int, int>> path = final_best_port.value().path;
        std::cout << path[0].first << ' ' << path[0].second;
        for (int i = 1; i < path.size(); ++i) {
            std::cout << ' ' << path[i].first << ' ' << path[i].second;
        }
        std::cout << '\n';
    } else {
        std::cout << -1 << '\n';
    }

    return 0;
}