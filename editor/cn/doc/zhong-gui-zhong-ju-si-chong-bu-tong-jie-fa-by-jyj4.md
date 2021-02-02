### 解题思路
如果逐项乘当然最简单，但是很容易超时。这时自然想到二分加速。二分也有两种实现：递归或迭代，个人感觉递归的容易些。每次把指数减半，返回的结果相乘，如果指数是奇数就在额外乘以一个x。迭代的技巧较强，需要明白数的二进制表示，同时维护每个bit表示的数权重，power=x^y。y每次加倍。

### 代码

```cpp
// Cheat
class Solution1 {
public:
    double myPow(double x, int n) {
        return pow(x, n);
    }
};

class Solution2 {
public:
    double myPow(double x, int n) {
        bool isNegative = n < 0;
        long N = abs(n);
        double res = 1.0;
        for (int i = 0; i < N; i++) {
            res *= x;
        }

        return isNegative ? 1.0 / res : res;
    }
};

class Solution3 {
public:
    double myPow(double x, int n) {
        bool isNegative = n < 0;
        long N = abs(n);
        double res = helper(x, N);
        return isNegative ? 1.0 / res : res;
    }

private:
    double helper(double x, long N) {
        if (N == 0) {
            return 1.0;
        }

        auto half = helper(x, N / 2);
        if (N % 2 == 0) {
            return half * half;
        } else {
            return half * half * x; 
        }
    }
};

class Solution {
public:
    double myPow(double x, int n) {
        bool isNegative = n < 0;
        long N = abs(n);
        double res = quickPow(x, N);
        return isNegative ? 1.0 / res : res;
    }

private:
    double quickPow(double x, long N) {
        if (N == 0) {
            return 1.0;
        }

        double power = x;
        double res = 1.0;
        while (N > 0) {
            if (N % 2 == 1) { // only count bits that are 1s in binary representation
                res *= power;
            }
            power *= power; // from x^(logx(power)) to x^(logx(power) * 2)
            N /= 2;
        }

        return res;
    }
};
```