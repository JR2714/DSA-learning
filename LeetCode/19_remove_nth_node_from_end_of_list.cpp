#include "common/list_node.h"
#include <vector>

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy;
        ListNode* pioneer = head;
        ListNode* follower = &dummy;
        follower->next = head;

        for(int cur = 0; cur < n; ++cur) {
            if(!pioneer) return nullptr;
            pioneer = pioneer->next;
        }

        while(pioneer) {
            pioneer = pioneer->next;
            follower = follower->next;
        }

        ListNode* to_be_deleted = follower->next;
        follower->next = to_be_deleted ? to_be_deleted->next : nullptr;

        delete to_be_deleted;
        return dummy.next;
    }
};

int main() {
    Solution sol;

    ListNode* test1 = new ListNode(1);
    ListNode* head = sol.removeNthFromEnd(test1, 1);
    printList(head);
    deleteList(head);

    std::vector<int> for_test2 = {1, 2, 3, 4, 5};
    ListNode* test2 = buildList(for_test2);
    head = sol.removeNthFromEnd(test2, 2);
    printList(head);
    deleteList(head);
}