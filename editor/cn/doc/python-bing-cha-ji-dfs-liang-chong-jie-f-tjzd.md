### 前言
Facebook 高频题，依旧是最近频繁出现的跟连通性相关的。

如果用并查集，本题多了一个关于人名的哈希。

用DFS可以省去哈希，所以最后效率会高一些。

---
### 方法一： 并查集
##### Python 版本
1. 直接暴力地把 `(姓名，邮箱)` 当作并查集字典中的 `key`，再额外维护一个字典，以每个集合的根节点作为 `key`，存储每个集合中所有的 `(姓名，邮箱)`。
2. 每次合并集合的时候除了更新根节点外，还要更新根节点对应的 `(姓名，邮箱)`
3. 最后添加答案的时候别忘了对这个人的所有邮箱排序。

##### C++ 版本
1. 总体思路和 `Python` 一致，说一下哈希表中 `key` 的细节
2. `C++` 的哈希表没有给 `pair` 提供哈希函数，可以自己写一个也可以转换一下思路：再额外维护一个 `邮箱 -> 姓名` 的哈希表，这样并查集中字典的 `key` 就可以省去姓名。`Python` 也可以用这个思路。
3. 也可以用一个特殊字符连接姓名和邮箱，比如 `%s+%s`。
##### 代码

```python []
class UnionFind:
    def __init__(self):
        self.father = {}
        # 根节点所在集合的所有账户
        self.accounts = {}
        
    def find(self,x):
        if not self.father[x]: return x
        
        # 递归的路径压缩处理
        self.father[x] = self.find(self.father[x])
        
        return self.father[x]
    
    def merge(self,x,y):
        root_x,root_y = self.find(x),self.find(y)
        
        if root_x == root_y:
            return
        
        # 按秩合并，更新根节点和所属的账户
        if len(self.accounts[root_x]) > len(self.accounts[root_y]):
            self.father[root_y] = root_x
            self.accounts[root_x] += self.accounts[root_y]
            del self.accounts[root_y]
        else:
            self.father[root_x] = root_y
            self.accounts[root_y] += self.accounts[root_x]
            del self.accounts[root_x]
    
    def add(self,x):
        if x not in self.father:
            self.father[x] = None
            self.accounts[x] = [x]

class Solution:
    def accountsMerge(self, accounts: List[List[str]]) -> List[List[str]]:
        uf = UnionFind()
        for account in accounts:
            # 找到姓名和主账户
            name,master = account[0],account[1]
            uf.add((name,master))
            
            # 和其余的账户一一合并
            account = list(set(account[2:]))
            for i in range(len(account)):
                uf.add((name,account[i]))
                uf.merge((name,master),(name,account[i]))
        
        res = []
        for key,value in uf.father.items():
            # 是根节点
            if not value:
                # 添加user
                usr_account = [uf.accounts[key][0][0]]
                # 添加账户
                for account in uf.accounts[key]:
                    usr_account.append(account[1])
                    
                res.append(sorted(usr_account))
                
        return res
```
```c++ []
class UnionFind{
private:
    unordered_map<string,string> father;
    // 根节点所在集合的所有账户
    unordered_map<string,vector<string>> accounts;

public:
    unordered_map<string,string> get_father(){
        return father;
    }
    
    unordered_map<string,vector<string>> get_accounts(){
        return accounts;
    }
    
    string find(string s){
        if(father[s] == "root") return s;
        
        // 递归的路径压缩处理
        father[s] = find(father[s]);
        
        return father[s];
    }
    
    void merge(string x,string y){
        string root_x = find(x);
        string root_y = find(y);
        
        if(root_x == root_y) return;
        
        // 按秩合并，更新根节点和所属的账户
        if(accounts[root_x].size() < accounts[root_y].size()){
            father[root_x] = root_y;
            for(auto& account: accounts[root_x])
                accounts[root_y].push_back(account);
            accounts.erase(root_x);
        }else{
            father[root_y] = root_x;
            for(auto& account: accounts[root_y])
                accounts[root_x].push_back(account);
            accounts.erase(root_y);
        }
        
    }
    
    void add(string x){
        if(!father.count(x)){
            father[x] = "root";
            accounts[x] = {x};
        }
    }
    
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        UnionFind uf;
        // email -> name
        unordered_map<string,string> email_to_name;
        
        for(auto& v: accounts){
            // 找到姓名和主账户
            string name = v[0];
            string master = v[1];
            email_to_name[master] = name;
            uf.add(master);
            
            // 和其余的账户一一合并
            for(int i = 2;i < v.size();i++){
                email_to_name[v[i]] = name;
                uf.add(v[i]);
                uf.merge(master,v[i]);
            }
        }
        
        vector<vector<string>> res;
        unordered_map<string,string> father = uf.get_father();
        unordered_map<string,vector<string>> acc = uf.get_accounts();
        
        for(auto& p: father){
            // 是根节点
            if(p.second == "root"){
                // 添加user
                vector<string> user_account = {email_to_name[p.first]};
                
                // 添加账户
                sort(acc[p.first].begin(),acc[p.first].end());
                for(auto& email: acc[p.first])
                    user_account.push_back(email);
                
                res.push_back(user_account);
            }
        }
        
        return res;

    }
};
```




