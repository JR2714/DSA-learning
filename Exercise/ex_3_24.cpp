#include <stdexcept>
#include <iostream>
#include <utility>
#include <cstddef> // 用于size_t

template <typename T>
class DoubleStacks {
    private:
        T* arr_;
        size_t left_size_ = 0;
        size_t right_size_ = 0;
        size_t N_ = 0;

    public:
        // 构造函数，禁用隐式构造
        explicit DoubleStacks(size_t initN)
        :arr_{new T[initN]()}
        ,N_{initN} {}

        ~DoubleStacks() {
            delete[] arr_;
        }

        // 拷贝构造函数
        DoubleStacks(const DoubleStacks<T>& other) // Rule of Five需要补全拷贝构造/赋值、移动构造/赋值
        :arr_{new T[other.N_]}
        ,left_size_{other.left_size_}
        ,right_size_{other.right_size_}
        ,N_{other.N_} {
            for(size_t i = 0; i < left_size_; ++i) arr_[i] = other.arr_[i];
            for(size_t i = 0; i < right_size_; ++i) arr_[N_ - i - 1] = other.arr_[N_ - i - 1];
        }

        // 拷贝赋值函数
        DoubleStacks& operator=(const DoubleStacks& other) {
            if(this == &other) return *this; // 检查自拷贝

            DoubleStacks temp(other); // 先分配内存，保证异常安全
            std::swap(*this, temp);
            
            return *this;
        }

        // 移动构造函数
        DoubleStacks(DoubleStacks&& other) noexcept // noexcept确保优先使用，提高效率
        :arr_{other.arr_}
        ,left_size_{other.left_size_}
        ,right_size_{other.right_size_}
        ,N_{other.N_} {
            other.arr_ = nullptr;
            other.N_ = other.left_size_ = other.right_size_ = 0; // 原先的位置已交给新的
        }

        // 移动赋值函数
        DoubleStacks& operator=(DoubleStacks&& other) noexcept{
            if(this == &other) return *this; // 防止自赋值

            delete[] arr_;

            arr_ = other.arr_;
            N_ = other.N_;
            left_size_ = other.left_size_;
            right_size_ = other.right_size_;

            other.arr_ = nullptr;
            other.N_ = other.left_size_ = other.right_size_ = 0;

            return *this;
        }

        // 左栈进入函数
        void LeftStackPush(const T& x) {
            if(left_size_ + right_size_ >= N_) throw std::overflow_error("栈溢出！");
            else {
                arr_[left_size_] = x;
                ++left_size_;
            }
        }

        void LeftStackPush(T&& x) {
            if(left_size_ + right_size_ >= N_) throw std::overflow_error("栈溢出！");
            else {
                arr_[left_size_] = std::move(x);
                ++left_size_;
            }
        }

        //右栈进入函数
        void RightStackPush(const T& x) {
            if(left_size_ + right_size_ >= N_) throw std::overflow_error("栈溢出！");
            else {
                arr_[N_ - right_size_ - 1] = x;
                ++right_size_;
            }
        }

        void RightStackPush(T&& x) {
            if(left_size_ + right_size_ >= N_) throw std::overflow_error("栈溢出！");
            else {
                arr_[N_ - right_size_ - 1] = std::move(x);
                ++right_size_;
            }
        }

        //左栈出函数
        T LeftStackPop() {
            if(left_size_ == 0) throw std::underflow_error("试图从空栈中移除！");
            else {
                T val = std::move(arr_[left_size_ - 1]);
                --left_size_;
                return val;
            }
        }

        // 右栈出函数
        T RightStackPop() {
            if(right_size_ == 0) throw std::underflow_error("试图从空栈中移除！");
            else {
                T val = std::move(arr_[N_ - right_size_]);
                --right_size_;
                return val;
            }
        }

        // 查询栈顶
        const T& LeftTop() const {
            if(left_size_ == 0) throw std::underflow_error("空栈无法查看栈顶数据！");
            else {
                return arr_[left_size_ - 1];
            }
        }

