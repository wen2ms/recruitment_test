#include <iostream>
#include <vector>
#include <climits>

int main() {
    int n;
    char start_letter, destination_letter;
    
    std::cin >> n >> start_letter >> destination_letter;

    int start = start_letter - 'a' + 1;
    int destination = destination_letter - 'a' + 1;

    std::vector<int> distances(n + 1, INT_MAX);
    std::vector<bool> checked(n + 1, false);
    std::vector<int> prev_nodes(n + 1);

    std::vector<std::vector<int>> graph(n + 1, std::vector<int>(n + 1));

    int value;
    std::string begin_letter, end_letter;

    std::cin >> begin_letter;
    while (begin_letter != "0000") {
        std::cin >> end_letter >> value;
        int begin = begin_letter[0] - 'a' + 1;
        int end = end_letter[0] - 'a' + 1;

        graph[begin][end] = value;
        graph[end][begin] = value;

        std::cin >> begin_letter;
    }

    distances[start] = 0;
    for (int i = 1; i <= n; ++i) {
        int minimum_distance = INT_MAX;
        int minimum_node;
        for (int j = 1; j <= n; ++j) {
            if (distances[j] < minimum_distance && !checked[j]) {
                minimum_distance = distances[j];
                minimum_node = j;
            }
        }

        checked[minimum_node] = true;
        for (int j = 1; j <= n; ++j) {
            if (graph[minimum_node][j] > 0) {
                if (minimum_distance + graph[minimum_node][j] < distances[j]) {
                    distances[j] = minimum_distance + graph[minimum_node][j];
                    prev_nodes[j] = minimum_node;
                }
            }
        }
    }

    std::vector<int> minimum_path;
    int current_node = destination;
    while (current_node != start) {
        minimum_path.push_back(current_node);
        current_node = prev_nodes[current_node];
    }
    minimum_path.push_back(start);

    for (int i = minimum_path.size() - 1; i >= 0; --i) {
        if (i == 0) {
            std::cout << std::string(1, 'a' + minimum_path[i] - 1) << std::endl;
        } else {
            std::cout << std::string(1, 'a' + minimum_path[i] - 1) << ' ';
        }
    }

    return 0;
}