#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
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

void print_list(const ListNode* head) {
    while (head) {
        std::cout << head->val << ' ';
        head = head->next;
    }
    std::cout << std::endl;
}

class Solution {
  public:
    ListNode* swapPairs(ListNode* head) {
        ListNode node(0, head);
        ListNode* prev = &node;
        ListNode* cur = head;

        while (cur && cur->next) {
            ListNode* next_pair = cur->next->next;
            ListNode* second = cur->next;

            prev->next = second;
            second->next = cur;
            cur->next = next_pair;

            prev = cur;
            cur = next_pair;
        }

        return node.next;
    }
};

int main() {
    ListNode* case_1 = construct_list({1,2,3,4});
    ListNode* case_2 = construct_list({});
    ListNode* case_3 = construct_list({1});
    ListNode* case_4 = construct_list({1,2,3});

    Solution solution;

    print_list(solution.swapPairs(case_1));

    print_list(solution.swapPairs(case_2));

    print_list(solution.swapPairs(case_3));

    print_list(solution.swapPairs(case_4));

    return 0;
}