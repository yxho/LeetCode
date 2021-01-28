//给定一个二维的矩阵，包含 'X' 和 'O'（字母 O）。 
//
// 找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。 
//
// 示例: 
//
// X X X X
//X O O X
//X X O X
//X O X X
// 
//
// 运行你的函数后，矩阵变为： 
//
// X X X X
//X X X X
//X X X X
//X O X X
// 
//
// 解释: 
//
// 被围绕的区间不会存在于边界上，换句话说，任何边界上的 'O' 都不会被填充为 'X'。 任何不在边界上，或不与边界上的 'O' 相连的 'O' 最终都会被
//填充为 'X'。如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。 
// Related Topics 深度优先搜索 广度优先搜索 并查集 
// 👍 461 👎 0

#include "include/headers.h"

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class UnionFind {
    vector<int> fathers;
public:
    UnionFind(int nums) {
        for (int i = 0; i < nums; i++) {
            fathers.push_back(i);
        }
    }

    void merge(int a, int b) {
        int roota = find(a);
        int rootb = find(b);
        if (roota != rootb) {
            fathers[rootb] = roota;
        }
    }

    int find(int node) {
        return fathers[node] == node ? node : find(fathers[node]);
    }

    bool isConnected(int a, int b) {
        return find(a) == find(b);
    }
};


class Solution {
public:
    void solve(vector<vector<char>> &board) {
        if (board.size() == 0)
            return;
        int rows = board.size();
        int cols = board[0].size();
        UnionFind *uf = new UnionFind(rows * cols + 1);
        int flag = rows * cols;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] == 'O') {
                    if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                        uf->merge(i * cols + j, flag);
                    } else {
                        if (i > 0 && board[i - 1][j] == 'O')
                            uf->merge(i * cols + j, (i - 1) * cols + j);
                        if (i < rows - 1 && board[i + 1][j] == 'O')
                            uf->merge(i * cols + j, (i + 1) * cols + j);
                        if (j > 0 && board[i][j - 1] == 'O')
                            uf->merge(i * cols + j, i * cols + j - 1);
                        if (j < cols - 1 && board[i][j + 1] == 'O')
                            uf->merge(i * cols + j, i * cols + j + 1);
                    }
                }
            }
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (uf->isConnected(i * cols + j, flag)) {
                    // 和dummyNode 在一个连通区域的,那么就是O；
                    board[i][j] = 'O';
                } else {
                    board[i][j] = 'X';
                }
            }
        }


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