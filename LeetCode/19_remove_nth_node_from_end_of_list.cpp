#include "common/list_node.h"
#include <vector>
#include <iostream>

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // pioneer 先走 n 步,之后两者同步,pioneer 到底时 follower 恰在待删节点前驱
        ListNode dummy;
        ListNode* pioneer = head;
        ListNode* follower = &dummy;
        follower->next = head;

        for(int cur = 0; cur < n; ++cur) {
            if(!pioneer) {
                std::cout << "要删除的位置不在列表中, 未对链表做出更改. \n";
                return head;
            }
            pioneer = pioneer->next;
        }

        while(pioneer) {
            pioneer = pioneer->next;
            follower = follower->next;
        }

        ListNode* to_be_deleted = follower->next;
        follower->next = to_be_deleted->next;

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