### 解题思路
这题难点在于怎么判断不符合条件的一半, 如果不能扔掉一半, 起码要不断地缩小空间. 每次拿到一个mid后, 如果它不等于target, 那么它可以将整个区间分为左侧[left, mid) 和右侧(mid, right), 而且整个两个区间值总有一个是有序的,  我们只有判断target是不是在有序的区间内, 是的话就可以把另外一半扔掉, 不在这有序的区间内的话, 就扔掉有序的这一半.

每一次二分后:  如果target已经找到, 可以直接返回, 
否则剩余区间可以分为2个部分[left, mid) 和 (mid, right);
情况1: nums[mid] > nums[left] : 暗示[left, mid) 有序的, (mid, right)则是螺旋的
*    判断target 是不是在[left, mid), 如果是则right = mid, 不在这个区间的话, 那么肯定在(mid, right), left = mid + 1;*
情况2: nums[mid] < nums[left] : 暗示(mid, right) 是有序的
*    判断target 是不是在(mid, right) 中, 如果是则left = mid +1, 不在这个区间的话, 那么肯定在[left, mid), right = mid;*
情况3: nums[mid] == nums[left], 无法区分,但是由于nums[mid] != target, 可以left++;


### 代码

```cpp
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if (nums.empty())
            return false;
        int left = 0;
        int right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return true;
            
            if (nums[mid] > nums[left]) { // mid左边的数组[left, mid)是有序的
                // target 就在[left, mid)中
                if (target >= nums[left] && target < nums[mid]) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            } else if (nums[mid] < nums[left]) {// mid 右边(mid, right)是有序的
                // target 就在(mid, right)中
                if (target > nums[mid] && target <= nums[right - 1])
                    left = mid + 1;
                else
                    right = mid;
            } else if (nums[mid] == nums[left]) {
                    left++;
            }
        }

        return false;
    }
};
```

// 用nums[right] 判断也是一样的, 每次扔掉一半, 就是不能扔掉一半, 也起码缩小一点空间 
```cpp
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if (nums.empty())
            return false;
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return true;
            
            if (nums[mid] > nums[right]) { // mid左边的数组是有序的
                if (target >= nums[left] && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else if (nums[mid] < nums[right]) {// mid 右边数组是有序的
                if (target > nums[mid] && target <= nums[right])
                    left = mid + 1;
                else
                    right = mid - 1;
            } else if (nums[mid] == nums[right]) {
                    right--;
            }
        }

        return false;
    }
};
```
