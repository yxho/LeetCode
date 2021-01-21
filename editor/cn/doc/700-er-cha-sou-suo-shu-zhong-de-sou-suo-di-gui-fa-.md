> **点击上方，关注「代码随想录」，算法路上不迷路！**

# 思路 

之前我们讲了都是普通二叉树，那么接下来看看二叉搜索树。

在[关于二叉树，你该了解这些！](https://mp.weixin.qq.com/s/_ymfWYvTNd2GvWvC5HOE4A)中，我们已经讲过了二叉搜索树。

二叉搜索树是一个有序树：

* 若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
* 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
* 它的左、右子树也分别为二叉搜索树 

这就决定了，二叉搜索树，递归遍历和迭代遍历和普通二叉树都不一样。

本题，其实就是在二叉搜索树中搜索一个节点。那么我们来看看应该如何遍历。

## 递归法

1. 确定递归函数的参数和返回值

递归函数的参数传入的就是根节点和要搜索的数值，返回的就是以这个搜索数值所在的节点。

代码如下：

```
TreeNode* searchBST(TreeNode* root, int val)
```

2. 确定终止条件

如果root为空，或者找到这个数值了，就返回root节点。

```
if (root == NULL || root->val == val) return root;
```

3. 确定单层递归的逻辑

看看二叉搜索树的单层递归逻辑有何不同。

因为二叉搜索树的节点是有序的，所以可以有方向的去搜索。

如果root->val > val，搜索左子树，如果root->val < val，就搜索右子树，最后如果都没有搜索到，就返回NULL。

代码如下：

```
if (root->val > val) return searchBST(root->left, val); // 注意这里加了return 
if (root->val < val) return searchBST(root->right, val);
return NULL;
```

这里可能会疑惑，在递归遍历的时候，什么时候直接return 递归函数的返回值，什么时候不用加这个 return呢。

我们在[二叉树：递归函数究竟什么时候需要返回值，什么时候不要返回值？](https://mp.weixin.qq.com/s/6TWAVjxQ34kVqROWgcRFOg)中讲了，如果要搜索一条边，递归函数就要加返回值，这里也是一样的道理。

**因为搜索到目标节点了，就要立即return了，这样才是找到节点就返回（搜索某一条边），如果不加return，就是遍历整棵树了。**

整体代码如下：

```
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if (root == NULL || root->val == val) return root;
        if (root->val > val) return searchBST(root->left, val);
        if (root->val < val) return searchBST(root->right, val);
        return NULL;
    }
};
```
PS：**相信很多小伙伴刷题的时候面对力扣上近两千到题目，感觉无从下手**，我花费半年时间整理了Github项目：[leetcode刷题攻略](https://github.com/youngyangyang04/leetcode-master)。 里面有**100多道经典算法题目刷题顺序、配有40w字的详细图解，常用算法模板总结，以及难点视频讲解**，按照list一道一道刷就可以了！star支持一波吧！

## 迭代法

一提到二叉树遍历的迭代法，可能立刻想起使用栈来模拟深度遍历，使用队列来模拟广度遍历。

对于二叉搜索树可就不一样了，因为二叉搜索树的特殊性，也就是节点的有序性，可以不使用辅助栈或者队列就可以写出迭代法。

对于一般二叉树，递归过程中还有回溯的过程，例如走一个左方向的分支走到头了，那么要调头，在走右分支。

而**对于二叉搜索树，不需要回溯的过程，因为节点的有序性就帮我们确定了搜索的方向。** 

例如要搜索元素为3的节点，**我们不需要搜索其他节点，也不需要做回溯，查找的路径已经规划好了。**

中间节点如果大于3就向左走，如果小于3就向右走，如图：
![700.二叉搜索树中的搜索1.png](https://pic.leetcode-cn.com/1606654120-WJvQuF-700.%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E4%B8%AD%E7%9A%84%E6%90%9C%E7%B4%A21.png)



所以迭代法代码如下：

```
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root != NULL) {
            if (root->val > val) root = root->left;
            else if (root->val < val) root = root->right;
            else return root;
        }
        return NULL;
    }
};
```

第一次看到了如此简单的迭代法，是不是感动的痛哭流涕，哭一会~

# 总结 

本篇我们介绍了二叉搜索树的遍历方式，因为二叉搜索树的有序性，遍历的时候要比普通二叉树简单很多。

但是一些同学很容易忽略二叉搜索树的特性，所以写出遍历的代码就未必真的简单了。

所以针对二叉搜索树的题目，一样要利用其特性。

文中我依然给出递归和迭代两种方式，可以看出写法都非常简单，就是利用了二叉搜索树有序的特点。


我是程序员Carl，可以找我[组队刷题](https://img-blog.csdnimg.cn/20201115103410182.png)，「代码随想录」目前正在循序渐进讲解算法，目前已经讲到了动态规划，[点击这里](https://img-blog.csdnimg.cn/20210102121706654.png)和上万录友一起打卡学习，来看看，你一定会发现相见恨晚！

**如果感觉题解对你有帮助，不要吝啬给一个👍吧！**
