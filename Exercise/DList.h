#pragma once
#include <utility>
#include <cstddef> // std::size_t
#include <stdexcept>

template <typename T>
class DList {
    private:
        // 节点结构体
        struct Node {
            T data;
            Node* next;
            Node* prev;

            Node(const T& init_data = T{ }, Node* init_n = nullptr, Node* init_p = nullptr)
            :data{init_data}
            ,next{init_n}
            ,prev{init_p} {}

            // 提供移动语义传入data，必要时轻量化构造
            Node(T&& init_data, Node* init_n = nullptr, Node* init_p = nullptr)
            :data{std::move(init_data)}
            ,next{init_n}
            ,prev{init_p} {}
        };

        std::size_t theSize;
        Node* head;
        Node* tail;

        //初始化函数
        void init() {
            theSize = 0;
            head = new Node;
            tail = new Node;
            head->next = tail;
            tail->prev = head;
        }

        // 擦除给定节点后的一个节点
        bool erase_after(Node* node) {
            if(node != nullptr && node->next != nullptr && node->next != tail) {
                Node* to_delete = node->next;
                node->next = to_delete->next;
                to_delete->next->prev = node;
                delete to_delete; // 释放指针指向的地址的内存
                --theSize;
                return true;
            } else {
                return false;
            }
        }

        // 在某节点前插入元素
        // 按const左值引用传递（拷贝版本）
        void insert_before(Node* node, const T& x) {
            Node* node_to_insert = new Node(x, node, node->prev);
            node->prev = node->prev->next = node_to_insert;
            ++theSize;
        }
        // 按右值引用传递（移动版本）
        void insert_before(Node* node, T&& x) {
            Node* node_to_insert = new Node(std::move(x), node, node->prev);
            node->prev = node->prev->next = node_to_insert;
            ++theSize;
        }

        // 在某节点后插入元素
        // 拷贝版本
        void insert_after(Node* node, const T& x) {
            Node* node_to_insert = new Node(x, node->next, node);
            node->next = node->next->prev = node_to_insert;
            ++theSize;
        }
        // 移动版本
        void insert_after(Node* node, T&& x) {
            Node* node_to_insert = new Node(std::move(x), node->next, node);
            node->next = node->next->prev = node_to_insert;
            ++theSize;
        }
    
    public:
        // 构造函数
        DList() {
            init();
        }

        // 在尾部推入元素
        // 拷贝版本
        void push_back(const T& x) {
            insert_before(tail, x);
        }
        // 移动版本
        void push_back(T&& x) {
            insert_before(tail, std::move(x));
        }

        // 在头部推入元素
        //拷贝版本
        void push_front(const T& x) {
            insert_after(head, x);
        }
        // 移动版本
        void push_front(T&& x) {
            insert_after(head, std::move(x));
        }

        // 析构函数
        ~DList() {
            while(erase_after(head)) {}; // 这里在释放中间的数据节点内存
            delete head;
            delete tail;
        }

        // 拷贝构造函数
        DList(const DList& other) {
            init();
            Node* copied_node = other.head->next;
            for(std::size_t i = 0; i < other.theSize; ++i) {
                push_back(copied_node->data);
                copied_node = copied_node->next;
            }
        }

        // 拷贝赋值函数
        DList& operator=(const DList& other) {
            if(this == &other) {return *this;}

            DList<T> copy_temp = DList(other);
            std::swap(copy_temp, *this); // 可能调用移动赋值？若不定义移动赋值，退化为拷贝赋值导致死循环。

            return *this;
        }

        // 移动构造函数
        DList(DList&& other) noexcept 
        :theSize{other.theSize}
        ,head{other.head}
        ,tail{other.tail} {
            other.theSize = 0;
            other.head = other.tail = nullptr;
        }

        // 移动赋值函数
        DList& operator=(DList&& other) noexcept {
            if(this == &other) {return *this;}

            while (erase_after(head)) {}
            delete head;
            delete tail;

            theSize = other.theSize;
            head = other.head;
            tail = other.tail;
            other.theSize = 0;
            other.head = other.tail = nullptr;

            return *this;
        }

        // 交换当前节点与下一个节点
        void swap_neighbor(size_t i) {
            if(i + 1 >= theSize) {
                throw std::out_of_range("交换索引越界");
            }

            Node* a = head->next;
            if(i < theSize / 2) {
                for(size_t j = 0; j < i; ++j) {
                    a = a->next;
                }
            } else {
                a = tail->prev;
                for(size_t j = theSize - 1; j > i; --j) {
                    a = a->prev;
                }
            }

            Node* b = a->next; // 现在需要交换a 和 b（由于题目不允许直接交换data，这里对指针操作）

            Node* a_prev = a->prev;
            Node* b_next = b->next;

            a_prev->next = b;
            b->next = a;
            a->next = b_next;

            b_next->prev = a;
            a->prev = b;
            b->prev = a_prev;
        }

        // 打印列表
        void print() const {
            Node* p = head->next;
            while(p != tail) {
                std::cout << p->data << std::endl;
                p = p->next;
            }
            std::cout << "\n";
        }
};