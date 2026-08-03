// LeetCode 21. Merge Two Sorted Lists
// 使用双指针原地穿插

#include "common/list_node.h"
#include <vector>

// ═══════════════ 题解 ═══════════════
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(!list1 || !list2) {
            return list1 ? list1 : list2;
        }

        if(list1->val > list2->val) {
            ListNode* swap_temp = list1;
            list1 = list2;
            list2 = swap_temp;
        }

        ListNode* head = list1;

        while(list2) {

            while(list1->next && list1->next->val <= list2->val) {
                list1 = list1->next;
            }

            // list1 耗尽，剩余 list2 批量接上
            if(!list1->next) {          
                list1->next = list2;
                break;
            }
            // 把 list2 节点插入 list1 之后
            ListNode* temp = list2->next; 
            list2->next = list1->next;
            list1->next = list2;
            list1 = list2;
            list2 = temp;

        }

        return head;
    }
};
// ═════════════════════════════════════

// 链表转 vector，便于与期望结果比较
std::vector<int> toVec(ListNode* head) {
    std::vector<int> v;
    while (head) {
        v.push_back(head->val);
        head = head->next;
    }
    return v;
}

// 打印 vector（用于显示期望结果）
void printVec(const std::vector<int>& v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) std::cout << ",";
        std::cout << v[i];
    }
    std::cout << "]";
}

