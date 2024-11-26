# Python 相关

## 输入/输出

对于大规模输入量，`input()` 可能过于缓慢。使用 `sys.stdin` 提高效率：

```python
import sys
input = sys.stdin.read
data = input().split()
```

大规模输出，使用 `sys.stdout`：

```python
import sys
sys.stdout.write('\n'.join(map(str, results)) + '\n')
```

## 内置数据结构、方法

### **1. 基础数据结构**

#### **`list`（动态数组）**

- 支持动态扩展、插入、删除、切片操作。
- 常用方法：`append`、`extend`、`insert`、`remove`、`pop`、`index`、`count`、`sort`、`reverse`

```python
arr = [1, 2, 3]
arr.append(4)       # [1, 2, 3, 4]
arr.pop()           # [1, 2, 3]
arr[1:3]            # [2, 3]
```

#### **`tuple`（不可变数组）**

- 不可变，支持哈希操作，可作为字典键。
- 常用操作：解包、索引、切片。

```python
tpl = (1, 2, 3)
x, y, z = tpl      # 解包
```

#### **`str`（字符串）**

- 不可变，支持切片操作。
- 常用方法：`split`、`join`、`replace`、`strip`、`find`、`startswith`、`endswith`

```python
s = "hello world"
words = s.split()        # ['hello', 'world']
new_s = s.replace(" ", "-")  # 'hello-world'
```

#### **`set`（集合）**

- 无序、元素唯一。
- 常用方法：`add`、`remove`、`discard`、`union`、`intersection`、`difference`

```python
s = {1, 2, 3}
s.add(4)                # {1, 2, 3, 4}
s.remove(2)             # {1, 3, 4}
```

#### **`dict`（哈希表/字典）**

- 键值对存储，支持快速查找。
- 常用方法：`keys`、`values`、`items`、`get`、`pop`、`update`

```python
d = {"a": 1, "b": 2}
d["c"] = 3
val = d.get("a", 0)    # 返回 1，如果键不存在返回默认值 0
```

### **2. `collections` 模块中的数据结构**

`collections` 模块扩展了 Python 的内置数据结构，提供了更多的功能。

#### **`deque`（双端队列）**

- 双端操作高效，适合队列、栈操作。
- 常用方法：`append`、`appendleft`、`pop`、`popleft`、`rotate`、`extend`

```python
from collections import deque
dq = deque([1, 2, 3])
dq.appendleft(0)       # [0, 1, 2, 3]
dq.pop()               # [0, 1, 2]
```

#### **`Counter`（计数器）**

- 统计元素频率。
- 常用方法：`most_common`、`elements`、`subtract`

```python
from collections import Counter
cnt = Counter("aabbcc")
print(cnt)             # {'a': 2, 'b': 2, 'c': 2}
print(cnt.most_common(1))  # [('a', 2)]
```

#### **`defaultdict`（带默认值的字典）**

- 为未定义的键提供默认值。
- 常用初始化方法：`int`、`list`、`set`

```python
from collections import defaultdict
d = defaultdict(list)
d["a"].append(1)
print(d)  # {'a': [1]}
```

#### **`OrderedDict`（有序字典）**

- 记录插入顺序（Python 3.7+ 中 `dict` 也支持）。

```python
from collections import OrderedDict
od = OrderedDict()
od["a"] = 1
od["b"] = 2
print(od)  # {'a': 1, 'b': 2}
```

#### **`namedtuple`（命名元组）**

- 类似类的不可变数据结构，字段可以通过名称访问。

```python
from collections import namedtuple
Point = namedtuple("Point", ["x", "y"])
p = Point(1, 2)
print(p.x, p.y)  # 1, 2
```

### **3. `heapq` 模块中的堆**

#### **`heapq`（最小堆）**

- 实现优先队列。
- 常用方法：`heappush`、`heappop`、`heapify`、`nlargest`、`nsmallest`

```python
import heapq
heap = []
heapq.heappush(heap, 3)
heapq.heappush(heap, 1)
heapq.heappop(heap)  # 返回 1
```

### **4. `itertools` 模块中的迭代器**

#### **常用迭代器**

- **`product`**：笛卡尔积。
- **`permutations`**：排列。
- **`combinations`**：组合。
- **`combinations_with_replacement`**：可重复组合。
- **`accumulate`**：累积求和。

```python
from itertools import product, permutations, combinations, accumulate
print(list(product([1, 2], repeat=2)))  # [(1, 1), (1, 2), (2, 1), (2, 2)]
print(list(accumulate([1, 2, 3])))     # [1, 3, 6]
```

### **5. `array` 模块中的数组**

- 提供更高效的数值存储。

```python
from array import array
arr = array('i', [1, 2, 3])  # 'i' 表示整数类型
arr.append(4)
```

### **6. `queue` 模块中的队列**

- 提供线程安全的队列实现。

#### **`Queue`（FIFO 队列）**

```python
from queue import Queue
q = Queue()
q.put(1)
print(q.get())  # 1
```

#### **`LifoQueue`（栈）**

```python
from queue import LifoQueue
stack = LifoQueue()
stack.put(1)
stack.put(2)
print(stack.get())  # 2
```

#### **`PriorityQueue`（优先队列）**

```python
from queue import PriorityQueue
pq = PriorityQueue()
pq.put((1, "low"))
pq.put((0, "high"))
print(pq.get())  # (0, 'high')
```

### 二分查找

```python
from bisect import bisect_left, bisect_right
arr = [1, 2, 4, 4, 5]
pos = bisect_left(arr, 4)   # 第一个 4 的索引：2
pos2 = bisect_right(arr, 4)  # 第一个大于 4 的索引：4
```

## 高精度浮点数

使用内置 `decimal` 库：

```python
from decimal import Decimal, getcontext

# 初始化
a = Decimal('1.1')   # 推荐用字符串，避免二进制误差
b = Decimal('2.2')
```

支持基本的加减乘除、整除、取模、比较等。

设置精度：

```python
getcontext().prec = 10  # 设置精度为 10 位
```

舍入：

```python
result = a.quantize(Decimal('0.01'))     # 保留两位小数
result = a.quantize(Decimal('1E-3'))    # 保留三位小数
```

数学运算：

```python
result = a.sqrt()    # 平方根
result = a.exp()     # e^a
result = a.ln()      # ln(a)
result = a.copy_abs()   # 绝对值
result = a.copy_negate()  # 取相反数
```

## 分数

使用内置 `fractions` 库：

```python
from fractions import Fraction

# 创建分数
f1 = Fraction(3, 4)          # 分子 3，分母 4，即 3/4
f2 = Fraction('0.75')        # 支持字符串初始化
f3 = Fraction(1.5)           # 浮点数也可初始化
```

支持基本的加减乘除、整除、取模、比较等。

分子分母：

```python
f = Fraction(5, 8)
numerator = f.numerator   # 分子：5
denominator = f.denominator  # 分母：8
f = Fraction(22, 7).limit_denominator(100)  # 限制分母不超过 100
```
