// LeetCode 141. Linked List Cycle
// 利用 206_reverse_slist.cpp 的翻转方法。
// 若返回的新头和原来的头相同，则有环。(这里我采用迭代重新写翻转方法)

#include "common/list_node.h"
#include <vector>

// ═══════════════ 题解 ═══════════════
class Solution {
    public:
        // 反转列表
        ListNode* reverseList(ListNode* head) {
            ListNode* prev = nullptr;
            ListNode* cur = head;
            
            while(cur) {
                ListNode* next = cur->next;
                cur->next = prev;
                prev = cur;
                cur = next;
            }

            return prev;
        }

        // 判断是否回环
        bool hasCycle(ListNode* head) {
            if(!head || !head->next || !head->next->next) {
                return false;
            }

            ListNode* temp = head;
            head = reverseList(head);

            if(head == temp) {
                head = reverseList(head);
                return true;
            }

            head = reverseList(head);
            return false;
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

    struct TestCase {
        std::vector<int> vals;  // 节点值
        int pos;                // 环入口下标，-1 表示无环
        bool expected;          // 期望结果
    };

    std::vector<TestCase> tests = {
        {{},                -1, false},  // 空链表
        {{1},               -1, false},  // 单节点，无环
        {{1},                0, true},   // 单节点自环
        {{1, 2},            -1, false},  // 两节点，无环
        {{1, 2},             0, true},   // 两节点，尾指向头
        {{1, 2, 3, 4, 5},   -1, false},  // 常规无环
        {{1, 2, 3, 4, 5},    4, true},   // 尾指向自己
        {{1, 2, 3, 4, 5},    2, true},   // 中间成环（5 -> 3）
    };

    int passed = 0;
    for (size_t i = 0; i < tests.size(); ++i) {
        auto& t = tests[i];
        ListNode* head = buildCycleList(t.vals, t.pos);

        std::cout << "Test " << i + 1 << ":  ";
        printListLimit(head, static_cast<int>(t.vals.size()) + 1);

        bool got = sol.hasCycle(head);
        bool ok = (got == t.expected);
        passed += ok;

        std::cout << "  expected = " << std::boolalpha << t.expected
                  << ", got = " << got
                  << (ok ? "  [PASS]" : "  [FAIL]") << "\n";

        // 验证 hasCycle 后链表被恢复为原样
        std::cout << "  restored: ";
        printListLimit(head, static_cast<int>(t.vals.size()) + 1);

        breakCycle(head, static_cast<int>(t.vals.size()), t.pos);
        deleteList(head);
        std::cout << "\n";
    }

    std::cout << "Passed " << passed << " / " << tests.size() << "\n";
    return 0;
}