#include <iostream>
using std::cout;
using std::endl;
 
class IntArray 
{
    private:
        int* data_;
        size_t size_;

    public:
        IntArray(size_t n);
        ~IntArray();
        IntArray(const IntArray& other);
        IntArray& operator=(const IntArray& other);
        size_t size() const;
        int& operator[](size_t i);
        const int& operator[](size_t i) const;
};

IntArray::IntArray(size_t n) //整数数组构造
    : data_(new int[n]())
    , size_(n)
{
    cout << "执行构造函数" << endl;
}

IntArray::~IntArray() //析构函数，释放堆上的数组
{
    cout << "执行析构函数" << endl;
    delete[] data_;
    data_ = nullptr;
}

IntArray::IntArray(const IntArray& other) // 拷贝构造
    : data_(new int[other.size_])         // 分配新内容
    , size_(other.size_)            
{
    cout << "执行拷贝构造函数" << endl;
    for(size_t i = 0; i < other.size_; i++)
        data_[i] = other.data_[i];  // 深拷贝
}

IntArray& IntArray::operator=(const IntArray& other) //拷贝赋值
{    
    cout << "执行拷贝赋值函数" << endl;
    if (this == &other)
        return *this;              // 防止自拷贝

    delete[] data_;                // 释放空间

    size_ = other.size_;
    data_ = new int[size_];
    for(size_t i = 0; i < size_; i++)
        data_[i] = other.data_[i]; // 赋值
    
    return *this;
}

size_t IntArray::size() const
{
    return size_;
}

int& IntArray::operator[](size_t i)
{
    return data_[i];
}

const int& IntArray::operator[](size_t i) const
{
    return data_[i];
}

int main()
{
    IntArray vd(0); // 空数组测试
    IntArray vd_1 = vd; //空数组的拷贝构造
    IntArray a(4);
    a[0] = 99;
    a[1] = 98;
    a[2] = 97;
    a[3] = 96;
    for(size_t i = 0; i < a.size(); i++)
        cout << a[i] << endl;

    IntArray b = a; // 拷贝构造
    for(size_t i = 0; i < b.size(); i++)
        cout << b[i] << endl;
    b[2] = 2;
    cout << a[2] << endl; // 测试深拷贝

    IntArray c(5);
    c = a; // 拷贝赋值
    for(size_t i = 0; i < c.size(); i++)
        cout << c[i] << endl;
    c[2] = 3;
    cout << a[2] << endl; //测试深拷贝

    a = b = c; // 结果是将最右边的值赋给前面两个
    for(size_t i = 0; i < a.size(); i++)
        cout << a[i] << endl;

    a = a; // 测试自赋值

    const IntArray cia(3);
    for(size_t i = 0; i < cia.size(); i++)
        cout << cia[i] << endl;
}
// 1.假若没写拷贝构造函数，编译器将自动编写拷贝构造函数，在拷贝时进行浅拷贝，
//   这时对于指针的拷贝会直接拷贝地址，在改动任意一个时两个都会被改动，析构是还会双重释放导致崩溃。
// 2.没写拷贝赋值时，同拷贝构造函数，改一个等于改所有，且存在双重释放的问题。
// 3.自赋值检查 if (this == &other) 是必须的，否则直接进入内存释放，该实体直接消失了，后面程序会报错。
// 4.若拷贝赋值如果写成传值（而非传 const 引用），执行拷贝赋值时会多创造一个实体出来，浪费内存。