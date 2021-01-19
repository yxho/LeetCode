### 解题思路
1. DFS/BFS(比较容易想到)
2. 并查集(附详细注释)

### 解法一 DFS 
![image.png](https://pic.leetcode-cn.com/1606097042-bNvKmw-image.png)

使用基于dfs的遍历 核心思路是遇到陆地就+1岛屿数量 然后把该陆地连通的所有陆地
全部标为2 防止后续重复计算 时间复杂度O（M^N）矩阵大小

注意： 题目为 vector<vector<char>> 不是 vector<vector<int>>
判断时是 grid[i][j]=='1'  而不是 grid[i][j]== 1    ！ 

### 代码

```cpp
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        // 遍历每一块
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                // 有陆地+1
                if(grid[i][j]=='1'){
                    count++;
                    // 遍历当前陆地连通的岛屿全部置为2
                    search(grid,i,j);
                }
            }
        }
        return count;
    }
    // dfs 遍历
    void search(vector<vector<char>>& grid, int i, int j){
        // 遍历到岛屿块
        if(inArea(i,j,grid.size(),grid[0].size()) && grid[i][j]=='1'){
            // visited 标为2 避免重复计算
            grid[i][j]='2';
            // 访问周边领接位置
            search(grid, i, j+1);
            search(grid, i, j-1);
            search(grid, i+1, j);
            search(grid, i-1, j);
        }
    }
    // 边界判断
    bool inArea(int i, int j, int row, int col){
        return (0<=i)&&(i<row)&&(0<=j)&&(j<col);
    }
};
```
### 解法二 并查集
![微信图片_20201123213748.png](https://pic.leetcode-cn.com/1606138688-dAeDiO-%E5%BE%AE%E4%BF%A1%E5%9B%BE%E7%89%87_20201123213748.png)


(1) 并查集（Disjoint-set）核心功能就是 (1)并 (2)查
Find: 查找元素所属子集
Unite：合并两个子集为一个新的集合
想更深入了解并查集可以参考两篇博客：
[并查集](https://blog.csdn.net/qq_38975553/article/details/108154673)
[并查集的C++实现及优化](https://www.jianshu.com/p/fc17847b0a31)

(2) 本质是 对于树形的集合可以利用数组进行索引和表示进行查找(有静态链表那味了)
(3) 解决本题的思路是，新建一个并查集类 包括parent母结点数组，rank秩数组(优化用)
和 count 数量
(4) 构造初始化时 需要全图遍历一次 把parent对应的有陆地的标号置为和parent数组下标一样的值。海洋都是-1
比如:

1 1 1 0
0 0 1 1

则 parent = [0,1,2,-1,-1,-1,6,7]
rank为秩 默认为0 若数有2个结点 则秩为1
比如前两个陆地 1 1 合并后 变为 parent = [1,1,2,-1,-1,-1,6,7] 第一块秩为1
count 初始化 遇到陆地就+1  比如 之前的count = 5
正式求解时 再遍历全图 每个点向上下左右四个方向合并 合并一块count--
之前的 会合并4次 count减去4次 就变成1了 只剩1块岛屿 
具体见代码 注释写的很详细了 求个赞~~~

### 代码
```cpp
// 定义并查集
class Djset {
private:
    // 数目
    int count;
    // 母结点集合
    vector<int> parent;
    // 秩（优化用）
    vector<int> rank;
public:
	// 初始构造函数 主要初始化3个私有成员
	// 默认parent数值为-1 一维，大小 是grid矩阵行数*列数
	// 默认rank 秩为 0 一维，大小 是grid矩阵行数*列数
	// 默认count数量为0
    Djset(vector<vector<char>>& grid):
    count(0),parent(vector<int>((grid.size()) * (grid[0].size()),-1)),
    rank(vector<int>((grid.size()) * (grid[0].size()), 0))
    {
        int row = grid.size();
        int col = grid[0].size();
        for(int i=0; i<row; ++i){
            for(int j=0; j<col; ++j){
                if(grid[i][j]=='1'){
// 初始化 若有陆地块 则母结点等于自己 否则是默认值-1
// 因为是二维 所以映射到一维数组需要转换一下关系
// : 行号*列数 + 列号                    
                    parent[i*col+j] = i*col+j;

// 遇到一块陆地就+1 后面根据连通分量再删
// 这个count 不是最终答案                    
                    count++;
                }
            }
        }
    }
	// 查 (找结点所在树的根节点) 如1->2->3->5  find(1) 得到 5
    int find(int x){
        // if(x!=parent[x]){
        // （1）路径压缩 优化
        // 所有子结点全部指向根节点 减少树的深度 但开销较大 不推荐
        //     parent[x] = find(parent[x]);
        // }
        // return parent[x];

        // （2）路径减半 优化
		// 使路径上每隔一个节点就指向其祖父节点(parent的parent)
		// 以 1->2->3->4->5 为例  若find(1) 路径查找优化为
		// 1->3->5 路径减半 减少树的深度 
        while(x!=parent[x]){
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
	// 并 (一个结点树并到另一个结点树上)
    void unite(int x1, int x2){
		// 使用秩优化 按秩合并 避免合成后变成单链表 O(n)复杂度
		// 找到 x1 和 x2两个树的根结点
        int f1 = find(x1);
        int f2 = find(x2);
		// 不相等才合并 相等就不需要合并了 证明在一棵树上
        if(f1!=f2){
		    // 秩f1>f2 f1长一些 把f2的树并在f1上 秩不增加 树总深度不变深
            if(rank[f1]>rank[f2]){
                parent[f2] = f1;  // 理解为 f2->f1
            }else{
		        // 秩f1<=f2 把f1的树并在f2上
                parent[f1] = f2;  // f1->f2
		        // 若 秩f1=f2 合并后秩会+1
		        // 例： f1:1->2  f2:3<-4   合： 1->2->3<-4 
                if(rank[f1]==rank[f2]){
                    rank[f2]++ ;
                }
            }
		    // 两块陆地合并成一块 减去一个数量 很重要！
            count--;
        }
    }
    int get_count() const{
        return count;
    }
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int row = grid.size();
        if(!row){return 0;}
        int col = grid[0].size();
        // 初始化并查集对象
        Djset djs(grid);
        // 全图遍历
        for(int i=0; i<row; ++i){
            for(int j=0; j<col; ++j){
                // 当前块为陆地
                if(grid[i][j]=='1'){
                    // 遍历过 避免重复
                    grid[i][j]='2';
                    // 向四个方向合并 有合并就会减去陆地数目得到最终的数目
                    // 向上
                    if(i-1>=0 && grid[i-1][j]=='1'){
                        djs.unite(i*col+j, (i-1)*col + j);
                    }
                    // 向左
                    if(j-1>=0 && grid[i][j-1]=='1'){
                        djs.unite(i*col+j, (i)*col + j-1);
                    }
                    // 向下
                    if(i+1<row && grid[i+1][j]=='1'){
                        djs.unite(i*col+j, (i+1)*col + j);
                    }
                    // 向右
                    if(j+1<col && grid[i][j+1]=='1'){
                        djs.unite(i*col+j, (i)*col + j+1);
                    }
                }
            }
        }
        // 得到最终数量
        return djs.get_count();       
    }
};
```
