# 对拍

假设待验证代码为 `1.cpp`，暴力程序为 `bl.cpp`，数据生成器为 `dm.py`。

## bash

无限循环：

```sh
while true; do
  python dm.py >in
  ./1 <in >out1
  ./bl <in >outbl
  if ! diff outbl out1; then
    break
  fi
done
```

限制次数（ChatGPT 生成的）：

```sh
#!/bin/bash
num_tests=100  # 设定测试次数
for ((i=1; i<=num_tests; i++)); do
    ./generator > input.txt
    ./brute < input.txt > brute_output.txt
    ./optimized < input.txt > optimized_output.txt

    if ! diff brute_output.txt optimized_output.txt > /dev/null; then
        echo "Mismatch found on test $i"
        echo "Input:"
        cat input.txt
        echo "Brute output:"
        cat brute_output.txt
        echo "Optimized output:"
        cat optimized_output.txt
        exit 1
    fi
    echo "Test $i passed!"
done
echo "All tests passed!"
```

## fish

```fish
while true
    python dm.py >in
    cat in | ./1 >out1
    cat in | ./bl >outbl
    diff out1 outbl
    if test $status -ne 0
        break
    end
end
```

## cmd

```cmd
@echo off
:loop
  python dm.py > in
  1.exe < in > out1
  bl.exe < in > outbl
  fc out1 outbl
if not errorlevel 1 goto loop
```

## powershell

ChatGPT 写的，没经过测试。

```powershell
while ($true) {
  # 生成测试数据
  ./generator.exe > input.txt

  # 运行暴力算法
  ./brute.exe < input.txt > brute_output.txt

  # 运行优化算法
  ./optimized.exe < input.txt > optimized_output.txt

  # 比较输出
  if (!(Compare-Object (Get-Content brute_output.txt) `
                      (Get-Content optimized_output.txt))) {
    Write-Output "Test passed!"
  } else {
    Write-Output "Mismatch found!"
    Write-Output "Input:"
    Get-Content input.txt
    Write-Output "Brute output:"
    Get-Content brute_output.txt
    Write-Output "Optimized output:"
    Get-Content optimized_output.txt
    break
  }
}
```
