# 树状数组

## 单点加，区间和。

需要运算满足结合律且可差分，如加法（和）、乘法（积）、异或等。

- 结合律： $(x \circ y) \circ z = x \circ (y \circ z)$ ，其中 $\circ$ 是一个二元运算符。
- 可差分：具有逆运算的运算，即已知 $x \circ y$ 和 $x$ 可以求出 $y$ 。

```cpp
{{ #include simple.cpp:default }}
```

## 区间加，单点查询。

维护差分数组即可。

## 区间加，区间和。

```cpp
{{ #include range_add_query.cpp:default }}
```

## 二维，子矩阵加，单点查询

改一改就是单点修改，子矩阵查询了。

[LOJ-133](https://loj.ac/p/133)

```cpp
{{ #include mat_simple.cpp:default }}
```

## 二维，子矩阵加，子矩阵查询

[LOJ-135](https://loj.ac/p/135)

```cpp
{{ #include mat_range.cpp:default }}
```

## 权值树状数组

TODO 完善代码

维护 $b_x$ 为 $x$ 在 $a$ 中出现的次数，对 $b$ 建树状数组。

单点修改，求 kth：

```cpp
// 权值树状数组查询第 k 小
int kth(int k) {
  int sum = 0, x = 0;
  for (int i = log2(n); ~i; --i) {
    x += 1 << i;                   // 尝试扩展
    if (x >= n || sum + t[x] >= k) // 如果扩展失败
      x -= 1 << i;
    else
      sum += t[x];
  }
  return x + 1;
}
```
