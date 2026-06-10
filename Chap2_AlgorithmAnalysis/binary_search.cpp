#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
using std::vector;

// 二分法查找，被查找向量已排序（由小到大）
//递归
template <typename Comparable>
int sub_binarySearch(const vector<Comparable>& a, const Comparable& x, int left, int right) {
    if (right < left)
        return -1;

    int mid = left + (right - left) / 2;
    if (x == a[mid])
        return mid;
    else if (x < a[mid])
        return sub_binarySearch(a, x, left, mid - 1);
    else
        return sub_binarySearch(a, x, mid + 1, right);
}//对于总量为N的数据，递归深度最坏为O(log N)，每递归一次要进行储存，从而是O(log N).

//封装接口
template <typename Comparable>
int binarySearch(const vector<Comparable>& a, const Comparable& x) {
    return sub_binarySearch(a, x, 0, static_cast<int>(a.size()) - 1);
}

//迭代
template <typename Comparable>
int binarySearch_1(const vector<Comparable>& a, const Comparable& x) {
    int left = 0, right = a.size() - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if (x == a[mid])
            return mid;
        else if (x < a[mid])
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}//对于任意数据，只用一次，储存对应的left等东西，空间复杂度O(1).

template <typename Comparable>
int Search(const vector<Comparable>& a, const Comparable& x) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] == x)
            return static_cast<int>(i);
    }
    return -1;
}

int main() {
    int top = 10000;

    for (int x = 0; x < 2; x++) {

        vector<int> arr(1000000);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, top); // 范围可调
        std::generate(arr.begin(), arr.end(), [&](){ return dist(gen); });
        std::sort(arr.begin(), arr.end());

        int to_find = 3422;

        auto start = std::chrono::high_resolution_clock::now();
        int id = binarySearch(arr, to_find);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout <<"递归二分：要找的数在索引" << id << "，用时" << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us。\n";

        start = std::chrono::high_resolution_clock::now();
        id = binarySearch_1(arr, to_find);
        end = std::chrono::high_resolution_clock::now();
        std::cout <<"迭代二分：要找的数在索引" << id << "，用时" << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us。\n";
        
        start = std::chrono::high_resolution_clock::now();
        id = Search(arr, to_find);
        end = std::chrono::high_resolution_clock::now();
        std::cout << "单纯搜索：要找的数在索引" << id << "，用时" << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us。\n"; 
    
        top = 1000000000;
    }
        return 0;
}