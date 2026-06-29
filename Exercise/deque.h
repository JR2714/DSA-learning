#include <stdexcept>
#include <cstddef>
#include <utility>

// 支持可拷贝数据类型T
template <typename T>
class Deque {
    private:
        size_t capacity_;
        size_t size_;
        T* arr_;
        size_t head_;
        size_t tail_;

        // 扩容
        void reserve(size_t new_capacity) {
            T* temp = new T[new_capacity];
            for(size_t curr = 0; curr < size_; ++curr) {
                temp[curr] = arr_[(head_ + curr) % capacity_];
            }
            head_ = 0;
            tail_ = size_ - 1;
            delete[] arr_;
            arr_ = temp;
            capacity_ = new_capacity;
        }

    public:
        // 构造函数
        explicit Deque(size_t init_capacity = size_t{})
        :capacity_{init_capacity + 1}
        ,size_{0}
        ,arr_{new T[capacity_]} {
            head_ = 0;
            tail_ = capacity_ - 1;
        }
        
        // 析构函数
        ~Deque() {
            delete[] arr_;
        }
        
        // 拷贝构造函数
        Deque(const Deque& other)
        :capacity_{other.capacity_}
        ,size_{other.size_}
        ,arr_{new T[other.capacity_]}
        ,head_{other.head_}
        ,tail_{other.tail_} {
            if(size_ != 0) {
                size_t i = head_;
                for(size_t j = 0; j < size_; ++j) {
                    arr_[i % capacity_] = other.arr_[i % capacity_];
                    ++i;
                }
                
            }
        }

        // 移动赋值
        Deque& operator=(Deque&& other) noexcept {
            if(this != &other) {
                delete[] arr_;
                arr_ = other.arr_;
                other.arr_ = nullptr;
                capacity_ = other.capacity_;
                size_ = other.size_;
                head_ = other.head_;
                tail_ = other.tail_;
                other.capacity_ = other.size_ = 0;
                other.head_ = other.tail_ = 0;
            }
            return *this;
        }

        // 拷贝赋值
        Deque& operator=(const Deque& other) {
            if(this != &other) {
                Deque temp_deque(other);
                *this = std::move(temp_deque);
            }
            return *this;
        }

        // 移动构造
        Deque(Deque&& other) noexcept 
        :capacity_{other.capacity_}
        ,size_{other.size_}
        ,arr_{other.arr_}
        ,head_{other.head_}
        ,tail_{other.tail_}{
            other.arr_ =nullptr;
            other.capacity_ = other.size_ = 0;
            other.head_ = other.tail_ = 0;
        }

        // 前端推入
        void push(const T& x) {
            if(size_ == capacity_) {
                reserve(2 * capacity_ + 1);
            }
            head_ = head_ == 0 ? capacity_ - 1 : head_ - 1;
            arr_[head_] = x;
            ++size_;
        }
        
        // 前端删除
        T pop() {
            if(size_ == 0) {
                throw std::logic_error("Try to pop from an empty queue!");
            }
            T temp = std::move(arr_[head_]);
            head_ = (head_ + 1) % capacity_;
            --size_;
            return temp;
        }

        // 后端推入
        void inject(const T& x) {
            if(size_ == capacity_) {
                reserve(2 * capacity_ + 1);
            }
            tail_ = (tail_ + 1) % capacity_;
            arr_[tail_] = x;
            ++size_;
        }

        // 后端删除
        T eject() {
            if(size_ == 0) {
                throw std::logic_error("Try to eject from an empty queue!");
            }
            T temp = std::move(arr_[tail_]);
            tail_ = tail_ == 0 ? capacity_ - 1 : tail_ - 1;
            --size_;
            return temp;
        }

        // 获取大小
        size_t size() const {
                return size_;
        }
};
