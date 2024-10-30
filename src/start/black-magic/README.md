# 黑魔法

## 创建多维 `vector`

**需要 C++14 及以上**

不可初始化值的版本：

```cpp
{{ #include xd_vector.cpp:default }}
```

带初始化值的版本，初始化值必须为第一个参数：

```cpp
{{ #include xd_vector_init.cpp:default }}
```

## “动态”的 `std::bitset`

**需要 C++14 及以上**

来自
[CF1856E2](https://codeforces.com/contest/1856/problem/E2)，
利用模板展开预定义大小为 $2^k$ 的函数。

```cpp
{{ #include fake_dynamic_bitset.cpp:default }}
```
