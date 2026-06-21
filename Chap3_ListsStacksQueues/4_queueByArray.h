#include <vector>
#include <utility>
#include <algorithm>
#include <stdexcept>
using std::vector;
using std::swap;
using std::move;


template <typename T>
class Queue {
    private:
        vector<T> arr;
        size_t front = 0;
        size_t back = -1;
        size_t currentSize = 0;

    public:
        explicit Queue(size_t capacity = 10)
        : arr(capacity) {}

        void enqueue(const T& x) { // 入队
            if(currentSize == arr.size()) { // 扩容2
                vector<T> arr_temp(2*arr.size() + 1);
                for(size_t i = 0; i < currentSize; ++i) {
                    arr_temp[i] = arr[(front + i) % arr.size()];
                }
                swap(arr_temp, arr);
                front = 0;
                back = currentSize - 1;
            }

            back = (back + 1) % arr.size();
            arr[back] = x;
            ++currentSize;
        }

        T dequeue() { // 出队
            if(currentSize == 0) throw std::underflow_error("Empty queue!");
            T val = move(arr[front]);
            front = (front + 1) % arr.size();
            --currentSize;
            return val;
        }

        T getFront() const { // 查看队首
            if (empty()) throw std::underflow_error("Empty queue!");
            return arr[front];
        }

        bool empty() const { // 判断是否为空队列
            return currentSize == 0;
        }

        size_t size() const { // 返回当前队列长度
            return currentSize;
        }

        void clear() { //清空队列
            front = 0;
            back = -1;
            currentSize = 0;
        }
};