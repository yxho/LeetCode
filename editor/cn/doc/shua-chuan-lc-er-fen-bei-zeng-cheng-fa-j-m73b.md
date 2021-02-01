
# 二分 + 倍增乘法解法

由于题目限定了我们不能使用乘法、除法和 mod 运算符。

我们可以先实现一个「倍增乘法」，然后利用对于 `x` 除以 `y`，结果 `x / y` 必然落在范围 `[0, x]` 的规律进行二分：

```java
class Solution {
    public int divide(int a, int b) {
        long x = a, y = b;
        boolean isNeg = false;
        if ((x > 0 && y < 0) || (x < 0 && y > 0)) isNeg = true;
        if (x < 0) x = -x;
        if (y < 0) y = -y;
        long l = 0, r = x;
        while (l < r) {
            long mid = l + r + 1 >> 1;
            if (mul(mid, y) <= x) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        long ans = isNeg ? -l : l;
        if (ans > Integer.MAX_VALUE || ans < Integer.MIN_VALUE) return Integer.MAX_VALUE;
        return (int)ans;
    }
    long mul(long a, long k) {
        long ans = 0;
        while (k > 0) {
            if ((k & 1) == 1) ans += a;
            k >>= 1;
            a += a;
        }
        return ans;
    }
}
```
* 时间复杂度：对 `x` 采用的是二分策略。复杂度为 *O({log n})*

* 空间复杂度：*O(1)*

***

# 总结

这道题的解法，主要涉及的模板有两个。

一个是「二分」模板，一个是「快速乘法」模板。都是高频使用的模板。

其中「二分」模板其实有两套，主要是根据 `check(mid)` 函数为 `true` 时，需要调整的是 `l` 指针还是 `r` 指针来判断。

* 当 `check(mid) == true` 调整的是 `l` 时：计算 `mid` 的方式应该为 `mid = l + r + 1 >> 1`：

```java
long l = 0, r = 1000009;
while (l < r) {
    long mid = l + r + 1 >> 1;
    if (check(mid)) {
        l = mid;
    } else {
        r = mid - 1;
    }
}
```

* 当 `check(mid) == true` 调整的是 `r` 时：计算 `mid` 的方式应该为 `mid = l + r >> 1`：

```java
long l = 0, r = 1000009;
while (l < r) {
    long mid = l + r >> 1;
    if (check(mid)) {
        r = mid;
    } else {
        l = mid + 1;
    }
}
```

另外一个是「快速乘法」模板，采用了倍增的思想：
```java
long mul(long a, long k) {
    long ans = 0;
    while (k > 0) {
        if ((k & 1) == 1) ans += a;
        k >>= 1;
        a += a;
    }
    return ans;
}
```

***

# 最后
这是 [「宫水三叶的刷题日记」](https://mp.weixin.qq.com/s/XERBC6sKvjCLAwV1G06yfg) 的 LeetCode 系列文章的第 `No.29` 篇，系列开始于 2021/01/01，截止于起始日 LeetCode 上共有 1916 道题目，部分是有锁题，我们将先将所有不带锁的题目刷完。进度为 `29/1916`

在这个系列文章里面，除了讲解解题思路以外，还会尽可能给出最为简洁的代码。如果涉及通解还会相应的代码模板。

关注 [「宫水三叶的刷题日记」](https://mp.weixin.qq.com/s/XERBC6sKvjCLAwV1G06yfg) ，和三叶一起刷穿 LeetCode ~