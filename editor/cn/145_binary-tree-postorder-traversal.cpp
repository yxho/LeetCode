//给定一个二叉树，返回它的 后序 遍历。 
//
// 示例: 
//
// 输入: [1,null,2,3]  
//   1
//    \
//     2
//    /
//   3 
//
//输出: [3,2,1] 
//
// 进阶: 递归算法很简单，你可以通过迭代算法完成吗？ 
// Related Topics 栈 树 
// 👍 507 👎 0

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
    vector<int> postorderTraversal(TreeNode *root) {
        /*方法一*/
//        vector<int> vec;
//        visit(root, vec);
//        return vec;
        vector<int> res;
        stack<TreeNode *> st;

        if (root != nullptr)
            st.push(root);
        while (!st.empty()) {
            auto cur = st.top();
            if (cur != nullptr) {
//                st.pop();
//                st.push(cur);
                st.push(nullptr);
                if (cur->right != nullptr)st.push(cur->right);
                if (cur->left != nullptr)st.push(cur->left);
            }else{
                st.pop();
                res.push_back(st.top()->val);
                st.pop();
            }
        }
        return res;

    }

    void visit(TreeNode *root, vector<int> &vec) {
        if (root == nullptr)
            return;
        visit(root->left, vec);
        visit(root->right, vec);
        vec.push_back(root->val);
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