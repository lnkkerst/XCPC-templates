# 虚树

[Luogu-P2495 \[SDOI2011\] 消耗战](https://www.luogu.com.cn/problem/P2495)

给一个有边权的有根树，每次询问给一堆点，求割掉一些边使得根节点无法到达。

点数量级 $1e5$，询问点之和数量级 $1e5$。

对每次询问的点建虚树，跑个 dp。核心是建树。

这份代码常数极大。

```cpp
{{ #include luogu-p2495.cpp:default }}
```
