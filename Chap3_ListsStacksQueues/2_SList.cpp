#include <algorithm>
#include <iostream>
#include <utility>

class SList {
    private:
        struct Node {
            int data;
            Node *next;

            Node(const int& d = int{}, Node *n = nullptr)
            : data{d}
            , next{n}
            {}

            Node(int&& d, Node *n = nullptr)
            : data{std::move(d)}
            , next{n}
            {}
        };

        int theSize;
        Node *head;
        
        void init() {
            theSize = 0;
            head = new Node; //分配到堆上可以有稳定的生命周期，不至于在移动构造时丢失，同时也便于在析构时同数据节点统一释放内存
            head->next = nullptr;
        }
    
    public:
        SList() {
            init();
        }

        ~SList() {
            while(erase_after(head)) {}
            delete head;
        }

        void insert_after(Node* node, int x) {
            node->next = new Node{x, node->next};
            ++theSize;
        }

        void push_front(int x) {
            insert_after(head, x);
        }

        bool erase_after(Node* node) {
            if(node != nullptr && node->next != nullptr) {
                Node* toDelete = node->next;
                node->next = toDelete->next;
                delete toDelete;
                --theSize;
                return true;
            }
            return false;
        }

        void pop_front() {
            erase_after(head);
        }

        Node* begin() const {
            return head->next;
        }

        Node* end() const {
            return nullptr;
        }

        void print() const {
            Node* p = head->next;
            while(p != nullptr) {
                std::cout << p->data << std::endl;
                p = p->next;
            }
        }
};
// 哨兵节点在插入和删除数字时让头尾跟内部等价起来，可以共用一套指令。

// 测试用
int main() {
    SList lst;

    // 1. 空链表 print
    std::cout << "=== 空链表 ===" << std::endl;
    lst.print();

    // 2. push_front
    std::cout << "=== push_front 30, 20, 10 ===" << std::endl;
    lst.push_front(10);
    lst.push_front(20);
    lst.push_front(30);
    lst.print();

    // 3. pop_front
    std::cout << "=== pop_front ===" << std::endl;
    lst.pop_front();
    lst.print();

    // 4. pop_front 清空
    std::cout << "=== pop_front x2 ===" << std::endl;
    lst.pop_front();
    lst.pop_front();
    lst.print();

    // 5. 空链表 pop_front（不应崩溃）
    std::cout << "=== 空链表 pop_front ===" << std::endl;
    lst.pop_front();
    lst.print();

    // 6. insert_after
    std::cout << "=== insert_after 测试 ===" << std::endl;
    lst.push_front(50);
    lst.push_front(10);
    lst.insert_after(lst.begin(), 25);  // 在 10 后插入 25
    lst.print();

    std::cout << "=== 析构测试通过 ===" << std::endl;
    return 0;
}