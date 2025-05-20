#include <iostream>
#include <vector>

struct ListNode {
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(0), next(next) {}

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

void print_list(const ListNode* head) {
    while (head) {
        std::cout << head->val << ' ';
        head = head->next;
    }
    std::cout << std::endl;
}

class Solution {
  public:
    ListNode* remove_nth_from_end(ListNode* head, int n) {
        ListNode* prev;
        ListNode* tail;

        prev = tail = head;
        for (int i = 0; i < n; ++i) {
            tail = tail->next;
        }

        if (!tail) {
            return nullptr;
        }

        while (tail->next) {
            prev = prev->next;
            tail = tail->next;
        }

        ListNode* nth_node_end = prev->next;
        prev->next = nth_node_end->next;
        delete nth_node_end;

        return head;
    }
};

int main() {

    ListNode* case_1 = construct_list({1, 2, 3, 4, 5});
    ListNode* case_2 = construct_list({1});
    ListNode* case_3 = construct_list({1, 2});

    Solution solution;

    print_list(solution.remove_nth_from_end(case_1, 2));

    print_list(solution.remove_nth_from_end(case_2, 1));

    print_list(solution.remove_nth_from_end(case_3, 1));
    return 0;
}