--- 

### 方法二： 深度优先搜索
1. 建图，我们可以忽略姓名，直接把关联的账户连接起来即可
2. 对每一个 `account` 子数组的第一个邮箱进行深度优先搜索，`子数组的姓名+得到的账户组（也要再排个序）` 就是这个人对应的答案

##### 代码
```python []
class Solution:
    def build_graph(self,accounts):
        """
        建图
        """
        graph = collections.defaultdict(list)
        for account in accounts:
            master = account[1]
            # 对剩余账户做一个去重
            for email in list(set(account[2:])):
                graph[master].append(email)
                graph[email].append(master)
        
        return graph
    
    def dfs(self,email,graph,visited,emails):
        """
        深搜遍历
        """
        # 已经访问过的就剪枝
        if email in visited:
            return 
        
        visited.add(email)
        emails.append(email)
        
        # 对邻居节点继续深搜
        for neighbor in graph[email]:
            self.dfs(neighbor,graph,visited,emails)
    
    def accountsMerge(self, accounts: List[List[str]]) -> List[List[str]]:
        graph = self.build_graph(accounts)

        res = []
        visited = set()
        for account in accounts:
            emails = []
            self.dfs(account[1],graph,visited,emails)
            if emails:
                res.append([account[0]] + sorted(emails))
        
        return res
```
```c++ []
class Solution {
public:
    unordered_map<string,vector<string>> build_graph(vector<vector<string>>& accounts){
        /* 建图 */
        unordered_map<string,vector<string>> graph;
        
        for(auto& account: accounts){
            
            string master = account[1];
            
            // 对剩余账户做一个去重
            for(auto& email: unordered_set<string>(account.begin()+2,account.end())){
                
                graph[master].push_back(email);
                graph[email].push_back(master);
            }
        }
        
        return graph;
    }
    
    void dfs(unordered_map<string,vector<string>>& graph,unordered_set<string>& visited,string& email,vector<string>& emails){
        /* 深搜遍历 */
        // 已经访问过的就剪枝
        if(visited.count(email))
            return;
        
        visited.insert(email);
        emails.push_back(email);
        
        // 对邻居节点继续深搜
        for(auto& neighbor: graph[email])
            dfs(graph,visited,neighbor,emails);
    }
    
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        // 建图
        unordered_map<string,vector<string>> graph = build_graph(accounts);
        
        vector<vector<string>> res;
        
        unordered_set<string> visited;
        
        for(auto& account: accounts){
            vector<string> emails;
            // 深搜得到name的所有邮箱
            dfs(graph,visited,account[1],emails);
            
            if(emails.empty())
                continue;
            
            // 排序，添加姓名，加入到答案中
            sort(emails.begin(),emails.end());
            emails.insert(emails.begin(),account[0]);
            res.push_back(emails);
        }
        
        return res;
    }
};
```



