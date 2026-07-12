# 第二课思考题

> 递归 Fibonacci 分析：[L1 习题](../Chap2_AlgorithmAnalysis/L1_taste.md) | 算法分析笔记：[Ch.2 笔记](../note/ch02-algorithm-analysis.md#l2-最大子序列和--对数时间243245)

## 3(a). 当使用Euclid算法计算gcd(M, N)时，其中M，N为Fibonacci数列相邻的两项，试求迭代步数。

由于Euclid算法即辗转相除法，并且Fibonacci由其构造很容易知道为严格递增列，为了方便，记$M=f_n$，$N=f_{n-1}$，其中$n\geq 1$，${f_n}(n\geq 0)$为Fibonacci数列。算法的每一步都对应了Fibonacci数列构造中的一次迭代。因此对于Fibonacci数列中的$M,N$，需要迭代$n-1$次。

对于Euclid算法，Fibonacci是最坏情况是因为：Euclid算法的速度跟每次辗转相除法除数前的倍数正相关，而Fibonacci数列保证了每次除数为1，这是最小的情况，从而是最坏的情况。（$Lam\'{e}$定理）

## 3(b). 分析Weiss教材中p70页提到的三种return pow错误的后果。

该题是关于快速幂的算法：

```cpp
bool isEven( int n )
{
    return n % 2 == 0;
}

long long pow( long long x, int n )
{
    if( n == 0 )
        return 1;
    if( n == 1 )
        return x;
    if( isEven( n ) )
        return pow( x * x, n / 2 );
    else
        return pow( x * x, n / 2 ) * x;
}
```

有三种错误：

### 8a

```cpp
if(isEven(n))
    return pow(pow(x, 2), n / 2);
```
这种错误会导致当迭代到$n=2$时，会陷入死循环，最终溢出。

### 8b

```cpp
if(isEven(n))
    return pow(pow(x, n / 2), 2);
```
问题同8a。

### 8c

```cpp
if(isEven(n))
    return pow(x, n / 2) * pow(x, n / 2);
```
分支之后调用了分支数次函数，完全没有优化算法时间复杂度。
