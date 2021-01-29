### 解题思路
![chrome_4LRHnLpC1g.png](https://pic.leetcode-cn.com/1602295453-YiwOAz-chrome_4LRHnLpC1g.png)
动态规划
1、新建dp数组，dp[m+1][n+1]初始化为0;
2、遍历两个字符串，填充dp数组；
3、如果字符相同，`text1[i-1]==text2[j-1]`，则表示公共子序列长度可以+1，即`dp[i][j]=dp[i-1][j-1]+1`；
4、如果不相同，在两个字符串分别减1的长度去找最长公共子序列`dp[i][j]=max(dp[i-1][j],dp[i][j-1])`；
5、最后dp数组最大的值，也就是`dp[m][n]`为最长公共子序列的长度。
### 复杂度
1、时间：O(mn),m、n分别为字符串长度；
2、空间：O(mn), 即dp数组大小。
### 代码

```cpp
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m=text1.size(),n=text2.size();
        
        int dp[m+1][n+1];
        memset(dp,0,sizeof(dp));

        for (int i=1;i<=m;i++) {
            for (int j=1;j<=n;j++) {
                if (text1[i-1]==text2[j-1]) {
                    dp[i][j]=dp[i-1][j-1]+1;
                } else {
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        return dp[m][n];
    }
};
```