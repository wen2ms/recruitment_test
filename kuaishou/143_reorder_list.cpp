#include <iostream>
#include <stack>

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* construct_list(const std::vector<int> nums) {
    ListNode *head, *tail;

    head = tail = nullptr;

    for (int num : nums) {
        if (head == nullptr) {
            head = tail = new ListNode(num);
        } else {
            tail->next = new ListNode(num);
            tail = tail->next;
        }
    }

    return head;
}

void print_list(const ListNode* head) {
    while (head != nullptr) {
        std::cout << head->val << ' ';

        head = head->next;
    }
    std::cout << std::endl;
}

class Solution {
  public:
    void reorderList(ListNode* head) {
        if (head == nullptr) {
            return;
        }

        std::stack<ListNode*> node_stack;
        ListNode* node = head;
        int size = 0;

        while (node != nullptr) {
            node_stack.push(node);
            ++size;

            node = node->next;
        }

        node = head;

        for (int i = 0; i < size / 2; ++i) {
            ListNode* tmp = node_stack.top();
            node_stack.pop();

            tmp->next = node->next;
            node->next = tmp;

            node = tmp->next;
        }

        node->next = nullptr;
    }
};

int main() {
    ListNode* case_1 = construct_list({1, 2, 3, 4});
    ListNode* case_2 = construct_list({1, 2, 3, 4, 5});

    Solution solution;

    solution.reorderList(case_1);

    solution.reorderList(case_2);

    print_list(case_1);

    print_list(case_2);

    return 0;
}