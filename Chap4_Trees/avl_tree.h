// 该AVL树实现了插入、删除

#ifndef AVL_TREE
#define AVL_TREE

#include <utility>
#include <algorithm>
#include <iostream>

template <typename Comparable>
class AVLTree {
    private:
        // 数据节点
        struct AVLNode {
            Comparable data;
            AVLNode* left;
            AVLNode* right;
            int height;

            AVLNode(const Comparable& init_d, AVLNode* init_l = nullptr, AVLNode* init_r = nullptr, int init_h = 0)
            :data{init_d}
            ,left{init_l}
            ,right{init_r}
            ,height{init_h} {}
        };

        // 返回节点高度
        int GetHeight(AVLNode* node) const {
            return node == nullptr ? -1 : node->height;
        }

        // 找元素
        bool Contain(const Comparable& x, AVLNode* node) const {
            if(!node) {
                return false;
            } else if(x < node->data) {
                return Contain(x, node->left);
            } else if(x > node->data) {
                return Contain(x, node->right);
            } else {
                return true;
            }
        }

        // 打印
        void PrintInOrder(AVLNode* node) const {
            if(node) {
                PrintInOrder(node->left);
                std::cout << node->data << "\n";
                PrintInOrder(node->right);
            }
        }

        // 插入元素 x
        void Insert(const Comparable& x, AVLNode*& node) {
            if(node == nullptr) {
                node = new AVLNode(x);
            } else if(x < node->data) {
                Insert(x, node->left);
            } else if(x > node->data) {
                Insert(x, node->right);
            }

            Balance(node);
        }

        // 删除元素
        void Delete(const Comparable& x, AVLNode*& node) {
            if(node == nullptr) {
                return; // 未找到元素
            }

            if(x < node->data) {
                Delete(x, node->left);
            } else if(x > node->data) {
                Delete(x, node->right);
            } else if(node->left && node->right) {
                node->data = FindMin(node->right)->data;
                Delete(node->data, node->right);
            } else {
                AVLNode* temp = node;
                node = node->left ? node->left : node->right;
                delete temp;
            }
            Balance(node);
        }

        // 找最小
        AVLNode* FindMin(AVLNode* node) const {
            if(node) {
                while(node->left){
                    node = node->left;
                }
            }
            return node;
        }

        // 平衡操作
        void Balance(AVLNode*& node) {
            if(node == nullptr){
                return;
            }

            if(GetHeight(node->left) - GetHeight(node->right) > 1) {
                if(GetHeight(node->left->left) >= GetHeight(node->left->right)) {
                    RightRotation(node);
                } else {
                    LeftRightRotation(node);
                }
            } else if(GetHeight(node->right) - GetHeight(node->left) > 1) {
                if(GetHeight(node->right->right) >= GetHeight(node->right->left)) {
                    LeftRotation(node);
                } else {
                    RightLeftRotation(node);
                }
            }

            node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
        }

        /*
            右单旋转，用于解决左左失衡
                k_2
                /   \
            k_1   Z
            /   \ 
            X(big)  Y
        */
        void RightRotation(AVLNode*& k_2) {
            AVLNode* k_1 = k_2->left;
            k_2->left = k_1->right;
            k_1->right = k_2;
            k_2->height = std::max(GetHeight(k_2->left), GetHeight(k_2->right)) + 1;
            k_1->height = std::max(GetHeight(k_2), GetHeight(k_1->left)) + 1;
            k_2 = k_1; // 把 k_1 连到树上，由于 Insert 为递归实现的，这相当于改了k_2父节点->left的指向，使其指向k_1了
        }

        /*
            左单旋转，用于解决右右失衡
                k_2
                /   \
                X     k_1
                    /   \
                    Y     Z(big)
        */
        void LeftRotation(AVLNode*& k_2) {
            AVLNode* k_1 = k_2->right;
            k_2->right = k_1->left;
            k_1->left = k_2;
            k_2->height = std::max(GetHeight(k_2->left), GetHeight(k_2->right)) + 1;
            k_1->height = std::max(GetHeight(k_2), GetHeight(k_1->right)) + 1;
            k_2 = k_1; // 把 k_1 连到树上
        }

        // 左右双旋，用于解决左右失衡
        void LeftRightRotation(AVLNode*& node) {
            LeftRotation(node->left);
            RightRotation(node);
        }

        // 右左双旋，用于解决右左失衡
        void RightLeftRotation(AVLNode*& node) {
            RightRotation(node->right);
            LeftRotation(node);
        }

        // 清空树
        void Empty(AVLNode*& node) {
            if(node) {
                Empty(node->left);
                Empty(node->right);
                delete node;
            }
            node = nullptr;
        }

        // 拷贝子树
        AVLNode* Copy(AVLNode* node) const {
            if(!node) {
                return node;
            } else {
                return new AVLNode(node->data, Copy(node->left), Copy(node->right), node->height);
            }
        }

        AVLNode* root_;

    public:
        // 构造函数
        AVLTree()
        :root_{nullptr} {}

        // 析构函数
        ~AVLTree() {
            Empty(root_);
        }

        // 拷贝构造
        AVLTree(const AVLTree& other) {
            root_ = Copy(other.root_);
        }

        // 拷贝赋值
        AVLTree& operator=(const AVLTree& other) {
            if(this != &other) {
                AVLTree temp(other);
                std::swap(temp, *this);
                return *this;
            }
            return *this;
        }

        // 移动构造
        AVLTree(AVLTree&& other) noexcept 
        :root_{other.root_} {
            other.root_ = nullptr;
        }

        // 移动赋值AVLTre
        AVLTree& operator=(AVLTree&& other) {
            std::swap(root_, other.root_);
            return *this;
        }

        // 插入
        void Insert(const Comparable& x) {
            Insert(x, root_);
        }

        // 删除
        void Delete(const Comparable& x) {
            Delete(x, root_);
        }

        // 查找是否存在某元素
        bool Contain(const Comparable& x) const {
            return Contain(x, root_);
        }

        // 中序遍历打印元素
        void PrintInOrder() const {
            PrintInOrder(root_);
        }

        // 返回树的高度
        int GetHeight() {
            return GetHeight(root_);
        }
};

#endif