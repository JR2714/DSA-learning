// LeetCode 142. Linked List Cycle II
// 使用快慢指针

#include "common/list_node.h"
#include <vector>

// ═══════════════ 题解 ═══════════════
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(!head) { 
            return nullptr;
        }

        ListNode* slow = head;
        ListNode* fast = head;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) {
                slow = head;
                while(slow != fast) { // 将入环第一个点视为“0”点
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;
            }
        }
        return nullptr;
    }
};
// ═════════════════════════════════════

// 打印链表，最多打印 limit 个节点（有环时避免死循环）
void printListLimit(ListNode* head, int limit) {
    ListNode* p = head;
    for (int i = 0; i < limit && p != nullptr; ++i) {
        if (i > 0) std::cout << " -> ";
        std::cout << p->val;
        p = p->next;
    }
    if (p != nullptr) std::cout << " -> ...";
    std::cout << "\n";
}

// 断开环（pos 为环入口下标，-1 无环），方便安全释放内存
void breakCycle(ListNode* head, int n, int pos) {
    if (pos < 0 || head == nullptr) return;
    ListNode* tail = head;
    for (int i = 1; i < n; ++i) tail = tail->next;
    tail->next = nullptr;
}

int main() {
    Solution sol;
    ListNode* head;
    ListNode* got;
    int passed = 0;

    // ═══ 无环组：期望 nullptr ═══
    std::vector<std::vector<int>> noCycle = {
        {},                     // 空链表
        {1},                    // 单节点
        {1, 2},                 // 两节点
        {1, 2, 3, 4, 5},        // 常规
        {-100000}               // 负数边界
    };
    for (auto& vals : noCycle) {
        head = buildCycleList(vals, -1);
        std::cout << "无环 " << vals.size() << " 节点: ";
        printListLimit(head, 6);
        got = sol.detectCycle(head);
        if (got == nullptr) {
            std::cout << "  got = nullptr  [PASS]\n";
            ++passed;
        } else {
            std::cout << "  got = " << got->val << "  [FAIL]\n";
        }
        deleteList(head);
    }
    std::cout << "\n";

    // ═══ 有环组：期望环入口的节点值 ═══
    // 测试 1：单节点自环（入口 = 唯一节点）
    head = buildCycleList({1}, 0);
    std::cout << "Test 1: 1 -> 1（自环），期望入口 1，实际 ";
    got = sol.detectCycle(head);
    if (got) std::cout << got->val; else std::cout << "nullptr";
    if (got != nullptr && got->val == 1) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    breakCycle(head, 1, 0);
    deleteList(head);

    // 测试 2：两节点，尾指头（入口 = 头）
    head = buildCycleList({1, 2}, 0);
    std::cout << "Test 2: 1 -> 2 -> 1，期望入口 1，实际 ";
    got = sol.detectCycle(head);
    if (got) std::cout << got->val; else std::cout << "nullptr";
    if (got != nullptr && got->val == 1) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    breakCycle(head, 2, 0);
    deleteList(head);

    // 测试 3：两节点，尾自环（入口 = 尾）
    head = buildCycleList({1, 2}, 1);
    std::cout << "Test 3: 1 -> 2 -> 2，期望入口 2，实际 ";
    got = sol.detectCycle(head);
    if (got) std::cout << got->val; else std::cout << "nullptr";
    if (got != nullptr && got->val == 2) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    breakCycle(head, 2, 1);
    deleteList(head);

    // 测试 4：标准例，-4 指回 2（入口 = 2）
    head = buildCycleList({3, 2, 0, -4}, 1);
    std::cout << "Test 4: 3 -> 2 -> 0 -> -4 -> 2，期望入口 2，实际 ";
    got = sol.detectCycle(head);
    if (got) std::cout << got->val; else std::cout << "nullptr";
    if (got != nullptr && got->val == 2) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    breakCycle(head, 4, 1);
    deleteList(head);

    // 测试 5：5 节点尾自环（入口 = 尾）
    head = buildCycleList({1, 2, 3, 4, 5}, 4);
    std::cout << "Test 5: 1 -> 2 -> 3 -> 4 -> 5 -> 5，期望入口 5，实际 ";
    got = sol.detectCycle(head);
    if (got) std::cout << got->val; else std::cout << "nullptr";
    if (got != nullptr && got->val == 5) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    breakCycle(head, 5, 4);
    deleteList(head);

    // 测试 6：5 节点，5 指回 3（入口 = 3）
    head = buildCycleList({1, 2, 3, 4, 5}, 2);
    std::cout << "Test 6: 1 -> 2 -> 3 -> 4 -> 5 -> 3，期望入口 3，实际 ";
    got = sol.detectCycle(head);
    if (got) std::cout << got->val; else std::cout << "nullptr";
    if (got != nullptr && got->val == 3) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    breakCycle(head, 5, 2);
    deleteList(head);

    // 测试 7：k=2, L=5（课堂推导的例子），7 指回 3
    head = buildCycleList({1, 2, 3, 4, 5, 6, 7}, 2);
    std::cout << "Test 7: 1..7 指回 3，期望入口 3，实际 ";
    got = sol.detectCycle(head);
    if (got) std::cout << got->val; else std::cout << "nullptr";
    if (got != nullptr && got->val == 3) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    breakCycle(head, 7, 2);
    deleteList(head);

    // 测试 8：正数边界值自环
    head = buildCycleList({100000}, 0);
    std::cout << "Test 8: 100000 -> 100000（自环），期望入口 100000，实际 ";
    got = sol.detectCycle(head);
    if (got) std::cout << got->val; else std::cout << "nullptr";
    if (got != nullptr && got->val == 100000) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    breakCycle(head, 1, 0);
    deleteList(head);
    std::cout << "\n";

    // ═══ 压力测试：10000 节点尾自环（题设节点数上界）═══
    std::vector<int> big(10000);
    for (int i = 0; i < 10000; ++i) big[i] = i + 1;
    head = buildCycleList(big, 9999);
    std::cout << "压力测试: 10000 节点尾自环，期望入口 " << big[9999] << "，实际 ";
    got = sol.detectCycle(head);
    if (got) std::cout << got->val; else std::cout << "nullptr";
    if (got != nullptr && got->val == big[9999]) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    breakCycle(head, 10000, 9999);
    deleteList(head);

    std::cout << "\nPassed " << passed << " / 14\n";
    return 0;
}
