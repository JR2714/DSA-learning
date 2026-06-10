#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
using std::vector;
using std::cout;


// Brute-force Iteration
int maxSubSum1( const vector<int>& seq ) {
    int maxSum = 0;
    for( size_t i = 0; i < seq.size(); i++ ) {
        for( size_t j = i; j < seq.size(); j++ ) {
            int thisSum = 0;
            for( size_t k = i; k <= j; k++ ) {
                thisSum += seq[k];
                if ( thisSum > maxSum ){
                    maxSum = thisSum;
                }
            }
        }
    }
    return maxSum;
}

// Optimized Brute-froce Iteration
int maxSubSum2( const vector<int>& seq ) {
    int maxSum = 0;
    for( size_t i = 0; i < seq.size(); i++ ) {
        int thisSum = 0;
        for(size_t j = i; j < seq.size(); j++) {
            thisSum += seq[j];
            if ( thisSum > maxSum ) {
                maxSum = thisSum;
            }
        }
    }
    return maxSum;
}

// Divide and Conquer
int sub_maxSubSum3( const vector<int>& seq, int left, int right ) {
    if ( left == right ) { 
        if ( seq[left] < 0 ) 
            return 0;
        else
            return seq[left];
    }

    int mid = left + (right - left) / 2;

    int leftMaxSum = sub_maxSubSum3( seq, left, mid);
    int rightMaxSum = sub_maxSubSum3( seq, mid + 1, right);

    int leftBoundMaxSum = 0, leftBoundSum = 0;
    for(int i = mid; i >= left; i--) {
        leftBoundSum += seq[i];
        if (leftBoundSum > leftBoundMaxSum)
            leftBoundMaxSum = leftBoundSum;
    }

    int rightBoundMaxSum = 0, rightBoundSum = 0;
    for(int i = mid + 1; i <= right; i++) {
        rightBoundSum += seq[i];
        if (rightBoundSum > rightBoundMaxSum)
            rightBoundMaxSum = rightBoundSum;
    }

    return std::max({rightBoundMaxSum + leftBoundMaxSum, rightMaxSum, leftMaxSum});
}
int maxSubSum3(const vector<int>& seq) {
    return sub_maxSubSum3(seq, 0, seq.size() - 1);
}

//Linear Time Algorithm
int maxSubSum4(const vector<int>& seq) {
    int maxSum = 0, thisSum = 0;
    for(size_t i = 0; i < seq.size(); i++) {
        thisSum += seq[i];
        if (thisSum < 0)
            thisSum = 0;
        else if (thisSum > maxSum)
            maxSum = thisSum;
    }
    return maxSum;
}

std::vector<int> generateRandomArray(int size, int minVal = -1000, int maxVal = 1000) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(minVal, maxVal);
    
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = dist(gen);
    }
    return arr;
}

// 计时包装器
template<typename Func>
long long measure(Func f, const vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    f(arr);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main( )
{
    vector<int> a { -2, 11, -4, 13, -5, -2 };
    int maxSum;

    maxSum = maxSubSum1( a );
    cout << "Max sum is " <<  maxSum << std::endl;
    maxSum = maxSubSum2( a );
    cout << "Max sum is " <<  maxSum << std::endl;
    maxSum = maxSubSum3( a );
    cout << "Max sum is " <<  maxSum << std::endl;
    maxSum = maxSubSum4( a );
    cout << "Max sum is " <<  maxSum << std::endl;

    std::vector<int> sizes = {1000, 5000, 10000, 50000, 100000};
    
    for (int N : sizes) {
        std::cout << "\n===== N = " << N << " =====" << std::endl;
        auto arr = generateRandomArray(N);
        
        // 注意：由于算法效率差异大，对较大 N 可能需要跳过 O(N^3) 算法
        long long t1;
        if (N < 5000) t1 = measure(maxSubSum1, arr);
        else t1 = -1;  // skip
        long long t2 = measure(maxSubSum2, arr);
        long long t3 = measure(maxSubSum3, arr);
        long long t4 = measure(maxSubSum4, arr);
        
        std::cout << "O(N^3)      : " << t1 << " us" << std::endl;
        std::cout << "O(N^2)      : " << t2 << " us" << std::endl;
        std::cout << "O(N log N)  : " << t3 << " us" << std::endl;
        std::cout << "O(N)        : " << t4 << " us" << std::endl;

    /* 由于50000以上O(N^3)算法时间太长，这里根据一次输出的结果给出估计
    ===== N = 1000 =====
    O(N^3)      : 843136 us
    O(N^2)      : 3253 us
    O(N log N)  : 91 us
    O(N)        : 7 us

    ===== N = 5000 =====
    O(N^3)      : 98914845 us
    O(N^2)      : 78625 us
    O(N log N)  : 484 us
    O(N)        : 33 us

    ===== N = 10000 =====
    O(N^3)      : 794441386 us
    O(N^2)      : 323849 us
    O(N log N)  : 990 us
    O(N)        : 63 us

    ===== N = 50000 =====
    O(N^3) : 99100000000 us (27.5 小时)（估计）
    O(N^2) : 8100000 us (8.10 秒)
    O(N log N) : 5600 us (5.60 毫秒)
    O(N) : 315 us

    ===== N = 100000 =====
    O(N^3) : 793000000000 us (220 小时)（估计）
    O(N^2) : 32400000 us (32.4 秒)
    O(N log N) : 11900 us (11.9 毫秒)
    O(N) : 630 us
        */
    }
    return 0;
}