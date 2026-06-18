#include <iostream>
#include <utility>

class SimpleVector {
    private:
        int theCapacity;
        int theSize;
        static const int SPARE_CAPACITY = 2;
        int* data;
    public:
        explicit SimpleVector(int initSize = 0) // 禁用隐式构造
        : theCapacity{initSize + SPARE_CAPACITY}
        , theSize{initSize} {
            data = new int[theCapacity];
        }

        ~SimpleVector() { //析构函数
            delete[] data;
        }

        void reserve(int newCapacity) { // 为push_back做准备
            if(newCapacity < theSize) {
                return;
            }

            int* newArray = new int [newCapacity];
            for(int i = 0; i < theSize; ++i) {
                newArray[i] = std::move(data[i]);
            }
            std::swap(newArray, data);
            delete[] newArray;
            theCapacity = newCapacity;
        }

        void push_back(int x) { //末尾增加元素
            if (theSize == theCapacity) { //符合条件扩容
                reserve(2*theCapacity + 1);
            }
            data[theSize++] = x; //先对data[theSize]位置赋值x，再将theSize加一以记录当前元素个数
        }

        int size() const { //获取SimpleVector大小
            return theSize;
        }

        int& operator[] (int index) { //获取指定索引的值
            return data[index];
        }

        int capacity() const { //获取分配的内存大小
            return theCapacity;
        }

        SimpleVector& operator=(const SimpleVector&) = delete;

        SimpleVector(const SimpleVector&) = delete;
};

  int main() {
      SimpleVector v;
      for (int i = 0; i < 20; ++i)
          v.push_back(i * 10);

      for (int i = 0; i < v.size(); ++i)
          std::cout << v[i] << " ";
      std::cout << "\nsize=" << v.size() << " cap=" << v.capacity() << std::endl;
  }