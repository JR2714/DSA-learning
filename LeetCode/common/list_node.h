#pragma once
#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 从 vector 构建链表（带哨兵，简化为统一插入逻辑）
inline ListNode* buildList(const std::vector<int>& vals) {
    ListNode dummy;
    ListNode* cur = &dummy;
    for (int v : vals) {
        cur->next = new ListNode(v);
        cur = cur->next;
    }
    return dummy.next;
}

// 打印链表
inline void printList(ListNode* head) {
    ListNode* p = head;
    while (p) {
        std::cout << p->val;
        if (p->next) std::cout << " -> ";
        p = p->next;
    }
    std::cout << "\n";
}

// 释放链表
inline void deleteList(ListNode* head) {
    while (head) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}
