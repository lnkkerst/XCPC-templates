# 并查集

## 简单版本

```cpp
{{ #include simple.cpp:default }}
```

## 启发式合并

```cpp
{{ #include union_by_rank.cpp:default }}
```

## 删除与移动

删除：将父亲设为自己，为了保证删除的元素都是叶节点，设置副本并初始化父亲为副本。
移动：保重移动的元素都在叶子节点。

实现以下功能：

1. 合并两个元素所处集合。
2. 移动 $p$ 到 $q$ 集合。
3. 查询元素所在集合大小和元素和。

```cpp
{{ #include remove_and_move.cpp:default }}
```

<!-- TODO 带权并查集 -->
