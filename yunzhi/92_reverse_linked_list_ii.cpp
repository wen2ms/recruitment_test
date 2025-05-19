#include <iostream>
#include <vector>

struct ListNode {
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}

    int val;
    ListNode* next;
};

ListNode* construct_list(const std::vector<int>& vec) {
    ListNode *head, *tail;
    head = tail = nullptr;

    for (int i = 0; i < vec.size(); ++i) {
        if (head == nullptr) {
            head = tail = new ListNode(vec[0]);
        } else {
            tail->next = new ListNode(vec[i]);
            tail = tail->next;
        }
    }
    return head;
}

auto print_list = [](const ListNode* head) {
    while (head != nullptr) {
        std::cout << head->val << ' ';
        head = head->next;
    }
    std::cout << std::endl; 
};

class Solution {
  public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head == nullptr || left == right) {
            return head;
        }

        ListNode node(0, head);
        ListNode* prev = &node;

        for (int i = 0; i < left - 1; ++i) {
            prev = prev->next;
        }

        ListNode* cur = prev->next;

        for (int i = 0; i < right - left; ++i) {
            ListNode* tmp = cur->next;

            cur->next = tmp->next;
            tmp->next = prev->next;
            prev->next = tmp;
        }

        return node.next;
    }
};

int main() {
    ListNode* case_1 = construct_list({1, 2, 3, 4, 5});
    ListNode* case_2 = construct_list({5});

    Solution solution;

    print_list(solution.reverseBetween(case_1, 2, 4));

    print_list(solution.reverseBetween(case_2, 1, 1));

    return 0;
}