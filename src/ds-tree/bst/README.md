# 平衡树

gnu pbds 中的 tree：

[Luogu-P3369](https://www.luogu.com.cn/problem/P3369)

普通平衡树

1. 插入 $x$ 数
2. 删除 $x$ 数(若有多个相同的数，应只删除一个)
3. 查询 $x$ 数的排名(排名定义为比当前数小的数的个数 $+1$ )
4. 查询排名为 $x$ 的数
5. 求 $x$ 的前驱(前驱定义为小于 $x$，且最大的数)
6. 求 $x$ 的后继(后继定义为大于 $x$，且最小的数)

`__gnu_pbds::tree` 不支持可重复集合，需要自己手动处理。

```cpp
{{ #include gnu_pbds_tree.cpp }}
```

`std::rope` 实现区间翻转：

```cpp
{{ #include rope_range_reverse.cpp }}
```
