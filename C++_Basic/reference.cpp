# include <iostream>
using namespace std;

void increment(int& x) {
    x += 1;
}

void print(const string& s) {
    cout << s << endl;
}

const int& max_of_three(const int& a, const int& b, const int& c) {
    if (a > b)
        if (a > c)
            return a;
        else
            return c;
    else if (b > c)
        return b;
    else 
        return c;
    
} //这样return安全是因为传入时用的外部调用者的引用，因此函数结束时不会销毁。

void swap_reference(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
} //和引用版的区别在于传入函数的参数从引用变为了指针，函数体swap的时候需要间接访问。

int main() {
    cout << "第一题：\n";
    int first = 4;
    increment(first);
    cout << first << endl;
    print("asdfasdfasdfafasdfagag\n");

    cout << "第二题：\n";
    cout << max_of_three(3, 5, 1000) << endl << endl;

    cout << "第三题：\n";
    int third_1 = 1;
    int third_2 = 2;
    swap_reference(third_1, third_2);
    cout << "third_1为" << third_1 << endl << "third_2为" << third_2 << endl;
    swap(&third_1, &third_2);
    cout << "third_1为" << third_1 << endl << "third_2为" << third_2 << endl;
}