#include <cstdint>
#include <iostream>
#include <vector>

struct Node {
    int node_id;
    uint32_t notice_count;
    Node* parent;
    std::vector<Node*> children;
};

Node* find(Node* root, const int node_id) {
    if (root == nullptr) {
        return nullptr;
    }
    if (root->node_id == node_id) {
        return root;
    }
    for (Node* node : root->children) {
        if (node == nullptr) {
            continue;
        }
        Node* target = find(node, node_id);
        if (target != nullptr) {
            return target;
        }
    }
    return nullptr;
}

void SetNoticeCount(Node* root, int nodeId, unsigned int noticeCount) {
    if (root == nullptr) {
        return;
    }
    Node* node = find(root, nodeId);
    if (node == nullptr) {
        return;
    }

    int diff = noticeCount - node->notice_count;
    node->notice_count = noticeCount;

    Node* curr = node->parent;
    while (curr != nullptr) {
        curr->notice_count += diff;
        curr = curr->parent;
    }
}

int main() {
    Node node_a{.node_id = 1, .notice_count = 3, .parent = nullptr, .children = {}};
    Node node_b{.node_id = 2, .notice_count = 2, .parent = &node_a, .children = {}};
    Node node_c{.node_id = 3, .notice_count = 1, .parent = &node_b, .children = {}};
    node_a.children.push_back(&node_b);
    node_b.children.push_back(&node_c);

    SetNoticeCount(&node_a, 3, 3);

    std::cout << node_a.notice_count << '\n';
    std::cout << node_b.notice_count << '\n';
    std::cout << node_c.notice_count << '\n';

    return 0;
}