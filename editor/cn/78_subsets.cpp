//给你一个整数数组 nums ，返回该数组所有可能的子集（幂集）。解集不能包含重复的子集。 
// 
//
// 示例 1： 
//
// 
//输入：nums = [1,2,3]
//输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
// 
//
// 示例 2： 
//
// 
//输入：nums = [0]
//输出：[[],[0]]
// 
//
// 
//
// 提示： 
//
// 
// 1 <= nums.length <= 10 
// -10 <= nums[i] <= 10 
// 
// Related Topics 位运算 数组 回溯算法 
// 👍 956 👎 0

#include "include/headers.h"

using namespace std;
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        backTrace(0,nums);
        return res;
    }
private:
    void backTrace(int index,vector<int>& nums){
        if(index == nums.size()){
            res.push_back(path);
            return;
        }
        path.push_back(nums[index]);
        backTrace(index+1,nums);
        path.pop_back();
        backTrace(index+1,nums);

    }

    vector<vector<int>> res;
    vector<int> path;
};
//leetcode submit region end(Prohibit modification and deletion)

int main()
{
    Solution s;
    vector<int> data{7, 1, 5, 3, 6, 4};
    //vector<int> ans = s.twoSum(data,11);
    //cout << ans[0]<<ans[1]<<endl;
    cout<<"Hello LeetCode"<<endl;
}