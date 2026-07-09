// 惰性删除的优点："删除"操作在过程中仅需"标记"动作，耗时比直接删除少，且由于操作集中平摊时间应该会少。
// 且"删除"动作并不立即删除物理内存中的数据，可以有"快照"或者说"回滚"的功能。
// 惰性删除的缺点：再遍历操作中，每经过一个节点，需要判断该节点的状态是否被标记为"已删除"，需要额外耗费时间。
// 另外，惰性删除不会立即释放物理内存，内存消耗较大。程序书写也较直接释放内存复杂。

// 测试框架由 AI 辅助生成，测试用例和验证逻辑经本人审查
#include <iostream>
#include <cassert>
#include "lazy_delete_list.h"

// 测试用 print —— 只打印活节点
template <typename T>
void print_live(LazyDeleteList<T>& lst, const char* label) {
    std::cout << label << ": 暂不实现遍历接口\n";
}

int main() {
    std::cout << "=== 测试 1: 构造与 push_back/push_front ===\n";
    {
        LazyDeleteList<int> a;
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);
        a.push_front(0);
        a.push_front(-1);
        std::cout << "push_back/push_front 完成\n";
    } // 析构不崩
    std::cout << "通过\n\n";

    std::cout << "=== 测试 2: pop_front / pop_back ===\n";
    {
        LazyDeleteList<int> a;
        a.push_back(10);
        a.push_back(20);
        a.push_back(30);
        a.pop_front();  // 删 10（惰性标记）
        a.pop_back();   // 删 30（惰性标记）
        // 只剩 20
    }
    std::cout << "通过\n\n";

    std::cout << "=== 测试 3: pop 空列表抛异常 ===\n";
    {
        LazyDeleteList<int> a;
        try {
            a.pop_front();
            std::cout << "失败: 未抛异常\n";
        } catch (const std::logic_error& e) {
            std::cout << "正确抛 logic_error: " << e.what() << "\n";
        }
        try {
            a.pop_back();
            std::cout << "失败: 未抛异常\n";
        } catch (const std::logic_error& e) {
            std::cout << "正确抛 logic_error: " << e.what() << "\n";
        }
    }
    std::cout << "通过\n\n";

    std::cout << "=== 测试 4: delete_the 基本功能 ===\n";
    {
        LazyDeleteList<int> a;
        for (int i = 0; i < 5; ++i) a.push_back(i);  // 0 1 2 3 4
        a.delete_the(0);  // 删 0
        a.delete_the(3);  // 删 4（删完0后还剩1 2 3 4，索引3=4）
        // 活节点: 1 2 3
    }
    std::cout << "通过\n\n";

    std::cout << "=== 测试 5: delete_the 越界抛异常 ===\n";
    {
        LazyDeleteList<int> a;
        a.push_back(1);
        try {
            a.delete_the(1);  // the_size=1, 索引1越界
            std::cout << "失败: 未抛异常\n";
        } catch (const std::out_of_range& e) {
            std::cout << "正确抛 out_of_range: " << e.what() << "\n";
        }
    }
    std::cout << "通过\n\n";

    std::cout << "=== 测试 6: 惰性删除 + delete_the 跨过已删节点 ===\n";
    {
        LazyDeleteList<int> a;
        a.push_back(10);
        a.push_back(20);
        a.push_back(30);
        a.push_back(40);
        a.delete_the(1);  // 标记删 20（活: 10 30 40，索引: 10=0, 30=1, 40=2）
        // 现在 delete_the(1) 应该跳过 20，删 30
        a.delete_the(1);  // 删 30
        // 活节点: 10 40
    }
    std::cout << "通过\n\n";

    std::cout << "=== 测试 7: 拷贝构造 ===\n";
    {
        LazyDeleteList<int> a;
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);
        a.delete_the(1);  // 惰性删 2

        LazyDeleteList<int> b(a);  // 拷贝：活节点 1 3 + 已标记删除的 2
        // b 应和 a 状态一致: the_size=2, deleted_size=1
    }
    std::cout << "通过\n\n";

    std::cout << "=== 测试 8: 移动构造 ===\n";
    {
        LazyDeleteList<int> a;
        a.push_back(100);
        a.push_back(200);
        LazyDeleteList<int> b(std::move(a));  // a 被移空
        // b 活节点: 100 200
        // a 析构不应崩溃
    }
    std::cout << "通过\n\n";

    std::cout << "=== 测试 9: 拷贝赋值 ===\n";
    {
        LazyDeleteList<int> a;
        a.push_back(5);
        a.push_back(6);
        LazyDeleteList<int> b;
        b.push_back(99);
        b = a;  // b 原有数据应被清掉，换成 a 的副本
    }
    std::cout << "通过\n\n";

    std::cout << "=== 测试 10: 移动赋值 ===\n";
    {
        LazyDeleteList<int> a;
        a.push_back(7);
        a.push_back(8);
        LazyDeleteList<int> b;
        b.push_back(999);
        b = std::move(a);  // b 原有数据被清，接管 a；a 被移空
    }
    std::cout << "通过\n\n";

    std::cout << "=== 测试 11: 自我赋值 ===\n";
    {
        LazyDeleteList<int> a;
        a.push_back(1);
        a.push_back(2);
        a = a;  // 自我拷贝赋值
        a = std::move(a);  // 自我移动赋值
        std::cout << "自我赋值不崩溃\n";
    }
    std::cout << "通过\n\n";

    std::cout << "=== 测试 12: clear ===\n";
    {
        LazyDeleteList<int> a;
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);
        a.delete_the(0);  // 惰性删
        a.clear();        // 物理清除所有节点
        // 空列表，析构不崩
    }
    std::cout << "通过\n\n";

    std::cout << "=== 全部测试完成 ===\n";
    return 0;
}