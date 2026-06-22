#include <list>
#include <iostream>
using std::list;
using std::cout;

template <typename Comparable>
list<Comparable> CapList(const list<Comparable>& L_1, const list<Comparable>& L_2) {
    list<Comparable> L_1CapL_2;
    auto itr = L_2.begin();
    for(const Comparable& i : L_1) {
        while(itr != L_2.end() && *itr < i) ++itr;
        if(itr != L_2.end() && *itr == i) L_1CapL_2.push_back(i);
    }
    return L_1CapL_2;
}

template <typename Comparable>
list<Comparable> CupList(const list<Comparable>& L_1, const list<Comparable>& L_2) {
    list<Comparable> L_1CupL_2;
    auto itr = L_2.begin();
    for(const Comparable& i : L_1) {
        while(itr != L_2.end() && *itr < i) {
            if(L_1CupL_2.empty()) L_1CupL_2.push_back(*itr);
            else if(*itr != L_1CupL_2.back()) L_1CupL_2.push_back(*itr);
            ++itr;
        }
        if(L_1CupL_2.empty()) L_1CupL_2.push_back(i);
        else if(i != L_1CupL_2.back()) L_1CupL_2.push_back(i);
    }
    while(itr != L_2.end()) {
        if(L_1CupL_2.empty()) L_1CupL_2.push_back(*itr);
        else if(*itr != L_1CupL_2.back()) L_1CupL_2.push_back(*itr);
        ++itr;
    }
    return L_1CupL_2;
}

int main() {
    list<int> L_1 = {0,3,5,6,7,10};
    list<int> L_2 = {-1,0,2,3,7,8,9,11};
    list<int> L_3 = CapList(L_1, L_2);
    list<int> L_4 = CupList(L_1, L_2);
    for(int i : L_3) cout << i << "\n";
    for(int i : L_4) cout << i << "\n";
}