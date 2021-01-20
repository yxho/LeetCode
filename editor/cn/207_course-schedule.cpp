//你这个学期必须选修 numCourse 门课程，记为 0 到 numCourse-1 。 
//
// 在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们：[0,1] 
//
// 给定课程总量以及它们的先决条件，请你判断是否可能完成所有课程的学习？ 
//
// 
//
// 示例 1: 
//
// 输入: 2, [[1,0]] 
//输出: true
//解释: 总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。所以这是可能的。 
//
// 示例 2: 
//
// 输入: 2, [[1,0],[0,1]]
//输出: false
//解释: 总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0；并且学习课程 0 之前，你还应先完成课程 1。这是不可能的。 
//
// 
//
// 提示： 
//
// 
// 输入的先决条件是由 边缘列表 表示的图形，而不是 邻接矩阵 。详情请参见图的表示法。 
// 你可以假定输入的先决条件中没有重复的边。 
// 1 <= numCourses <= 10^5 
// 
// Related Topics 深度优先搜索 广度优先搜索 图 拓扑排序 
// 👍 692 👎 0

#include "include/headers.h"

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
        vector<vector<int> > tolearn; // 当前课需要学哪些课
        vector<int> belearned; // 当前课被哪些课学习了
        tolearn.resize(numCourses);
        belearned.resize(numCourses);
        for (auto cur:prerequisites) {
            tolearn[cur[1]].push_back(cur[0]);
            ++belearned[cur[0]];
        }
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (belearned[i] == 0)   // 当前课不是任何课的前置课程
                q.push(i);
        }
        int ans = 0;
        while (!q.empty()) {
            ans++;
            int k = q.front();
            q.pop();
            for (auto u:tolearn[k]) {
                belearned[u]--; // 学完了，减一
                if (belearned[u] == 0)
                    q.push(u);
            }
        }
        return ans == numCourses;
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