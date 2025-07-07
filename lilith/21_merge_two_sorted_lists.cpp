#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
  public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) {
            return list2;
        }

        if (list2 = nullptr) {
            return list1;
        }

        if (list1->val < list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);

            return list1;
        } else {
            list2->next = mergeTwoLists(list1, list2->next);

            return list2;
        }
    }
};

ListNode* construct_list(const std::vector<int>& vec) {
    ListNode* head;
    ListNode* tail;

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

void print_list(ListNode* head) {
    while (head) {
        std::cout << head->val << ' ';
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    ListNode* case_1_l1 = construct_list({1, 2, 4});
    ListNode* case_1_l2 = construct_list({1, 3, 4});

    ListNode* case_2_l1 = construct_list({});
    ListNode* case_2_l2 = construct_list({});

    ListNode* case_3_l1 = construct_list({});
    ListNode* case_3_l2 = construct_list({0});

    Solution solution;

    print_list(solution.mergeTwoLists(case_1_l1, case_1_l2));

    print_list(solution.mergeTwoLists(case_2_l1, case_2_l2));

    print_list(solution.mergeTwoLists(case_3_l1, case_3_l2));

    return 0;
}