# 树状数组

## 单点加，区间和。

需要运算满足结合律且可差分，如加法（和）、乘法（积）、异或等。

- 结合律： $(x \circ y) \circ z = x \circ (y \circ z)$ ，其中 $\circ$ 是一个二元运算符。
- 可差分：具有逆运算的运算，即已知 $x \circ y$ 和 $x$ 可以求出 $y$ 。

```cpp
{{ #include simple.cpp:16:59 }}
```

## 区间加，单点查询。

维护差分数组即可。

```cpp
{{ #include diff.cpp:16:63 }}
```

## 区间加，区间和。

```cpp
{{ #include range_add_query.cpp:16:80 }}
```

## 二维，子矩阵加，单点查询

改一改就是单点修改，子矩阵查询了。

[POJ-2155](http://poj.org/problem?id=2155)

没有经过严格测试。

```cpp
{{ #include mat_simple.cpp:16:77 }}
```

## 二维，子矩阵加，子矩阵查询

[POJ-2155](http://poj.org/problem?id=2155)

没有经过严格测试。

```cpp
{{ #include mat_range.cpp:16:85 }}
```
