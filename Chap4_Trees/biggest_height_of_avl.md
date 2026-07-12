# 关于如何计算 AVL 树的最大高度

书中提到 AVL 树对应 h 最小元素 $S(h)$ 由推导式
$$
S(h)=S(h-1)+S(h-2)+1,\,S(0)=1,\,S(1)=2
$$
确定。回顾[第二章中对计算 Fibonacci 数列的递归方法](../Chap2_AlgorithmAnalysis/L1_taste.md)，可以发现推导式一样。详见 [Ch.4 AVL 笔记](../note/ch04-trees.md#l2-avl-树44-pp144158)。，用同样的方法，设令 $T(h+3)=S(h)+1$ ，此时
$$
T(h)=T(h-1)+T(h-2),\,T(3)=2,\,T(4)=3
$$
那么 
$$
T(h)=\frac{\phi^h-\psi^h}{\sqrt{5}}
$$
其中 $\phi=(1+\sqrt{5})/2,\,\psi=(1-\sqrt{5})/2$ ，则
$$
S(h)=\frac{\phi^{h+3}-\psi^{h+3}}{\sqrt{5}}-1
$$
考虑 $h$ 较大时的情况，则 
$$
S(h)\approx \frac{\phi^{h+3}}{\sqrt{5}}-1
$$
由于 $S(h)$ 指的是“该高度对应最少节点数”，则节点数 $N_h$ 满足
$$
N_h\geq S(h) \approx \frac{\phi^{h+3}}{\sqrt{5}}-1
$$
于是
$$
N_h\gtrsim \frac{\phi^{h+3}}{\sqrt{5}}-1，\\
\log_{\phi}\sqrt{5}(N_h+1)-3\gtrsim h,\\
h\lesssim \log^{-1}\phi\left[\log(N_h+1)+\log\sqrt{5}\right]-3,\\
h\lesssim 1.440\log(N+1)-1.328.
$$
进一步地有
$$
h\leq 1.440\log(N+1)-1.328.
$$
