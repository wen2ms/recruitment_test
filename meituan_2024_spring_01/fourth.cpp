#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>

std::unordered_map<long long, long long> current_friends;

long long find(long long i) {
    if (i != current_friends[i]) {
        current_friends[i] = find(current_friends[i]);
    }

    return current_friends[i];
}

void merge(long long i, long long j) {
    long long i_family = find(i);
    long long j_family = find(j);

    current_friends[i_family] = j_family;
}

int main() {
    long long n;
    int m, q;

    std::cin >> n >> m >> q;
    std::set<std::pair<long long, long long>> original_friends;

    for (int i = 0; i < m; ++i) {
        long long u, v;

        std::cin >> u >> v;
        if (u > v) {
            std::swap(u, v);
        }

        current_friends[u] = u;
        current_friends[v] = v;

        original_friends.insert({u, v});
    }

    std::vector<std::tuple<int, long long, long long>> all_operations;
    std::set<std::pair<long long, long long>> deleting_friends;

    for (int i = 0; i < q; ++i) {
        int op;
        long long u, v;

        std::cin >> op >> u >> v;
        if (u > v) {
            std::swap(u, v);
        }

        current_friends[u] = u;
        current_friends[v] = v;

        all_operations.push_back({op, u, v});

        if (op == 1) {
            deleting_friends.insert({u, v});
        }
    }

    for (auto [u, v] : original_friends) {
        if (deleting_friends.find({u, v}) == deleting_friends.end()) {
            merge(u, v);
        }
    }

    std::vector<bool> query_results;
    for (int i = q - 1; i >= 0; --i) {
        auto [op, u, v] = all_operations[i];

        if (op == 1 && original_friends.find({u, v}) != original_friends.end()) {
            merge(u, v);
        } else if (op == 2) {
            u = find(u);
            v = find(v);
            
            query_results.push_back(u == v);
        }
    }

    for (int i = query_results.size() - 1; i >= 0; --i) {
        if (query_results[i]) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }
    }

    return 0;
}