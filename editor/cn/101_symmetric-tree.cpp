//给定一个二叉树，检查它是否是镜像对称的。 
//
// 
//
// 例如，二叉树 [1,2,2,3,4,4,3] 是对称的。 
//
//     1
//   / \
//  2   2
// / \ / \
//3  4 4  3
// 
//
// 
//
// 但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的: 
//
//     1
//   / \
//  2   2
//   \   \
//   3    3
// 
//
// 
//
// 进阶： 
//
// 你可以运用递归和迭代两种方法解决这个问题吗？ 
// Related Topics 树 深度优先搜索 广度优先搜索 
// 👍 1210 👎 0

#include "include/headers.h"

using namespace std;
//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    // dfs
    bool compare(TreeNode *left, TreeNode *right) {
        if (left == nullptr && right == nullptr) {
            return true;
        } else if (left == nullptr || right == nullptr) {
            return false;
        } else if (right->val != left->val) {
            return false;
        } else {
            return compare(left->left, right->right) && compare(left->right, right->left);
        }
    }

    bool isSymmetric(TreeNode *root) {
        if (root == nullptr)
            return true;
        return compare(root->left, root->right);
    }

//// bfs
//    bool isSymmetric(TreeNode *root) {
//        if (root == nullptr)
//            return true;
//        queue<TreeNode *> q;
//        q.push(root->left);
//        q.push(root->right);
//        while (!q.empty()) {
//            auto l = q.front();
//            q.pop();
//            auto r = q.front();
//            q.pop();
//            if (l == nullptr && r == nullptr)
//                continue;
//            if (l == nullptr || r == nullptr || (l->val != r->val))
//                return false;
//            q.push(l->left);
//            q.push(r->right);
//            q.push(l->right);
//            q.push(r->left);
//        }
//        return true;
//    }

};
//leetcode submit region end(Prohibit modification and deletion)

int main() {
    Solution s;
    vector<int> data{7, 1, 5, 3, 6, 4};
    //vector<int> ans = s.twoSum(data,11);
    //cout << ans[0]<<ans[1]<<endl;
    cout << "Hello LeetCode" << endl;
}