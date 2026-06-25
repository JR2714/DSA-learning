#pragma once
#include <algorithm>
#include <iostream>
#include <utility>
#include <stdexcept>

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

        size_t theSize;
        Node *head;
        
        void init() {
            theSize = 0;
            head = new Node; //分配到堆上可以有稳定的生命周期，不至于在移动构造时丢失，同时也便于在析构时同数据节点统一释放内存
            head->next = nullptr;
        }

        // 提供[]运算提取对应节点
        Node* operator[](size_t x) {
            if(x >= theSize) {
                throw std::overflow_error("超出列表范围！");
            }
            Node* re = begin();
            for(;x != 0; --x) {
                re = re->next;
            }
            return re;
        }

        // 交换当前节点的后两位
        void swap_after(Node* prev) {
            if(prev == nullptr || prev->next == nullptr || prev->next->next == nullptr) {
                throw std::invalid_argument("选中节点及后续两个节点不能为空");
            }
            Node* A = prev->next;
            Node* B = A->next;
            Node* C = B->next;

            prev->next = B;
            B->next = A;
            A->next = C;
        }
        // 提供交换头两个节点的函数
        void swap_first_two() {
            swap_after(head);  // head 是哨兵节点
        }
    
    public:
        SList() {
            init();
        }

        ~SList() {
            while(erase_after(head)) {}
            delete head;
        }

        // 暂且禁用拷贝和移动，以后再加入
        SList(const SList&) = delete;
        SList& operator=(const SList&) = delete;
        SList(SList&&) = delete;
        SList& operator=(SList&&) = delete;

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
                delete toDelete; // 释放toDelete指向的那个地址的内存
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
            std::cout << "\n";
        }

        // 交换i和i+1节点（用索引习惯）；这里优化了接口，保证交换操作的统一性和安全性
        void swap_neighbor(size_t i) {
            if(i == 0) {
                swap_first_two();
            }else {
            swap_after((*this)[i-1]);
            }
        }
};
// 哨兵节点在插入和删除数字时让头尾跟内部等价起来，可以共用一套指令。