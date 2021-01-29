//
// 
// 有 n 个城市，其中一些彼此相连，另一些没有相连。如果城市 a 与城市 b 直接相连，且城市 b 与城市 c 直接相连，那么城市 a 与城市 c 间接相连
//。 
//
// 省份 是一组直接或间接相连的城市，组内不含其他没有相连的城市。 
//
// 给你一个 n x n 的矩阵 isConnected ，其中 isConnected[i][j] = 1 表示第 i 个城市和第 j 个城市直接相连，而 
//isConnected[i][j] = 0 表示二者不直接相连。 
//
// 返回矩阵中 省份 的数量。 
//
// 
//
// 示例 1： 
//
// 
//输入：isConnected = [[1,1,0],[1,1,0],[0,0,1]]
//输出：2
// 
//
// 示例 2： 
//
// 
//输入：isConnected = [[1,0,0],[0,1,0],[0,0,1]]
//输出：3
// 
//
// 
//
// 提示： 
//
// 
// 1 <= n <= 200 
// n == isConnected.length 
// n == isConnected[i].length 
// isConnected[i][j] 为 1 或 0 
// isConnected[i][i] == 1 
// isConnected[i][j] == isConnected[j][i] 
// 
// 
// 
// Related Topics 深度优先搜索 并查集 
// 👍 482 👎 0

#include "include/headers.h"

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class UnionFind {
public:
    UnionFind(int nums) {
        for (int i = 0; i < nums; i++) {
            fathers.push_back(i);
        }
    }

    void merge(int a, int b) {
        int aFather = find(a);
        int bFather = find(b);
        if (aFather != bFather) {
            fathers[bFather] = aFather;
        }
    }

    int find(int a) {
        return fathers[a] == a ? a : find(fathers[a]);
    }

    bool isConnet(int a, int b) {
        return find(a) == find(b);
    }

private:
    vector<int> fathers;
};

class Solution {
public:
    int findCircleNum(vector<vector<int>> &isConnected) {
        int nums = isConnected.size();
        UnionFind *uf = new UnionFind(nums);

        for (int i = 0; i < nums; i++) {
            for (int j = i + 1; j < nums; j++) {
                if (isConnected[i][j] == 1) {
                    uf->merge(i, j);
                }
            }
        }
        set<int> st;
        for (int i = 0; i < nums; i++) {
            st.insert(uf->find(i));
        }
        return st.size();
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