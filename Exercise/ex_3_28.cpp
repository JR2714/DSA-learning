#include "deque.h"
#include <iostream>
#include <string>
#include <cassert>

// 辅助函数：打印 deque 内容（仅用于调试，不依赖 deque 内部迭代器）
template<typename T>
void printDeque(const Deque<T>& dq, const std::string& label = "") {
    // 由于 Deque 未提供遍历接口，此处我们通过拷贝构造来间接验证，或者直接使用已知的公共接口无法遍历，
    // 但我们可以使用 push/pop 来测试，这里只做简单输出。
    std::cout << label << " : size = " << dq.size() << " (无法直接打印内容)\n";
}

int main() {
    try {
        std::cout << "=== 测试 Deque 类 ===\n\n";

        // 1. 默认构造与基本操作 (int)
        std::cout << "1. 测试 int 类型基本操作\n";
        Deque<int> dq;
        assert(dq.size() == 0);
        
        dq.push(10);
        dq.push(20);
        dq.inject(30);
        dq.inject(40);
        // 预期队列：从前往后：20, 10, 30, 40
        assert(dq.size() == 4);
        assert(dq.pop() == 20);    // 弹出前端
        assert(dq.pop() == 10);
        assert(dq.eject() == 40);  // 弹出后端
        assert(dq.eject() == 30);
        assert(dq.size() == 0);
        std::cout << "   int 基本操作通过\n";

        // 2. 测试扩容 (push 和 inject 触发 reserve)
        std::cout << "2. 测试扩容\n";
        Deque<int> dq2;
        for (int i = 0; i < 20; ++i) {
            dq2.push(i);
        }
        assert(dq2.size() == 20);
        // 验证顺序：由于每次 push 在前端插入，最终顺序应该是 19,18,...,0
        for (int i = 19; i >= 0; --i) {
            assert(dq2.pop() == i);
        }
        assert(dq2.size() == 0);
        std::cout << "   扩容测试通过\n";

        // 3. 测试拷贝构造
        std::cout << "3. 测试拷贝构造\n";
        Deque<int> dq3;
        dq3.push(1);
        dq3.push(2);
        dq3.inject(3);
        // dq3: 前端顺序: 2,1,3
        Deque<int> dq4(dq3); // 拷贝
        assert(dq4.size() == dq3.size());
        assert(dq4.pop() == 2);
        assert(dq4.pop() == 1);
        assert(dq4.pop() == 3);
        assert(dq4.size() == 0);
        // 原对象应不受影响
        assert(dq3.size() == 3);
        std::cout << "   拷贝构造通过\n";

        // 4. 测试移动构造
        std::cout << "4. 测试移动构造\n";
        Deque<int> dq5;
        dq5.push(100);
        dq5.push(200);
        Deque<int> dq6(std::move(dq5));
        assert(dq6.size() == 2);
        assert(dq6.pop() == 200);
        assert(dq6.pop() == 100);
        assert(dq5.size() == 0); // 被移动对象应为空
        std::cout << "   移动构造通过\n";

        // 5. 测试拷贝赋值
        std::cout << "5. 测试拷贝赋值\n";
        Deque<int> dq7;
        dq7.push(5);
        dq7.push(6);
        Deque<int> dq8;
        dq8 = dq7;
        assert(dq8.size() == 2);
        assert(dq8.pop() == 6);
        assert(dq8.pop() == 5);
        std::cout << "   拷贝赋值通过\n";

        // 6. 测试移动赋值
        std::cout << "6. 测试移动赋值\n";
        Deque<int> dq9;
        dq9.push(7);
        dq9.push(8);
        Deque<int> dq10;
        dq10 = std::move(dq9);
        assert(dq10.size() == 2);
        assert(dq10.pop() == 8);
        assert(dq10.pop() == 7);
        assert(dq9.size() == 0);
        std::cout << "   移动赋值通过\n";

        // 7. 测试字符串类型 (非POD)
        std::cout << "7. 测试 std::string 类型\n";
        Deque<std::string> dq_str;
        dq_str.push("hello");
        dq_str.inject("world");
        dq_str.push("!");
        // 顺序：!, hello, world
        assert(dq_str.pop() == "!");
        assert(dq_str.pop() == "hello");
        assert(dq_str.pop() == "world");
        assert(dq_str.size() == 0);
        std::cout << "   string 类型测试通过\n";

        // 8. 异常测试 (空队列 pop/eject)
        std::cout << "8. 测试空队列异常\n";
        Deque<int> dq_empty;
        bool caught = false;
        try {
            dq_empty.pop();
        } catch (const std::logic_error& e) {
            caught = true;
            std::cout << "   捕获到 pop 异常: " << e.what() << "\n";
        }
        assert(caught);
        caught = false;
        try {
            dq_empty.eject();
        } catch (const std::logic_error& e) {
            caught = true;
            std::cout << "   捕获到 eject 异常: " << e.what() << "\n";
        }
        assert(caught);
        std::cout << "   异常测试通过\n";

        // 9. 边界测试：大量元素，观察性能和正确性
        std::cout << "9. 大量元素测试 (10000个)\n";
        Deque<int> dq_big;
        for (int i = 0; i < 10000; ++i) {
            dq_big.inject(i);
        }
        assert(dq_big.size() == 10000);
        for (int i = 0; i < 10000; ++i) {
            assert(dq_big.pop() == i);
        }
        assert(dq_big.size() == 0);
        std::cout << "   大量元素测试通过\n";

        std::cout << "\n所有测试通过！\n";
    } catch (const std::exception& e) {
        std::cerr << "测试失败，异常: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
