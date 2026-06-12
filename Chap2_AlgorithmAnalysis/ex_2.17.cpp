#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>
using std::swap;
using std::max;
using std::min;
using std::cout;
using std::vector;
using std::set;

// a. Find the minimum subsequence sum.
int minSubSum(const vector<int>& v) {
    int minSum = 0, thisSum = 0;

    for(size_t i = 0; i < v.size(); i++) {
        thisSum += v[i];
        if(thisSum > 0)
            thisSum = 0;
        else if(minSum > thisSum) {
            minSum = thisSum;
        }
    }
    return minSum;
} // 时间复杂度O(N)，注：该算法允许去空子列且空子列和视为0.

// b. Find the minimum positive subsequence sum.
int minPoSubSum(const vector<int>& v) {
    vector<int> prefix = {0};
    for(size_t i = 0; i < v.size(); i++) {
        prefix.push_back(v[i] + prefix[i]);
    }

    int thisSum = 0, minSum = INT_MAX;

    for(size_t i = 0; i < prefix.size(); i++) {
        for(size_t j = 0; j < i; j++) {
            if(prefix[j] < prefix[i]) {
                thisSum = prefix[i] - prefix[j];
                if(minSum > thisSum)
                    minSum = thisSum;
            }
        }
    }
    return minSum == INT_MAX ? 0 : minSum;
} // 时间复杂度O(N^2)，空间复杂度O(1)。

// Optimized
int minPoSubSum_Op(const vector<int>& v) {
    // 构建前缀和数组，prefix[0] = 0, prefix[i] = sum(v[0..i-1])
    vector<long long> prefix(v.size() + 1, 0);
    for (size_t i = 0; i < v.size(); ++i) {
        prefix[i+1] = prefix[i] + v[i];
    }

    set<long long> seen;
    seen.insert(0);                 // 前缀和0（空子序列）
    long long minSum = LLONG_MAX;   // 初始化为最大长整型

    for (size_t i = 1; i < prefix.size(); ++i) {
        long long cur = prefix[i];

        // 找到严格小于 cur 的最大前缀和
        auto it = seen.lower_bound(cur);
        if (it != seen.begin()) {
            --it;                     // 前驱元素
            long long diff = cur - *it;
            if (diff > 0 && diff < minSum) {
                minSum = diff;
            }
        }

        seen.insert(cur);
    }

    return (minSum == LLONG_MAX) ? 0 : static_cast<int>(minSum);
}

// c. Find the maximum subsequence product
int maxSubPro(const vector<int>& v) {
    int ans = 1, curMax = 1, curMin = 1;

    for(int x : v) {
        if (x < 0)
            swap(curMax, curMin);
        curMax = max(curMax * x, x);
        curMin = min(curMin * x, x);
        ans = max(ans,curMax);
    }
    return ans;
} // 时间复杂度O(N)，空间复杂度O(1).此处约定空子列乘积为1.

int main() {
    vector<int> a = {1, -2 ,10, -9, 2};
    cout << minSubSum(a) << "\n";
    cout << minPoSubSum(a) << "\n";
    cout << minPoSubSum_Op(a) << "\n";
    cout << maxSubPro(a) << "\n";
    return 0;
}