#include <iostream>
#include <vector>

struct ListNode {
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}

    int val;
    ListNode* next;
};

ListNode* contruct_list(const std::vector<int>& vec) {
    ListNode *head, *tail;
    head = tail = nullptr;

    for (int i = 0; i < vec.size(); ++i) {
        if (head == nullptr) {
            head = tail = new ListNode(vec[i]);
        } else {
            tail->next = new ListNode(vec[i]);
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
    ListNode* reverseList(ListNode* head) {
        ListNode* node = nullptr;

        while (head != nullptr) {
            ListNode* tmp = head->next;

            head->next = node;

            node = head;

            head = tmp;
        }

        return node;
    }
};

int main() {
    ListNode* case_1 = contruct_list({1, 2, 3, 4, 5});
    ListNode* case_2 = contruct_list({1, 2});
    ListNode* case_3 = contruct_list({});

    Solution solution;

    print_list(solution.reverseList(case_1));

    print_list(solution.reverseList(case_2));

    print_list(solution.reverseList(case_3));

    return 0;
}