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

// 构建带环链表：pos 为环入口下标（0 起），pos = -1 表示无环
inline ListNode* buildCycleList(const std::vector<int>& vals, int pos) {
    ListNode* head = buildList(vals);
    if (pos < 0 || head == nullptr) return head;

    ListNode* entry = head;
    for (int i = 0; i < pos; ++i) entry = entry->next;

    ListNode* tail = head;
    while (tail->next) tail = tail->next;
    tail->next = entry;
    return head;
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
