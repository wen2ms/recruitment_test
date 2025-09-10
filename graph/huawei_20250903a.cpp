#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class UnionFind {
  public:
    explicit UnionFind(int size) : parents_(size) {
        for (int i = 0; i < size; ++i) {
            parents_[i] = i;
        }
    }

    int find(int index) {
        if (parents_[index] != index) {
            parents_[index] = find(parents_[index]);
        }
        return parents_[index];
    }

    void unite(int node1, int node2, std::vector<int>& strength, const std::vector<std::pair<std::string, int>>& vertices,
               std::vector<int>& max_id) {
        int root1 = find(node1);
        int root2 = find(node2);
        if (root1 == root2) {
            return;
        }
        parents_[root1] = root2;
        strength[root2] += strength[root1];

        if (vertices[max_id[root1]].second > vertices[max_id[root2]].second) {
            max_id[root2] = max_id[root1];
        }
    }

  private:
    std::vector<int> parents_;
};

int main() {
    int vertices_count;
    std::cin >> vertices_count;
    std::vector<std::pair<std::string, int>> vertices(vertices_count);
    std::unordered_map<std::string, int> name_to_id;
    std::vector<int> strength(vertices_count);
    std::vector<int> max_id(vertices_count);
    UnionFind union_find(vertices_count);
    for (int i = 0; i < vertices_count; ++i) {
        std::cin >> vertices[i].first >> vertices[i].second;
        name_to_id[vertices[i].first] = i;
        strength[i] = vertices[i].second;
        max_id[i] = i;
    }

    int edges_count;
    std::cin >> edges_count;
    for (int i = 0; i < edges_count; ++i) {
        std::string start;
        std::string end;
        std::cin >> start >> end;
        union_find.unite(name_to_id[start], name_to_id[end], strength, vertices, max_id);
    }

    int max_strength = -1;
    std::string max_name;

    for (int i = 0; i < vertices_count; ++i) {
        if (union_find.find(i) == i) {
            if (strength[i] > max_strength) {
                max_strength = strength[i];
                max_name = vertices[max_id[i]].first;
            }
        }
    }
    std::cout << max_name << ' ' << max_strength << '\n';

    return 0;
}