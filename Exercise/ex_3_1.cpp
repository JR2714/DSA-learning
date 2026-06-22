#include <list>
#include <iostream>
#include <stdexcept>
using std::cout;
using std::list;

void printLots(const list<int>& L, const list<int>& P) {
    auto itr = L.begin();
    int prev = 0;
    for(int idx : P) {
        if (static_cast<size_t>(idx) >= L.size() || idx < 0) {
            throw std::out_of_range("索引超出范围！");
        }
        int steps = idx - prev;
        while (steps--) ++itr;
        prev = idx;
        cout << *itr << "\n";
    }
}

int main() {
    list<int> L = {3,2,4,5,6};
    list<int> P = {0,3,4,7}; // 7超出索引范围
    printLots(L, P);
}

// 本题实现的时间复杂度为O(P+L)，但就查找输出这个功能来说，vector比题目要求的list更加适合。