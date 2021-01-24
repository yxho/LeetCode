### 思路
1. 使用并查集将邮箱地址相同的账户的索引合并起来
2. 使用 `unordered_map<int, pair<string, set<string>>>` 将数据整理过来
    1. 其中第一个 `int` 代表原数据中索引
    2. `pair` 的 `first` 代表账户名称
    3. `pair` 的 `second` 使用 `set` 去掉重复邮箱地址并排序
3. 最后转成输出格式


### 并查集
```C++ []
struct DSU {
    DSU(int n) : data(n, -1) {}

    bool unionSet(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) return false;
        if (data[x] > data[y]) {
            swap(x, y);
        }
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }

    int root(int x) {
        return data[x] < 0 ? x : data[x] = root(data[x]);
    }

    int size(int x) {
        return -data[root(x)];
    }

    vector<int> data;
}; 
```

### 答题
```C++ []
class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        DSU dsu(accounts.size());
        unordered_map<string, int> mp;
        for (int i = 0; i < accounts.size(); i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                const auto& email = accounts[i][j];
                if (mp.find(email) != mp.end()) {
                    dsu.unionSet(mp[email], i);
                }
                mp[email] = i;
            }
        }

        unordered_map<int, pair<string, set<string>>> temp;
        for (int i = 0; i < accounts.size(); i++) {
            int x = dsu.root(i);
            if (temp.find(x) == temp.end()) {
                temp[x].first = accounts[i][0];
            }
            for (int j = 1; j < accounts[i].size(); j++) {
                temp[x].second.insert(accounts[i][j]);
            }
        }

        vector<vector<string>> ans;
        for (auto& [k, p] : temp) {
            ans.push_back({ p.first });
            copy(p.second.begin(), p.second.end(), back_inserter(ans.back()));
        }
        return ans;
    }
};
```



### 致谢
感谢您的观看，希望对您有帮助，欢迎热烈的交流！  

**如果感觉还不错就点个赞吧~**

在 [我的力扣个人主页](https://leetcode-cn.com/u/ikaruga/) 中有我使用的做题助手项目链接，帮助我收集整理题目，可以方便的 `visual studio` 调试，欢迎关注，star

