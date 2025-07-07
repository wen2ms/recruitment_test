#include <iostream>
#include <vector>

// 给定一个链表，按照以下规则重新排列：
// 头节点保持不变。
// 遍历剩下的节点：
// 奇数下标（从1开始计数）的节点插入到链表尾部。
// 偶数下标的节点插入到链表头部（即头插法）。
// 最终返回新的链表头节点。
// 注意：
// 下标是从 1 开始计数的，也就是说：
// 第 1 个节点（head->next）视为下标 1，插入到尾部。
// 第 2 个节点视为下标 2，插入到头部。
// 以此类推。

// 1 → 2 → 3 → 4 → 5
// 5 → 3 → 1 → 2 → 4

struct ListNode {
    ListNode() : val(0), next(nullptr) {}
    ListNode(int val) : val(val), next(nullptr) {}
    ListNode(int val, ListNode* next) : val(val), next(next) {}

    int val;
    ListNode* next;
};

ListNode* construct_list(const std::vector<int>& nums) {
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

class Solution {
  public:
    ListNode* formatList(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }

        ListNode* new_head = head;
        ListNode* tail = head;
        int index = 1;

        ListNode* curr = head->next;
        tail->next = nullptr;

        while (curr != nullptr) {
            ListNode* tmp = curr->next;

            if (index % 2 == 1) {
                tail->next = curr;
                tail = curr;
                tail->next = nullptr;
            } else {
                curr->next = new_head;
                new_head = curr;
            }

            curr = tmp;
            ++index;
        }

        return new_head;
    }
};

void print_nums(const ListNode* list) {
    while (list != nullptr) {
        std::cout << list->val << ' ';
        list = list->next;
    }

    std::cout << std::endl;
}

int main() {
    std::vector<int> case_1 = {1, 2, 3, 4, 5};
    std::vector<int> case_2 = {1, 2, 3, 4, 5, 6, 7};

    Solution solution;

    print_nums(solution.formatList(construct_list(case_1)));

    print_nums(solution.formatList(construct_list(case_2)));

    return 0;
}