int main() {
    Solution sol;
    ListNode *list1, *list2, *got;
    int passed = 0;

    // ═══ 空链表组：一边为空时直接返回另一边 ═══
    std::vector<std::pair<std::vector<int>, std::vector<int>>> emptyCases = {
        {{}, {}},            // 两个都空，期望 []
        {{}, {1, 2, 3}},     // list1 空，期望 [1,2,3]
        {{1, 2, 3}, {}}      // list2 空，期望 [1,2,3]
    };
    for (auto& p : emptyCases) {
        list1 = buildList(p.first);
        list2 = buildList(p.second);
        std::vector<int> expect = p.first.empty() ? p.second : p.first;
        std::cout << "空链表: ";
        printVec(p.first);
        std::cout << " + ";
        printVec(p.second);
        std::cout << "，期望 ";
        printVec(expect);
        std::cout << "，实际 ";
        got = sol.mergeTwoLists(list1, list2);
        printList(got);
        if (toVec(got) == expect) { std::cout << "  [PASS]\n"; ++passed; }
        else { std::cout << "  [FAIL]\n"; }
        deleteList(got);
    }
    std::cout << "\n";

    // ═══ 常规组 ═══
    // Test 1：单节点，list1 较小
    list1 = buildList({1});
    list2 = buildList({2});
    std::cout << "Test 1: [1] + [2]，期望 [1,2]，实际 ";
    got = sol.mergeTwoLists(list1, list2);
    printList(got);
    if (toVec(got) == std::vector<int>({1, 2})) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    deleteList(got);

    // Test 2：单节点，需要交换头
    list1 = buildList({2});
    list2 = buildList({1});
    std::cout << "Test 2: [2] + [1]，期望 [1,2]，实际 ";
    got = sol.mergeTwoLists(list1, list2);
    printList(got);
    if (toVec(got) == std::vector<int>({1, 2})) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    deleteList(got);

    // Test 3：经典示例（含相等元素）
    list1 = buildList({1, 2, 4});
    list2 = buildList({1, 3, 4});
    std::cout << "Test 3: [1,2,4] + [1,3,4]，期望 [1,1,2,3,4,4]，实际 ";
    got = sol.mergeTwoLists(list1, list2);
    printList(got);
    if (toVec(got) == std::vector<int>({1, 1, 2, 3, 4, 4})) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    deleteList(got);

    // Test 4：list1 整体更小，list2 全部接到末尾
    list1 = buildList({1, 2, 3});
    list2 = buildList({4, 5, 6});
    std::cout << "Test 4: [1,2,3] + [4,5,6]，期望 [1,2,3,4,5,6]，实际 ";
    got = sol.mergeTwoLists(list1, list2);
    printList(got);
    if (toVec(got) == std::vector<int>({1, 2, 3, 4, 5, 6})) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    deleteList(got);

    // Test 5：list2 整体更小，交换头后 list2 全部接到末尾
    list1 = buildList({4, 5, 6});
    list2 = buildList({1, 2, 3});
    std::cout << "Test 5: [4,5,6] + [1,2,3]，期望 [1,2,3,4,5,6]，实际 ";
    got = sol.mergeTwoLists(list1, list2);
    printList(got);
    if (toVec(got) == std::vector<int>({1, 2, 3, 4, 5, 6})) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    deleteList(got);

    // ═══ 边界组 ═══
    // Test 6：list1 只有一个节点，且需跳过 list2 的多个节点
    list1 = buildList({5});
    list2 = buildList({1, 2, 3, 4});
    std::cout << "Test 6: [5] + [1,2,3,4]，期望 [1,2,3,4,5]，实际 ";
    got = sol.mergeTwoLists(list1, list2);
    printList(got);
    if (toVec(got) == std::vector<int>({1, 2, 3, 4, 5})) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    deleteList(got);

    // Test 7：交替穿插
    list1 = buildList({1, 3, 5});
    list2 = buildList({2, 4, 6});
    std::cout << "Test 7: [1,3,5] + [2,4,6]，期望 [1,2,3,4,5,6]，实际 ";
    got = sol.mergeTwoLists(list1, list2);
    printList(got);
    if (toVec(got) == std::vector<int>({1, 2, 3, 4, 5, 6})) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    deleteList(got);

    // Test 8：交替穿插（需要交换头）
    list1 = buildList({2, 4, 6});
    list2 = buildList({1, 3, 5});
    std::cout << "Test 8: [2,4,6] + [1,3,5]，期望 [1,2,3,4,5,6]，实际 ";
    got = sol.mergeTwoLists(list1, list2);
    printList(got);
    if (toVec(got) == std::vector<int>({1, 2, 3, 4, 5, 6})) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    deleteList(got);

    // Test 9：全部相等
    list1 = buildList({1, 1, 1});
    list2 = buildList({1, 1, 1});
    std::cout << "Test 9: [1,1,1] + [1,1,1]，期望 [1,1,1,1,1,1]，实际 ";
    got = sol.mergeTwoLists(list1, list2);
    printList(got);
    if (toVec(got) == std::vector<int>({1, 1, 1, 1, 1, 1})) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    deleteList(got);

    // Test 10：等长逐位交错
    list1 = buildList({1, 2, 3, 4, 5});
    list2 = buildList({1, 2, 3, 4, 5});
    std::cout << "Test 10: [1,2,3,4,5] + [1,2,3,4,5]，期望 [1,1,2,2,3,3,4,4,5,5]，实际 ";
    got = sol.mergeTwoLists(list1, list2);
    printList(got);
    if (toVec(got) == std::vector<int>({1, 1, 2, 2, 3, 3, 4, 4, 5, 5})) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    deleteList(got);

    // Test 11：list1 很小，list2 全部在前面（末尾插入）
    list1 = buildList({10});
    list2 = buildList({1, 2, 3});
    std::cout << "Test 11: [10] + [1,2,3]，期望 [1,2,3,10]，实际 ";
    got = sol.mergeTwoLists(list1, list2);
    printList(got);
    if (toVec(got) == std::vector<int>({1, 2, 3, 10})) { std::cout << "  [PASS]\n"; ++passed; }
    else { std::cout << "  [FAIL]\n"; }
    deleteList(got);
    std::cout << "\n";

    // ═══ 压力测试：10000 节点交错合并（题设节点数上界为 50，这里加大验证正确性）═══
    std::vector<int> even, odd;
    for (int i = 0; i < 10000; ++i) {
        even.push_back(2 * i);
        odd.push_back(2 * i + 1);
    }
    std::vector<int> expect(20000);
    for (int i = 0; i < 20000; ++i) expect[i] = i;
    list1 = buildList(even);
    list2 = buildList(odd);
    std::cout << "压力测试: 10000 节点交错合并，期望有序 0..19999，实际 ";
    got = sol.mergeTwoLists(list1, list2);
    std::vector<int> gotVec = toVec(got);
    if (gotVec == expect) { std::cout << "长度 " << gotVec.size() << " 且有序  [PASS]\n"; ++passed; }
    else { std::cout << "顺序错误  [FAIL]\n"; }
    deleteList(got);

    std::cout << "\nPassed " << passed << " / 15\n";
    return 0;
}
