#include "4_queueByArray.h"
#include <iostream>
#include <stdexcept>
using std::cout;
using std::cin;

int Josephus(size_t N, size_t M) {
    if(N == 0 || M == 0) {
        throw std::logic_error("人数和数的数不能为非正数！");
    }
    Queue<int> win(N);
    for(size_t i = 1; i <= N; ++i) {
        win.enqueue(i);
    }

    while(win.size() != 1) {
        for(size_t i = 0; i < M - 1; ++i) {
            win.enqueue(win.dequeue());
        }
        cout << win.dequeue() << "号出局！\n";
    }

    cout << win.getFront() << "号是赢家！\n";
    return win.getFront();
}

int main() {
    size_t N = 7, M = 3;
    cout << "请输入人数：\n";
    cin >> N;
    cout << "请输入单次数的数字：\n";
    cin >> M;
    Josephus(N, M);
}