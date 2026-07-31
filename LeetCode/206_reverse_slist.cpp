// LeetCode 206. Reverse Linked List
// 递归法：O(N) 时间，O(N) 栈空间

#include "common/list_node.h"
#include <vector>

// ═══════════════ 题解 ═══════════════
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode* newHead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }
};
// ═════════════════════════════════════

int main() {
    Solution sol;

    std::vector<std::vector<int>> tests = {
        {1, 2, 3, 4, 5},
        {1, 2},
        {1},
        {}
    };

    for (auto& t : tests) {
        ListNode* head = buildList(t);
        std::cout << "Input:  "; printList(head);
        head = sol.reverseList(head);
        std::cout << "Output: "; printList(head);
        deleteList(head);
        std::cout << "\n";
    }

    return 0;
}
