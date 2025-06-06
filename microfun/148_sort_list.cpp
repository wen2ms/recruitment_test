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
            head = tail = new ListNode(vec[i]);
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
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }

        ListNode* slow = head;
        ListNode* fast = head->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* mid = slow->next;
        slow->next = nullptr;

        ListNode* left = sortList(head);
        ListNode* right = sortList(mid);

        return merge(left, right);
    }

  private:
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode node;
        ListNode* tail = &node;

        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        tail->next = l1 ? l1 : l2;
        return node.next;
    }
};

int main() {
    ListNode* case_1 = construct_list({4, 2, 1, 3});
    ListNode* case_2 = construct_list({-1, 5, 3, 4, 0});
    ListNode* case_3 = construct_list({});

    Solution solution;

    print_list(solution.sortList(case_1));

    print_list(solution.sortList(case_2));

    print_list(solution.sortList(case_3));

    return 0;
}