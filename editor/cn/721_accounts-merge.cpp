//给定一个列表 accounts，每个元素 accounts[i] 是一个字符串列表，其中第一个元素 accounts[i][0] 是 名称 (name)，其
//余元素是 emails 表示该账户的邮箱地址。 
//
// 现在，我们想合并这些账户。如果两个账户都有一些共同的邮箱地址，则两个账户必定属于同一个人。请注意，即使两个账户具有相同的名称，它们也可能属于不同的人，因为
//人们可能具有相同的名称。一个人最初可以拥有任意数量的账户，但其所有账户都具有相同的名称。 
//
// 合并账户后，按以下格式返回账户：每个账户的第一个元素是名称，其余元素是按字符 ASCII 顺序排列的邮箱地址。账户本身可以以任意顺序返回。 
//
// 
//
// 示例 1： 
//
// 
//输入：
//accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnn
//ybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Ma
//ry", "mary@mail.com"]]
//输出：
//[["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  
//["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]
//解释：
//第一个和第三个 John 是同一个人，因为他们有共同的邮箱地址 "johnsmith@mail.com"。 
//第二个 John 和 Mary 是不同的人，因为他们的邮箱地址没有被其他帐户使用。
//可以以任何顺序返回这些列表，例如答案 [['Mary'，'mary@mail.com']，['John'，'johnnybravo@mail.com']，
//['John'，'john00@mail.com'，'john_newyork@mail.com'，'johnsmith@mail.com']] 也是正确的
//。
// 
//
// 
//
// 提示： 
//
// 
// accounts的长度将在[1，1000]的范围内。 
// accounts[i]的长度将在[1，10]的范围内。 
// accounts[i][j]的长度将在[1，30]的范围内。 
// 
// Related Topics 深度优先搜索 并查集 
// 👍 220 👎 0

#include "include/headers.h"

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    unordered_map<string, vector<string>> buildGraph(vector<vector<string>> &accounts) {
        unordered_map<string, vector<string>> graph;
        for (auto &account:accounts) {
            string master = account[1];
            for (auto &email : unordered_set<string>(account.begin() + 2, account.end())) {
                graph[master].push_back(email);
                graph[email].push_back(master);
            }
        }
        return graph;
    }

    void dfs(unordered_map<string, vector<string>> &graph, unordered_set<string> &visited, string email,
             vector<string> &emails) {
        if (visited.count(email)) // 图，如果一个email曾经查过那么与他关联的所有Email都查过，没有必要再查；这个enmail所关联的用户已经查过了，跳过就行了
            return;
        visited.insert(email);
        emails.push_back(email);
        for (auto &email:graph[email])
            dfs(graph, visited, email, emails);
    }

    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts) {
        auto graph = buildGraph(accounts);
        vector<vector<string>> res;
        unordered_set<string> visited;
        for (auto &account:accounts) {
            vector<string> vec;
            dfs(graph, visited, account[1], vec);
            if (vec.empty())
                continue;
            sort(vec.begin(), vec.end());
            vec.insert(vec.begin(), account[0]);
            res.push_back(vec);
        }
        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

int main() {
    Solution s;
    vector<int> data{7, 1, 5, 3, 6, 4};
    //vector<int> ans = s.twoSum(data,11);
    //cout << ans[0]<<ans[1]<<endl;
    cout << "Hello LeetCode" << endl;
}