
我的**思考顺序**是：自顶向下->**记忆化搜索**  再到 自底向上->**动态规划**

把递归搞清楚了，动态规划的状态转移方程自然而然就能想到了

话不多说，东西都在代码里


首先是【**记忆化搜索**】
```cpp
// 记忆化DFS
class Solution {
public:
    vector<int> memo;
    int numDecodings(string s) {
        if (s[0] == '0') return 0;

        memo.resize(s.size()+1, -1);

        return dfs(s, 0);
    }

    // 返回从 起点cur 到 终点s.size() 能有多少条路可以走
    int dfs(string &s, int cur){

        // 到达终点，返回1
        if (cur >= s.size()){
            return 1;
        }

        // 当前为0，无法继续，返回0
        if (s[cur] == '0') return 0;

        // 边界情况处理
        if (cur+1 == s.size()){
            return dfs(s, cur+1); 
        }

        // 记忆检查
        if (memo[cur] != -1){
            return memo[cur];
        }

        // 继续DFS
        int one = dfs(s, cur+1); 
        int two = 0;

        if (s.substr(cur, 2) <= "26") {
            two = dfs(s, cur+2);
        }

        // 记忆
        memo[cur] = one + two;
        return one + two;
    }
};
```

然后是【**动态规划**】
```cpp
// DP o(n) 可以使用滚动数组代替DP数组->o(1)空间
class Solution {
public:
    int numDecodings(string s) {
        // 处理掉前缀0，以及保证数组长度>=2
        if (s[0]  ==  '0') return 0;
        if (s.size() == 1) return 1;

        // 到这里，说明数组长度>=2
        int len = s.size();
        vector<int> DP(len+1, 0);

        // 终点从后向前遍历
        // 初始化，终点为1（注意这里终点是s[len]，DP[len]）
        DP[ len ] = 1;

        // 初始化后2个边界元素，便于之后书写，此时已经用到状态转移方程，但重点不是这里，是下方遍历
        DP[len-1] = (canOverOne(s, len-1) ? DP[len] : 0);
        DP[len-2] = (canOverTwo(s, len-2) ? DP[len] : 0) + (canOverOne(s, len-2) ? DP[len-1] : 0);

        for (int i = len-3; i >= 0; --i){
            
            // 状态转移方程
            int case_two = (canOverTwo(s, i) ? DP[i+2] : 0);
            int case_one = (canOverOne(s, i) ? DP[i+1] : 0);
            DP[i] = case_one + case_two;

        }
        return DP[0];
    }

    // 判断[cur]与[cur+1]组成的2个字符串 能否满足解码条件，从而能够继续向后到达cur+2的位置
    bool canOverTwo(string &s, int cur){
        // 像这样的：'04' '00' '09' 0开头的肯定不能解码
        //          '27' '28' '49' 大于26的肯定也不能解码
        
        string str = s.substr(cur, 2);

        if (str[0] == '0') return false;

        return str <= "26";
    }

    // 判断[cur]字符 能否满足解码条件，从而能够继续向后到达cur+1的位置
    bool canOverOne(string &s, int cur){
        // 像这样的：'0' 直接排除，比较简单
        return s[cur] != '0';
    }
};
```
