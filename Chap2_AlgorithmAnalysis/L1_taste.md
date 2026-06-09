# **Chap 2. 算法分析第一节习题**

## **1. 给出算法的Big-Oh时间复杂度**

### [**(a)**](#que-a)

```cpp
for (int i = 0; i < n; ++i)
  for (int j = 0; j < n; ++j)
      a[i][j] = 0;
```

该算法的时间复杂度为$O(N^2)$。因为内部语句复杂度为$O(1)$，循环次数为$N^2$次。

### **（b）**

```cpp
for (int i = 0; i < n; ++i)
    for (int j = 0; j < i; ++j)
      ++count;
```

该算法时间复杂度为$O(N^2)$。分析同[a](#que-a)。

### **(c)**

```cpp
for (int i = 0; i < n; ++i)
  for (int j = 0; j < n; ++j)
      for (int k = 0; k < n; ++k)
          if (i == j && j == k)
              cout << i;
```

该算法时间复杂度为$O(N^3)$。因为虽然循环中的语句只有当i = j = k时才会执行，但最内层循环中的条件判定每次都会执行，因此时间复杂度需要计算。

### **(d)**

```cpp
for (int i = 1; i <= n; i *= 2)
    cout << i;
```

该算法复杂度为$O(log_2 N)$，这是由i的指数递增决定的，循环次数$k$满足$n\approx 2^k$，从而$k\approx log_2 N$。

## 2. 上界、下界和紧确界

一个算法在处理大小为 N 的输入时，运行时间为 3N² + 100N + 500 微秒。则我们说该算法是$O(N^2)$的、是$\Omega(N^2)$、同时还是$\Theta(N^2)$的。这是因为运行时间已经很明确地是一个N的初等函数了，所以很容易找到等价无穷大量，从而这三个东西存在且相等。

## 3. 递归Fibonacci数列函数(Recursion)

第40项本身调用一次，函数体中会调用39、38项的函数而每个被调用的函数会调用两个函数，知道最后调用到递归起点第1、2项。

设第$n$项需要调用函数$f_n$次，则：

\[
f_n=f_{n-1}+f_{n-2}+1
\]
可化为类似Fibonacci数列的递推式：
\[
f_n+1=(f_{n-1}+1)+(f_{n-2}+1)
\]
对于

```cpp
long fib(int n)
{
    if(n <= 1)
        return 1;
    else
        return fib(n - 1) + fib(n - 2);
}
```

$f_0=f_1=1$，从而：

\[
(f_n+1)+\frac{\sqrt{5}-1}{2}(f_{n-1}+1)=2(\frac{\sqrt{5}+1}{2})^n
\]

\[
f_{n+1}=\frac{\sqrt{5}-3}{2^{n-1}}\sum_{k=0}^{n-1}\left[(\sqrt{5}+1)^k(1-\sqrt{5})^{n-1-k}\right]+2(\frac{\sqrt{5}+1}{2})^n-1.
\]

代入即可算得$f_{40}$，时间复杂度$O((\frac{\sqrt{5}+1}{2})^N)$。

用迭代时：

```cpp
int Fib(int n) {
    int pre = 0;
    int now = 1;
    for(int i = 0; i < n - 1; i++){
        int temp = now;
        now += pre;
        pre = temp;
    }
    return now;
}
```

仅需39次循环，时间复杂度$O(N)$。
