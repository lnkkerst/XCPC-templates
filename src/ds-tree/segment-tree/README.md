# 线段树

## 区间加，区间求和

[Luogu-P3372](https://www.luogu.com.cn/problem/P3372)

```cpp
{{ #include simple_add_sum.cpp:default }}
```

## 区间加，区间最大（小）值

```cpp
{{ #include add_max.cpp:default }}
```

## 区间加，区间乘，区间求和

[Luogu-P3373](https://www.luogu.com.cn/problem/P3373)

```cpp
{{ #include add_mul_sum.cpp:default }}
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
{{ #include add_sum_dyno.cpp:default }}
```

## 线段树合并

TODO 完善代码

常用于权值线段树，动态开点

```cpp
int merge(int u, int v, int l, int r) {
  if(!u) {
    return v;
  }
  if(!v) {
    return u;
  }
  if(u == v) {
    sum[u] += sum[v];
    return a;
  }
  int mid = ((r - l) >> 1) + l;
  ls[u] = merge(ls[u], ls[v], l, mid);
  rs[u] = merge(rs[u], rs[v], mid + 1, r);
  pushup(u);
  return u;
}
```

## 线段树分裂

TODO 完善代码

只能用于有序的序列，常用于动态开点的权值线段树

```cpp
void split(int &u, int &v, int l, int r, int L, int R) {
  if(l < L || r > R) {
    return;
  }
  if(!u) {
    return;
  }
  if(l >= L && r <= R) {
    v = u;
    u = 0;
    return;
  }
  if(!q) {
    q = newNode();
  }
  int mid = ((r - l) >> 1) + l;
  if(L <= mid) {
    split(ls[u], ls[v], l, mid, L, R);
  }
  if(R > mid) {
    split(rs[u], rs[v], mid + 1, r, L, R);
  }
  pushup(u);
  pushup(v);
}
```
