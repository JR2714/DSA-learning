// 测试用 —— 测试 countLeaves 和 BST 基本操作
#include <iostream>
#include <cassert>
#include "binary_search_tree_with_count_leaves.h"
using namespace std;

int main() {
    // Test 1: Empty tree
    BinarySearchTree<int> empty;
    cout << "Empty tree leaves: " << empty.countLeaves() << " (expected 0)" << endl;
    assert(empty.countLeaves() == 0);

    // Test 2: Single node
    BinarySearchTree<int> single;
    single.insert(5);
    cout << "Single node leaves: " << single.countLeaves() << " (expected 1)" << endl;
    assert(single.countLeaves() == 1);

    // Test 3: Two nodes (root + left child)
    BinarySearchTree<int> two;
    two.insert(5);
    two.insert(3);
    cout << "Two nodes (5->3) leaves: " << two.countLeaves() << " (expected 1)" << endl;
    assert(two.countLeaves() == 1);

    // Test 4: The tree from exercise 4.1
    BinarySearchTree<int> t;
    int seq[] = {5, 3, 7, 2, 4, 6, 9, 1, 8};
    for (int x : seq) t.insert(x);
    cout << "Full tree leaves: " << t.countLeaves() << " (expected 4: 1,4,6,8)" << endl;
    assert(t.countLeaves() == 4);

    // Test 5: After deletion (remove 5, which has two children)
    t.remove(5);
    cout << "After deleting root(5): ";
    t.printTree(cout);
    cout << "Leaves: " << t.countLeaves() << " (expected 4: 1,4,6?,8?)" << endl;

    // Test 6: Delete a leaf
    t.remove(1);
    cout << "After deleting leaf 1, leaves: " << t.countLeaves() << endl;

    // Test 7: Delete all nodes one by one
    t.makeEmpty();
    cout << "After makeEmpty, leaves: " << t.countLeaves() << " (expected 0)" << endl;
    assert(t.countLeaves() == 0);

    // Test 8: Skewed tree (all right children)
    BinarySearchTree<int> skewed;
    for (int i = 1; i <= 1000; i++) skewed.insert(i);
    cout << "Skewed tree (1000 nodes) leaves: " << skewed.countLeaves() << " (expected 1)" << endl;
    assert(skewed.countLeaves() == 1);

    cout << "\nAll tests passed!" << endl;
    return 0;
}
