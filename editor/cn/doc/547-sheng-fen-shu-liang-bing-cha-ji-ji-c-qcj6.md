> **点击上方关注「代码随想录」，算法路上不迷路！**


今天这道题题目是一道基础的并查集。

关于并查集其实是可以讲一大堆，哈哈，但今天看每日一题有点晚了，我先把代码贴出来吧（都写上注释了）

C++代码如下：

```
class Solution {
private: 
    int father[210]; // 题目1 <= n <= 200
    int n; // 边的数量
    
    // 并查集初始化
    void init() {
        for (int i = 0; i < n; ++i) {
            father[i] = i;
        }
    }
    // 并查集里寻根的过程
    int find(int u) {
        return u == father[u] ? u : father[u] = find(father[u]);
    }
    // 将v->u 这条边加入并查集
    void join(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return ;
        father[v] = u;
    }
    // 判断 u 和 v是否找到同一个根，本题用不上
    bool same(int u, int v) {
        u = find(u);
        v = find(v);
        return u == v;
    }

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        n = isConnected.size();
        init();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isConnected[i][j]) join(i, j);
            }
        }
        // 此时已经并查集已经把边链接好了 
        unordered_set<int> uset; // 容积有多少个没有链接的省份
        for (int i = 0; i < n; i++) {   
            uset.insert(find(i));
        }
        return uset.size();
    }
};

```
「代码随想录」目前正在循序渐进讲解算法，目前已经讲到了动态规划，[点击这里](https://img-blog.csdnimg.cn/20210102121706654.png)和上万录友一起打卡学习，来看看，你一定会发现相见恨晚！

**如果感觉题解对你有帮助，不要吝啬给一个👍吧！**
