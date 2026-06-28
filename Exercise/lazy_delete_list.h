#include <cstddef>
#include <utility>
#include <stdexcept>

template <typename T>
class LazyDeleteList {
    private:
        //节点状态结构体
        struct Node {
            T data;
            Node* prev;
            Node* next;
            bool in_list; // 记录该节点是否“在列表中”

            Node(const T& init_data = T{}, Node* init_prev = nullptr, Node* init_next = nullptr)
            :data{init_data}
            ,prev{init_prev}
            ,next{init_next} {
                in_list = true; // 默认创建时为“在列表中”
            }

            Node(T&& init_data, Node* init_prev = nullptr, Node* init_next = nullptr)
            :data{std::move(init_data)}
            ,prev{init_prev}
            ,next{init_next} {
                in_list = true;
            }
        };

        std::size_t the_size; // 现有有效列表元素个数
        std::size_t deleted_size; // 现有标记删除列表元素个数
        Node* head;
        Node* tail;

        // 初始化函数
        void init() {
            head = new Node;
            tail = new Node;
            head->next = tail;
            tail->prev = head;
            head->in_list = false;
            tail->in_list = false;
        }

        // 在某节点前插入元素
        // 按const左值引用传递（拷贝版本）
        void insert_before(Node* node, const T& x) {
            Node* node_to_insert = new Node(x, node->prev, node);
            node->prev = node->prev->next = node_to_insert;
            ++the_size;
        }
        // 按右值引用传递（移动版本）
        void insert_before(Node* node, T&& x) {
            Node* node_to_insert = new Node(std::move(x), node->prev, node);
            node->prev = node->prev->next = node_to_insert;
            ++the_size;
        }

        // 在某节点后插入元素
        // 拷贝版本
        void insert_after(Node* node, const T& x) {
            Node* node_to_insert = new Node(x, node, node->next);
            node->next = node->next->prev = node_to_insert;
            ++the_size;
        }
        // 移动版本
        void insert_after(Node* node, T&& x) {
            Node* node_to_insert = new Node(std::move(x), node, node->next);
            node->next = node->next->prev = node_to_insert;
            ++the_size;
        }

        //删除当前节点
        void delete_node(Node* node) {
            node->in_list = false;
            --the_size;
            ++deleted_size;
            if(the_size == deleted_size) {
                release();
            }
        }

        // 达到临界时物理清除已删除节点
        void release() {
            Node* curr = head->next;
            while (curr != tail) {
                Node* next_node = curr->next;
                if (!curr->in_list) {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    delete curr;
                    --deleted_size;
                }
                curr = next_node;
            }
        }

    public:
        // 在列表头推入元素
        // 拷贝版本
        void push_front(const T& x) {
            insert_after(head, x);
        }
        // 移动版本
        void push_front(T&& x) {
            insert_after(head, std::move(x));
        }

        // 在列表尾推入元素
        // 拷贝版本
        void push_back(const T& x) {
            insert_before(tail, x);
        }
        // 移动版本
        void push_back(T&& x) {
            insert_before(tail, std::move(x));
        }

        // 删除头部元素
        void pop_front() {
            if(the_size == 0) {
                throw std::logic_error("Try to pop from an empty list!");
            }
            Node* curr = head->next;
            while(!curr->in_list) {
                curr = curr->next;
            }
            if(curr == tail) {
                throw std::logic_error("Try to pop tail node!");
            }
            delete_node(curr);
        }

        // 删除尾部元素
        void pop_back() {
            if(the_size == 0) {
                throw std::logic_error("Try to pop from an empty list!");
            }
            Node* curr = tail->prev;
            while(!curr->in_list) {
                curr = curr->prev;
            }
            if(curr == head) {
                throw std::logic_error("Try to pop head node!");
            }
            delete_node(curr);
        }

        // 删除第i个（索引处）的元素
        void delete_the(size_t i) {
            // 由于deleted_size小于the_size，且无法得知被删除的元素的位置，只让遍历的未删除元素少一些
            if(i >= the_size) {
                throw std::out_of_range("Try to delete an element out of list!");
            }
            if(i < the_size / 2) {
                Node* curr = head->next;
                for(size_t j = 0; j < i; ++j) {
                    curr = curr->next;
                    while(!curr->in_list) {
                        curr = curr->next;
                    }                   
                }
                delete_node(curr);
            }else {
                Node* curr = tail->prev;
                for(size_t j = the_size - 1; j > i; --j) {
                    curr = curr->prev;
                    while(!curr->in_list) {
                        curr = curr->prev;
                    }
                }
                delete_node(curr);
            }
        }

        // 清空列表
        void clear() {
            if(head) {
                Node* curr = head->next;
                while(curr != tail) {
                    Node* next_temp = curr->next;
                    delete curr;
                    curr = next_temp;
                }
                head->next = tail;
                tail->prev = head;
                the_size = 0;
                deleted_size = 0;
            }
        }

        // 构造函数
        LazyDeleteList()
        :the_size{0}
        ,deleted_size{0} {
            init();
        }

        // 析构函数
        ~LazyDeleteList() {
            clear();
            delete head;
            head = nullptr;
            delete tail;
            tail = nullptr;
        }

        // 拷贝构造函数
        LazyDeleteList(const LazyDeleteList& other) {
            init();
            Node* curr = other.head->next;
            while(curr != other.tail) {
                push_back(curr->data);
                tail->prev->in_list = curr->in_list;
                curr = curr->next;
            }
            the_size = other.the_size;
            deleted_size = other.deleted_size;
        }

        // 移动构造函数
        LazyDeleteList(LazyDeleteList&& other)
        :the_size{other.the_size}
        ,deleted_size{other.deleted_size}
        ,head{other.head}
        ,tail{other.tail} {
            other.deleted_size = other.the_size = 0;
            other.tail = other.head = nullptr;
        }

        // 移动赋值函数
        LazyDeleteList& operator=(LazyDeleteList&& other) {
            if(this != &other) {
                clear();
                delete head;
                delete tail;
                the_size = other.the_size;
                deleted_size = other.deleted_size;
                head = other.head;
                tail = other.tail;
                other.deleted_size = other.the_size = 0;
                other.tail = other.head = nullptr;
            }
            return *this;
        }

        // 拷贝赋值函数
        LazyDeleteList& operator=(const LazyDeleteList& other) {
            if(this != &other) {
                LazyDeleteList<T> temp_list(other);
                *this = std::move(temp_list);
            }
            return *this;
        }

};