# 状压 DP

枚举子集的子集，时间复杂度 $3^n$：

```cpp
for (int i = 0; i < (1 << n); ++i) {
  for (int j = i; j; j = (j - 1) & i) {
    // j 为 i 的子集
  }
}
```
