// Array.h
// #pragma once
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class Array
{
    private:
        T* data_;
        size_t size_;

    public:
        Array(size_t n);
        ~Array();
        Array(const Array& other);
        Array& operator=(const Array& other);
        Array(Array&& other) noexcept;
        Array& operator=(Array&& other) noexcept;
        size_t size() const;
        T& operator[](size_t i);
        const T& operator[](size_t i) const;
        void print(const char* label) const;
};

template <typename T>
Array<T>::Array(size_t n) //构造函数
    : data_(new T[n]())
    , size_(n)
{
    cout << "执行构造函数" << endl;
}

template <typename T>
Array<T>::~Array()  //析构函数
{
    cout << "执行析构函数" << endl;
    delete[] data_;
    data_ = nullptr;
}

template <typename T>
Array<T>::Array(const Array& other)  //拷贝构造
    : data_(new T[other.size_])
    , size_(other.size_)
{
    cout << "执行拷贝构造函数" << endl;
    for(size_t i = 0; i < size_; i++)
        data_[i] = other.data_[i];
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other)  //拷贝赋值符号函数
{
    cout << "执行拷贝赋值符号函数" << endl;
    if (this == &other) // 自赋值检查
        return *this;

    delete[] data_;

    size_ = other.size_;
    data_ = new T[size_];
    
    for(size_t i = 0; i < size_; i++) // 深拷贝
        data_[i] = other.data_[i];

    return *this;
}

template <typename T>
Array<T>::Array(Array&& other) noexcept //移动构造函数
    : data_(other.data_)
    , size_(other.size_)
{
    cout << "执行移动构造函数" << endl;
    other.data_ = nullptr;
    other.size_ = 0;
}

template <typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept //移动赋值符号函数
{
    cout << "执行移动赋值符号函数" << endl;
    if (this == &other) // 自赋值检查
        return *this;

    delete[] data_;

    size_ = other.size_;
    data_ = other.data_;

    other.data_ = nullptr;
    other.size_ = 0;

    return *this;
}

template <typename T> //我试试改个名字，好像L也可以
size_t Array<T>::size() const // 获取数组大小
{
    return size_;
}

template <typename T>
T& Array<T>::operator[](size_t i) //查询数组
{
    return data_[i];
}

template <typename T>
const T& Array<T>::operator[](size_t i) const //查询常量数组
{
    return data_[i];
}

template <typename T>
void Array<T>::print(const char* label) const //打印数组详情
{
    cout << "{\n数组名为：" << label << endl;
    cout << "数组大小：" << size_ << endl;
    cout << "数组为：" << endl;
    if (size_ == 0)
        cout << "[]\n}" << endl;
    else
    {
        cout << "[";
        for(size_t i = 0; i < size_; i++)
        {
            if (i == size_ - 1)
                cout << data_[i] << "]\n}\n";
            else
                cout << data_[i] << ", ";
        }
    }
}

// main.cpp
#include <iostream>
#include <utility>
#include <string>
using std::cout;
using std::endl;
using std::string;

int main()
{
    Array<int> my_arr_i(4);
    my_arr_i[0] = 10;
    my_arr_i[1] = 20;
    my_arr_i[2] = 30;
    my_arr_i[3] = 40;
    my_arr_i.print("my_arr_i");

    Array<double> my_arr_d(4);
    my_arr_d[0] = 1.3;
    my_arr_d[1] = 2.17;
    my_arr_d[2] = 3.14;
    my_arr_d[3] = 1.2;
    my_arr_d.print("my_arr_d");

    Array<string> my_arr_s(4);
    my_arr_s[0] = "What";
    my_arr_s[1] = "a great";
    my_arr_s[2] = "job";
    my_arr_s[3] = "!";
    my_arr_s.print("my_arr_s");

    // 拷贝构造测试
    Array<int> my_arr_i_1 = my_arr_i;
    my_arr_i_1.print("my_arr_i_1");
    my_arr_i_1[0] = 99;
    my_arr_i.print("my_arr_i(test deepcopy)");

    // 拷贝赋值符号测试
    Array<double> my_arr_d_1(3);
    my_arr_d_1 = my_arr_d;
    my_arr_d_1.print("my_arr_d_1");
    my_arr_d_1 = my_arr_d_1; // 自拷贝

    // 移动构造测试
    Array<string> my_arr_s_1 = std::move(my_arr_s);
    my_arr_s_1.print("my_arr_s_1");

    // 移动赋值符号测试
    my_arr_i = std::move(my_arr_i_1);
    my_arr_i.print("my_arr_i");
    my_arr_i_1.print("my_arr_i_1(have been moved)");

    return 0;
}
