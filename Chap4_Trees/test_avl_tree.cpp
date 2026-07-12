#include "avl_tree.h"
#include <iostream>

int main() {
    AVLTree<int> avl_tree;
    avl_tree.Insert(20);
    avl_tree.Insert(10);
    avl_tree.Insert(30);
    avl_tree.Insert(5);
    avl_tree.Insert(15);
    avl_tree.Insert(25);
    avl_tree.Insert(35);
    avl_tree.Insert(3);
    avl_tree.Insert(2);
    avl_tree.Insert(1);
    avl_tree.Insert(0);
    std::cout << avl_tree.GetHeight() << "\n";
    avl_tree.Delete(20);
    avl_tree.Delete(30);
    avl_tree.PrintInOrder();
    std::cout << avl_tree.GetHeight() << "\n";
}