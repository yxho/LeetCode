### 解题思路
设置虚拟父节点为N，将边界上的'O'与虚拟父节点连接起来，采用并查集把'O'的元素连通起来,最后把不是与虚拟父节点的'O'区域改为'X'即可；其中并查集采用压缩路径的方式可以防止超时。

### 代码

```cpp
class UnionSet{
public:
    UnionSet(int n){
        this->m_n=n;
        this->father=new int[n];
        for(int i=0;i<n;i++){
            father[i]=i;
        }
    }
    int find(int x){
        //采用路径压缩可以减少时间
        return father[x]=(father[x]==x?x:find(father[x]));
        //if(father[x]==x) return x;
        //return find(father[x]);
    }
    void  merge(int x,int y){
        int fx=find(x),fy=find(y);
        if(fx==fy) return;
        father[fx]=fy;
    }
    bool isconnect(int x,int y){
        return find(x)==find(y);
    }
    ~UnionSet(){
        delete[]father;
    }
private:
    int *father;
    int m_n;
};

class Solution {
public:
    int node(int x,int y,int j){
        return x*j+y;
    }
    int dir[2][2]={0,1,1,0};
    void solve(vector<vector<char>>& board) {
        if(board.size()==0||board[0].size()==0) return ;
        UnionSet u=UnionSet(board.size()*board[0].size()+1);
        int dummpy_fa=board.size()*board[0].size();
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[0].size();j++){
                if(board[i][j]!='O') continue;
                bool edge=i==0||i==board.size()-1||j==0||j==board[0].size()-1;
                for(int k=0;k<2;k++){
                    int xx=i+dir[k][0];
                    int yy=j+dir[k][1];
                    if(xx<board.size()&&yy<board[0].size()&&board[xx][yy]=='O'){
                        u.merge(node(xx,yy,board[0].size()),node(i,j,board[0].size()));
                    }
                }
                if(!edge) continue;
                u.merge(node(i,j,board[0].size()),dummpy_fa);
            }
        }
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[0].size();j++){
                if(board[i][j]!='O') continue;
                if(!u.isconnect(dummpy_fa,node(i,j,board[0].size()))){
                    board[i][j]='X';
                }
            }
        }
    }
};
```