        const T& RightTop() const {
            if(right_size_ == 0) throw std::underflow_error("空栈无法查看栈顶数据！");
            else {
                return arr_[N_ - right_size_];
            }
        }
};

// 测试用 main — 覆盖拷贝/移动/赋值/自赋值路径
int main() {
    // 基础功能测试
    {
        std::cout << "=== 基础功能 ===\n";
        DoubleStacks<int> DS(10);
        for(size_t i = 0; i < 10; ++i) DS.LeftStackPush(static_cast<int>(i));
        std::cout << "左栈出: " << DS.LeftStackPop() << "\n";
        DS.RightStackPush(999);
        std::cout << "左栈出: " << DS.LeftStackPop() << "\n";
        DS.RightStackPush(1000);
        std::cout << "左栈顶: " << DS.LeftTop() << "\n";
        std::cout << "右栈顶: " << DS.RightTop() << "\n";
    }
    std::cout << "\n";

    // 拷贝构造测试
    {
        std::cout << "=== 拷贝构造 ===\n";
        DoubleStacks<int> A(5);
        A.LeftStackPush(10);
        A.RightStackPush(20);
        DoubleStacks<int> B(A);              // 拷贝构造
        std::cout << "A.左顶: " << A.LeftTop() << "\n";
        std::cout << "B.左顶: " << B.LeftTop() << "\n";  // 应 == 10
        std::cout << "A.右顶: " << A.RightTop() << "\n";
        std::cout << "B.右顶: " << B.RightTop() << "\n";  // 应 == 20
    }
    std::cout << "\n";

    // 拷贝赋值测试
    {
        std::cout << "=== 拷贝赋值 ===\n";
        DoubleStacks<int> A(5);
        A.LeftStackPush(42);
        DoubleStacks<int> B(10);
        B.LeftStackPush(99);
        B = A;                                 // 拷贝赋值 (不同大小)
        std::cout << "A.左顶: " << A.LeftTop() << "\n";
        std::cout << "B.左顶: " << B.LeftTop() << "\n";  // 应 == 42
    }
    std::cout << "\n";

    // 自赋值测试 (拷贝)
    {
        std::cout << "=== 拷贝自赋值 ===\n";
        DoubleStacks<int> A(5);
        A.LeftStackPush(77);
        A = A;                                 // 自赋值
        std::cout << "A.左顶: " << A.LeftTop() << "\n";  // 应 == 77
    }
    std::cout << "\n";

    // 移动构造测试
    {
        std::cout << "=== 移动构造 ===\n";
        DoubleStacks<int> A(5);
        A.LeftStackPush(33);
        A.RightStackPush(44);
        DoubleStacks<int> B(std::move(A));     // 移动构造
        std::cout << "B.左顶: " << B.LeftTop() << "\n";  // 应 == 33
        std::cout << "B.右顶: " << B.RightTop() << "\n";  // 应 == 44
    }
    std::cout << "\n";

    // 移动赋值测试
    {
        std::cout << "=== 移动赋值 ===\n";
        DoubleStacks<int> A(5);
        A.LeftStackPush(55);
        DoubleStacks<int> B(10);
        B = std::move(A);                      // 移动赋值
        std::cout << "B.左顶: " << B.LeftTop() << "\n";  // 应 == 55
    }
    std::cout << "\n";

    // 移动自赋值测试
    {
        std::cout << "=== 移动自赋值 ===\n";
        DoubleStacks<int> A(5);
        A.LeftStackPush(88);
        A = std::move(A);                      // 移动自赋值
        std::cout << "A.左顶: " << A.LeftTop() << "\n";  // 应 == 88
    }
    std::cout << "\n";

    // 右值 push 测试
    {
        std::cout << "=== 右值 push ===\n";
        DoubleStacks<int> DS(5);
        DS.LeftStackPush(111);                 // 右值版本
        DS.RightStackPush(222);                // 右值版本
        std::cout << "左顶: " << DS.LeftTop() << "\n";
        std::cout << "右顶: " << DS.RightTop() << "\n";
    }

    return 0;
}