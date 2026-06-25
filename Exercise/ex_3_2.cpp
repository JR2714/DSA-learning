#include "../Chap3_ListsStacksQueues/2_SList.h"
#include "DList.h"
#include <iostream>

int main() {
    SList Sl;
    Sl.push_front(1);
    Sl.push_front(2);
    Sl.push_front(3);
    Sl.print();
    Sl.swap_neighbor(1);
    Sl.print();
    Sl.swap_neighbor(0);
    Sl.print();

    std::cout << "\n";
    
    DList<int> Dl;
    Dl.push_front(1);
    Dl.push_front(2);
    Dl.push_front(3);
    Dl.print();
    Dl.swap_neighbor(1);
    Dl.print();
    Dl.swap_neighbor(0);
    Dl.print();

}