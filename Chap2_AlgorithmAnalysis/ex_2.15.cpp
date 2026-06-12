#include <iostream>
#include <vector>
using std::cout;
using std::vector;
const int kNoFound = -1;

//找已排序数组中是否有元素等于下标（1开始）。
int FindIndexEqualsValue(const vector<int>& v) {
    int low = 0, high = v.size() - 1;
    
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(v[mid] == mid + 1)
            return mid + 1;
        else if(v[mid] < mid + 1) 
            low = mid + 1;
        else 
            high = mid - 1;
    }
    return kNoFound;
}// 时间复杂度O(log N)

int main() {
    vector<int> v = {-99, 0, 2, 4, 7, 9};
    cout << FindIndexEqualsValue(v) << '\n';
    return 0;
}