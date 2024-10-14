# 堆

## 二叉堆

```cpp
{{ #include main.cpp:default }}
```

## 对顶堆

[SPOJ-RMID2](https://www.spoj.com/problems/RMID2/) [Luogu-SP16254](https://www.luogu.com.cn/problem/SP16254)

多组数据，不断读入整数，读入到 $-1$ 时输出并删除当前序列中位数（$-1$ 不插入），偶数个数时输出较小的中位数，遇到 $0$ 结束。

数据范围 $10^5$。

```cpp
{{ #include kth_heap.cpp:default }}
```
