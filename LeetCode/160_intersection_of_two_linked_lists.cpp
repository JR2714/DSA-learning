//160. 相交链表
// 使用双指针分别先后遍历各自链表, 从而让它们在交点处(或空节点)相遇.

#include "common/list_node.h"
#include <iostream>
#include <string>
#include <vector>

// ═══════════════ 题解 ═══════════════
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB) {
            return nullptr;
        }
        ListNode* ptrA = headA;
        ListNode* ptrB = headB;

        while(ptrA != ptrB) {
            ptrA = ptrA ? ptrA->next : headB;
            ptrB = ptrB ? ptrB->next : headA;
        }
        return ptrA;
    }
};
// ═════════════════════════════════════

// ═══════════════ 测试辅助 ═══════════════
// 构建两条相交链表: 各自独有前缀 + 共享尾巴(节点是同一份内存, 真共享)
// shared 为空 → 两条独立链表, 无交点
void buildIntersectionLinkedLists(const std::vector<int>& prefixA,
                                  const std::vector<int>& prefixB,
                                  const std::vector<int>& shared,
                                  ListNode*& headA, ListNode*& headB,
                                  ListNode*& inter) {
    headA = buildList(prefixA);
    headB = buildList(prefixB);
    inter = buildList(shared);

    if (inter) {
        ListNode* tailA = headA;
        if (tailA) {
            while (tailA->next) tailA = tailA->next;
            tailA->next = inter;
        } else {
            headA = inter;
        }

        ListNode* tailB = headB;
        if (tailB) {
            while (tailB->next) tailB = tailB->next;
            tailB->next = inter;
        } else {
            headB = inter;
        }
    }
}

// 释放相交链表: 独有前缀各删各的, 共享尾巴只删一次(删两次 = double free)
void deleteIntersectingLists(ListNode* headA, ListNode* headB, ListNode* inter) {
    while (headA && headA != inter) {
        ListNode* tmp = headA;
        headA = headA->next;
        delete tmp;
    }
    while (headB && headB != inter) {
        ListNode* tmp = headB;
        headB = headB->next;
        delete tmp;
    }
    deleteList(inter);
}

// 打印核对: 比较的是节点地址(指针), 不是值
void printResult(const char* name, ListNode* got, ListNode* expected) {
    std::cout << name << ": 实际 = "
              << (got ? std::to_string(got->val) : "nullptr")
              << ", 期望 = "
              << (expected ? std::to_string(expected->val) : "nullptr")
              << (got == expected ? "  通过" : "  失败") << "\n";
}

int main() {
    Solution sol;
    ListNode *headA = nullptr, *headB = nullptr, *inter = nullptr;

    // 用例1: 无交点, 长度不同
    buildIntersectionLinkedLists({1, 2, 3}, {4, 5}, {}, headA, headB, inter);
    printResult("用例1 无交点, 长度不同", sol.getIntersectionNode(headA, headB), nullptr);
    printList(headA);
    printList(headB);
    deleteIntersectingLists(headA, headB, inter);

    // 用例2: 无交点, 等长
    buildIntersectionLinkedLists({1, 2, 3}, {4, 5, 6}, {}, headA, headB, inter);
    printResult("用例2 无交点, 等长", sol.getIntersectionNode(headA, headB), nullptr);
    printList(headA);
    printList(headB);
    deleteIntersectingLists(headA, headB, inter);

    // 用例3: 陷阱! 值相同但节点是两份独立内存 → 无交点
    buildIntersectionLinkedLists({1, 2, 3}, {1, 2, 3}, {}, headA, headB, inter);
    printResult("用例3 值相同但节点不同", sol.getIntersectionNode(headA, headB), nullptr);
    printList(headA);
    printList(headB);
    deleteIntersectingLists(headA, headB, inter);

    // 用例4: 中部相交 (LeetCode 示例1: 交点 val = 8)
    buildIntersectionLinkedLists({4, 1}, {5, 6, 1}, {8, 4, 5}, headA, headB, inter);
    printResult("用例4 中部相交", sol.getIntersectionNode(headA, headB), inter);
    printList(headA);
    printList(headB);
    deleteIntersectingLists(headA, headB, inter);

    // 用例5: 尾部相交 (LeetCode 示例3: 交点 val = 4)
    buildIntersectionLinkedLists({2, 6}, {1, 5, 9}, {4}, headA, headB, inter);
    printResult("用例5 尾部相交", sol.getIntersectionNode(headA, headB), inter);
    printList(headA);
    printList(headB);
    deleteIntersectingLists(headA, headB, inter);

    // 用例6: 交点就是 A 的头 (A 无独有前缀)
    buildIntersectionLinkedLists({}, {9}, {1, 2, 3}, headA, headB, inter);
    printResult("用例6 交点即 A 头", sol.getIntersectionNode(headA, headB), inter);
    deleteIntersectingLists(headA, headB, inter);

    // 用例7: 交点就是 B 的头 (B 无独有前缀)
    buildIntersectionLinkedLists({7}, {}, {1, 2, 3}, headA, headB, inter);
    printResult("用例7 交点即 B 头", sol.getIntersectionNode(headA, headB), inter);
    deleteIntersectingLists(headA, headB, inter);

    // 用例8: 等长且相交
    buildIntersectionLinkedLists({1, 2}, {5, 6}, {3, 4}, headA, headB, inter);
    printResult("用例8 等长且相交", sol.getIntersectionNode(headA, headB), inter);
    deleteIntersectingLists(headA, headB, inter);

    // 用例9: A 为空
    buildIntersectionLinkedLists({}, {1, 2}, {}, headA, headB, inter);
    printResult("用例9 A 为空", sol.getIntersectionNode(headA, headB), nullptr);
    deleteIntersectingLists(headA, headB, inter);

    // 用例10: B 为空
    buildIntersectionLinkedLists({1, 2}, {}, {}, headA, headB, inter);
    printResult("用例10 B 为空", sol.getIntersectionNode(headA, headB), nullptr);
    deleteIntersectingLists(headA, headB, inter);

    // 用例11: 压力测试 (5000 + 4000 独有节点, 共享 1 个尾巴)
    std::vector<int> bigA, bigB;
    for (int i = 0; i < 5000; ++i) bigA.push_back(i);
    for (int i = 0; i < 4000; ++i) bigB.push_back(i);
    buildIntersectionLinkedLists(bigA, bigB, {50000}, headA, headB, inter);
    printResult("用例11 压力测试", sol.getIntersectionNode(headA, headB), inter);
    deleteIntersectingLists(headA, headB, inter);
}
// ═════════════════════════════════════