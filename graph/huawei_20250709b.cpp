#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

void dfs(const int source, const int destination, std::vector<std::vector<int>>& all_paths, std::vector<int>& current_path,
         std::vector<bool>& visited_nodes, std::vector<bool>& visited_edges,
         const std::vector<std::vector<std::pair<int, int>>>& adjacent) {
    visited_nodes[source] = true;
    if (source == destination) {
        all_paths.push_back(current_path);
    } else {
        for (const auto& [end, edge_id] : adjacent[source]) {
            if (!visited_nodes[end] && !visited_edges[edge_id]) {
                visited_edges[edge_id] = true;
                current_path.push_back(edge_id);
                dfs(end, destination, all_paths, current_path, visited_nodes, visited_edges, adjacent);
                current_path.pop_back();
                visited_edges[edge_id] = false;
            }
        }
    }
    visited_nodes[source] = false;
}

int main() {
    int nodes_count;
    int edges_count;
    int source;
    int destination;
    std::cin >> nodes_count >> edges_count >> source >> destination;

    std::vector<std::vector<std::pair<int, int>>> adjacent(nodes_count + 1);
    for (int i = 1; i <= edges_count; ++i) {
        int start;
        int end;
        std::cin >> start >> end;
        adjacent[start].emplace_back(end, i);
        adjacent[end].emplace_back(start, i);
    }

    std::vector<std::vector<int>> all_paths;
    std::vector<int> current_path;
    std::vector<bool> visited_nodes(nodes_count + 1);
    std::vector<bool> visited_edges(edges_count + 1);

    dfs(source, destination, all_paths, current_path, visited_nodes, visited_edges, adjacent);

    std::sort(all_paths.begin(), all_paths.end());

    std::unordered_map<int, std::vector<int>> edge_to_paths;
    for (int i = 0; i < all_paths.size(); ++i) {
        for (int edge_id : all_paths[i]) {
            edge_to_paths[edge_id].push_back(i + 1);
        }
    }

    int queries_count;
    std::cin >> queries_count;

    for (int i = 0; i < queries_count; ++i) {
        int destoryed_edge;
        std::cin >> destoryed_edge;
        auto iter = edge_to_paths.find(destoryed_edge);
        if (iter == edge_to_paths.end()) {
            std::cout << 0 << '\n';
        } else {
            std::cout << iter->second.size();
            for (int path_id : iter->second) {
                std::cout << ' ' << path_id;
            }
            std::cout << '\n';
        }
    }

    return 0;
}