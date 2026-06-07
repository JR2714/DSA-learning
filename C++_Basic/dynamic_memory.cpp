#include <iostream>
// using std::cin;
using std::cout;
using std::endl;

int main() {
    const size_t N = 8;
    cout << "第一题：\n";
    // int N = 1;
    // do {
    //     cout << "请输入需要数列的前几项：\n";
    //     cin >> N;
    // }
    // while (N <=0);
    
    if (N <= 0)
        cout << "[]" << endl;
    else if (N == 1)
        cout << "[0]" << endl;
    else if (N == 2)
        cout << "[0, 1]" << endl;
    else {
        int* p = new int[N]();
        *p = 0;
        cout << "[0, ";
        *(p + 1) = 1;
        cout << "1, ";
        for(size_t i = 2; i < N; i++) {
            *(p + i) = *(p + i - 1) + *(p + i - 2);
            if (i < N - 1)
                cout << *(p + i) << ", ";
            else
                cout << *(p + i) << "]" << endl;
        }
        delete[] p; 
        p = nullptr;
    }

    cout << "第二题：\n";
    int* q = new int(100);
    cout << *q << endl;
    delete q;
    q = nullptr;

    //第三题思考：上面的数组本身和那个整型实在堆里面，而创建的指针则是再栈里面。



}