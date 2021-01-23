# 解题思路；
从题目描述：要返回某员工及其所有下属的 重要度；
  因此 可以从某员工求出其所有直系员工的重要度
但如果求所有下属？
1.因为**每一个 员工都关联其直系下属，**那么再重复求上面的直系下属的直系下属即开始递归
便可求出其即其所有下属的重要度。

# 代码
```
class Solution {    
public:
    int getImportance(vector<Employee *> employees, int id) {
        int sum = 0;
        for (const auto &a : employees) { //先遍历所有员工，找出匹配id的员工
            if (id == a->id) {  //找着了
                sum += a->importance;   //加上重要度
                for (const auto &under_id : a->subordinates) { //在遍历所有员工，找出每个直系下属
                    sum += getImportance(employees, under_id);
                    //找每个直系员工的下属，相当再重来一遍的过程。就形成dfs了
                }
                return sum; //返回这个员工及其下属的重要度之和
            }
        }
        return 0;
    }
};
```
