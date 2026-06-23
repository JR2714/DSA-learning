#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>

template <typename T>
class StackWithMin {
    private:
        std::vector<T> stack_;
        std::vector<T> min_; // 新分配栈用于储存到对应堆顶时的最小元素
    
    public:
        // 入栈操作
        void push(const T& x) {
            stack_.push_back(x);
            // 将当前栈中最小值push进min_栈顶
            if(min_.empty() || x < min_.back()) {
                min_.push_back(x);
            } else {
                min_.push_back(min_.back());
            }
        }

        // 出栈操作
        void pop() {
            if(stack_.empty()) throw std::underflow_error("试图从空栈中删除元素！");
            stack_.pop_back();
            min_.pop_back();
        }

        // 查找当前最小
        const T& min() const {
            if(stack_.empty()) throw std::underflow_error("试图从空栈中查找最小元素！");
            return min_.back();
        }
};

int main() {
    try {
        // 1. 基本操作
        StackWithMin<int> s;
        s.push(5);
        s.push(3);
        s.push(7);
        s.push(2);
        std::cout << "Min: " << s.min() << std::endl;          // 应输出 2

        s.pop();
        std::cout << "Min after pop: " << s.min() << std::endl; // 应输出 3

        s.push(1);
        std::cout << "Min after push 1: " << s.min() << std::endl; // 应输出 1

        // 2. 拷贝构造
        StackWithMin<int> s2 = s;
        std::cout << "s2 min: " << s2.min() << std::endl;      // 应输出 1
        s2.pop();
        std::cout << "s2 min after pop: " << s2.min() << std::endl; // 应输出 3
        std::cout << "s min unchanged: " << s.min() << std::endl;   // 仍为 1

        // 3. 移动构造
        StackWithMin<int> s3 = std::move(s);
        std::cout << "s3 min: " << s3.min() << std::endl;      // 应输出 1
        // 此时 s 为空，不再使用

        // 4. 异常测试（可选）
        // StackWithMin<int> empty;
        // empty.min();   // 会抛异常
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}