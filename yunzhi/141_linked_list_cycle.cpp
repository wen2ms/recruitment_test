#include <iostream>
#include <vector>

struct ListNode {
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}

    int val;
    ListNode* next;
};

ListNode* construct_list(const std::vector<int>& vec, int pos) {
    ListNode *head, *tail;
    head = tail = nullptr;

    ListNode* cycle_node = nullptr;
    for (int i = 0; i < vec.size(); ++i) {
        if (head == nullptr) {
            head = tail = new ListNode(vec[0]);
        } else {
            tail->next = new ListNode(vec[i]);
            tail = tail->next;
        }

        if (i == pos) {
            cycle_node = tail;
        }
    }

    tail->next = cycle_node;

    return head;
}

bool has_cycle(ListNode* head) {
    ListNode* slow;
    ListNode* fast;

    slow = fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}

int main() {
    ListNode* case_1 = construct_list({3, 2, 0, -4}, 1);
    ListNode* case_2 = construct_list({1, 2}, 0);
    ListNode* case_3 = construct_list({1}, -1);

    std::cout << has_cycle(case_1) << std::endl;

    std::cout << has_cycle(case_2) << std::endl;

    std::cout << has_cycle(case_3) << std::endl;

    return 0;
}