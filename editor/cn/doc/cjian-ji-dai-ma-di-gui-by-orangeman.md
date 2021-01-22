### 解题思路
1.方法一：递归
2.方法二：前序遍历 根左右遍历
3.方法三：中序遍历 左根右遍历
4.方法四：后序遍历 根右左遍历，`reverse`后就成左右根了
5.方法五：层序遍历 一层一层遍历

### 代码

```递归 []
class Solution {
public:
    int rangeSumBST(TreeNode* root, int L, int R) {
        if(!root) return 0;
        if(root->val >= L && root->val <= R) return rangeSumBST(root->left, L, R) + rangeSumBST(root->right, L, R) + root->val;
        else return rangeSumBST(root->left, L, R) + rangeSumBST(root->right, L, R);
    }
};
```
```前序遍历 []
class Solution {
public:
    int rangeSumBST(TreeNode* root, int L, int R) {
        int res = 0;
        stack<TreeNode*> stk;
        TreeNode* cur = root;
        while(cur || stk.size()) {
            while(cur) {
                stk.push(cur);
                if(cur->val >= L && cur->val <= R) res += cur->val;
                cur = cur->left;
            }
            cur = stk.top();
            stk.pop();
            cur = cur->right;
        }
        return res;
    }
};
```

```中序遍历 []
class Solution {
public:
    int rangeSumBST(TreeNode* root, int L, int R) {
        int res = 0;
        stack<TreeNode*> stk;
        TreeNode* cur = root;
        while(cur || stk.size()) {
            while(cur) {
                stk.push(cur);
                cur = cur->left;
            }
            cur = stk.top();
            stk.pop();
            if(cur->val >= L && cur->val <= R) res += cur->val;
            cur = cur->right;
        }
        return res;
    }
};
```
```后序遍历 []
class Solution {
public:
    int rangeSumBST(TreeNode* root, int L, int R) {
        int res = 0;
        stack<TreeNode*> stk;
        TreeNode* cur = root;
        while(cur || stk.size()) {
            while(cur) {
                stk.push(cur);
                if(cur->val >= L && cur->val <= R) res += cur->val;
                cur = cur->right;
            }
            cur = stk.top();
            stk.pop();
            cur = cur->left;
        }
        return res;
    }
};
```

```层序遍历 []
class Solution {
public:
    int rangeSumBST(TreeNode* root, int L, int R) {
        queue<TreeNode*> q;
        int res = 0;
        if(root) q.push(root);
        while(q.size()) {
            int n = q.size();
            for(int i = 0; i < n; i ++) {
                TreeNode* tr = q.front();
                q.pop();
                if(tr->val >= L && tr->val <= R) res += tr->val;
                if(tr->left) q.push(tr->left);
                if(tr->right) q.push(tr->right);
            }
        }
        return res;
    }
};
```

