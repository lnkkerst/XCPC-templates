# 背包 DP

如无特殊说明，默认 `v` 为价值（value），`w` 为重量（weight）。

## 01 背包

[Luogu-P2871](https://www.luogu.com.cn/problem/P2871)

```cpp
{{ #include 01.cpp:19:35 }}
```

## 完全背包

[Luogu-P1616](https://www.luogu.com.cn/problem/P1616)

```cpp
{{ #include complete.cpp:19:35 }}
```

## 多重背包

[AcWing-5](https://www.acwing.com/problem/content/5/)

```cpp
{{ #include multiple.cpp:20:46 }}
```

## 混合背包

[Luogu-P1833](https://www.luogu.com.cn/problem/P1833) 按类型分别套用上面三种背包的代码即可。

```cpp
{{ #include mix.cpp:19:75 }}
```

## 二维费用背包

[Luogu-P1855](https://www.luogu.com.cn/problem/P1855)

```cpp
{{ #include 2d.cpp:19:37 }}
```

## 分组背包

[Luogu-P1757](https://www.luogu.com.cn/problem/P1757)

> 有 $n$ 件物品和一个大小为 $m$ 的背包，第 $i$ 个物品的价值为 $w_i$，
> 体积为 $v_i$。同时，每个物品属于一个组，同组内最多只能选择一个物品。
> 求背包能装载物品的最大总价值。

```cpp
{{ #include group.cpp:19:41 }}
```

可以转化成分组背包：有依赖的背包，把物品依赖的选择方案分到同一组。

## 背包问题变种

### 输出方案

用 $g_{i,v}$ 表示第 $i$ 件物品占用空间为 $v$
的时候是否被选择，转移时记录选或不选，输出：

```cpp
int cur_w = m;
vector<int> selected;

for (int i = n; i >= 1; --i) {
  if (g[i][cur_w]) {
    selected.emplace_back(i);
    cur_w -= w[i];
  }
}
```

### 求方案数量

把转移中求最大值变为求和。

01 背包：$dp_i = \sum{dp_i, dp_{i-w_i}}, dp_0 = 1$

### 求最优方案数量

TODO 重写并测试

```cpp
for (int i = 0; i < N; i++) {
  for (int j = V; j >= v[i]; j--) {
    int tmp = std::max(dp[j], dp[j - v[i]] + w[i]);
    int c = 0;
    if (tmp == dp[j]) {
      c += cnt[j]; // 如果从dp[j]转移
    }
    if (tmp == dp[j - v[i]] + w[i]) {
      c += cnt[j - v[i]]; // 如果从dp[j-v[i]]转移
    }
    dp[j] = tmp;
    cnt[j] = c;
  }
}
int max = 0; // 寻找最优解
for (int i = 0; i <= V; i++) {
  max = std::max(max, dp[i]);
}
int res = 0;
for (int i = 0; i <= V; i++) {
  if (dp[i] == max) {
    res += cnt[i]; // 求和最优解方案数
  }
}
```

### 求第 k 优解

TODO 重写并测试

```cpp
memset(dp, 0, sizeof(dp));
int i, j, p, x, y, z;
scanf("%d%d%d", &n, &m, &K);
for (i = 0; i < n; i++) {
  scanf("%d", &w[i]);
}
for (i = 0; i < n; i++) {
  scanf("%d", &c[i]);
}
for (i = 0; i < n; i++) {
  for (j = m; j >= c[i]; j--) {
    for (p = 1; p <= K; p++) {
      a[p] = dp[j - c[i]][p] + w[i];
      b[p] = dp[j][p];
    }
    a[p] = b[p] = -1;
    x = y = z = 1;
    while (z <= K && (a[x] != -1 || b[y] != -1)) {
      if (a[x] > b[y]) {
        dp[j][z] = a[x++];
      } else {
        dp[j][z] = b[y++];
      }
      if (dp[j][z] != dp[j][z - 1]) {
        z++;
      }
    }
  }
}
printf("%d\n", dp[m][K]);
```
