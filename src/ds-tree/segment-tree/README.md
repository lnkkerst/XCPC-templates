# 线段树

## 区间加，区间求和

[Luogu-P3372](https://www.luogu.com.cn/problem/P3372)

```cpp
{{ #include simple_add_sum.cpp:18:109 }}
```

## 区间加，区间乘，区间求和

[Luogu-P3373](https://www.luogu.com.cn/problem/P3373)

```cpp
{{ #include add_mul_sum.cpp:18:158 }}
```

## 区间加，区间求和，动态开点

常用于权值线段树。

[Luogu-P3369](https://www.luogu.com.cn/problem/P3369)

普通平衡树

1. 插入 $x$ 数
2. 删除 $x$ 数(若有多个相同的数，应只删除一个)
3. 查询 $x$ 数的排名(排名定义为比当前数小的数的个数 $+1$ )
4. 查询排名为 $x$ 的数
5. 求 $x$ 的前驱(前驱定义为小于 $x$，且最大的数)
6. 求 $x$ 的后继(后继定义为大于 $x$，且最小的数)

```cpp
{{ #include add_sum_dyno.cpp:18:146 }}
```
