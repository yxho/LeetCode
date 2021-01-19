### 解题思路
dfs,发现1就把1变成0；直到上下左右都找不出1为止。
注意的点就是遍历grid的过程中一定要用引用，否则dfs所修改的内容无法作用到函数外。
### 代码

```cpp
class Solution {
public:
    void island(vector<vector<char>>& grid, int i, int j){ //dfs出现1时保证把以该起点出发的所有发现的上下左右为1的值改为0；
        if(i<grid.size()&&j<grid[i].size()&&grid[i][j]=='1') grid[i][j] = '0'; //是1修改为0，再找其上下左右周围为1的位置。
        else return; //不是1，就直接返回
        island(grid,i+1,j); //下
        island(grid,i-1,j); //上
        island(grid,i,j+1); //右
        island(grid,i,j-1); //左
        return; //上下左右都不是1就返回
    }
    int numIslands(vector<vector<char>>& grid) {
        int cnt = 0;
        int i = 0; //行号
        for(vector<char> &temp:grid){ //这里注意一定要用引用
            int j = 0; //列号
            for(char &temp_c : temp){ //这里也要用引用
                if(temp_c=='0') {j++;continue;} //遍历如果为0就继续
                island(grid,i,j); //如果不为零就进行dfs，并且岛数量加1；
                cnt++;
                j++;
            }
            i++;
        }
        return cnt;
    }
};
```