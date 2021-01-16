### 解题思路
此题二分查找的关键难点在于右边界right的初始值设立。通常情况下，如果用左闭右开区间的写法left = 0, right = N, while (left < right), 如果相等直接返回，如果偏大 right = mid, 如果偏小left = mid + 1。但是该题不能直接应用。仔细想想为什么呢？因为常规的二分搜索，只是比较nums[i]跟target的大小关系，并不会访问两边的i+1或者i-1的值。故而设置为N没问题。但是该题我们要比较nums[mid]和nums[mid + 1]的关系，如果还是将right初始值设置为N，当mid = N - 1时，会越界访问nums[mid+1]=nums[N]，比如下面的例子：[3, 4]。一个巧妙的处理方法就是将right的初始值设置为N-1，这样整体往左偏移1，可以保证mid左右边的值也就是能访问到N-2的位置。这样mid+1=N-1仍然在合理的下标范围之内。如果判断偏小left=mid+1=N-1，right=N-1 不再满足left < right条件，退出。而此时要找的最大值恰好就就是N-1。其他情况比如[1, 3, 2], left = 0, right = 2, mid = 1, nums[mid]=nums[1] = 3 > nums[mid + 1] = nums[2] = 2, right = mid = 1, mid = (0 + 1) / 2 = 0, nums[mid] = nums[0] = 1 < nums[mid + 1] = nums[1] = 3, left = mid + 1 = 1, left = 1 < right = 1 不再成立，退出，此时left=1恰好是我们要找的peak位置坐标。因此总结一句话，此题只要将从常规的二分右边界right设小一点，设置为N-1（不是常规的N），采用左闭右开区间写法，比较mid和mid +1大小关系左右移动，就立即变为简单问题啦！

### 代码

```cpp
// Linear search 1
class Solution1 {
public:
    int findPeakElement(vector<int>& nums) {
        if (nums.empty()) {
            return -1;
        } else if (nums.size() == 1) {
            return 0;
        }

        int N = nums.size();
        nums.insert(nums.begin(), INT_MIN);
        nums.push_back(INT_MIN);
        for (int i = 1; i <= N; i++) {
           if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) {
               return i - 1;
           }
        }

        return -1;
    }
};

// Linear search 2
class Solution2 {
public:
    int findPeakElement(vector<int>& nums) {
        if (nums.empty()) {
            return -1;
        }

        int N = nums.size();
        for (int i = 0; i < N - 1; i++) {
           if (nums[i] > nums[i + 1]) {
               return i;
           }
        }

        return N - 1;
    }
};

// Binary search recursion
class Solution3 {
public:
    int findPeakElement(vector<int>& nums) {
        if (nums.empty()) {
            return -1;
        }
        
        int N = nums.size();
        return binarySearch(nums, 0, N - 1); 
    }

private:
    int binarySearch(vector<int>& nums, int left, int right) {
        if (left == right) {
            return left;
        }

        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[mid + 1]) {
            return binarySearch(nums, left, mid); // since mid could be the peak
        } else {
            return binarySearch(nums, mid + 1, right);
        }
    }
};

// Binary search iterative 
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if (nums.empty()) {
            return -1;
        }
        
        int N = nums.size();
        return binarySearch(nums, 0, N - 1); 
    }

private:
    int binarySearch(vector<int>& nums, int left, int right) {
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[mid + 1]) {
                right = mid; // since mid could be the peak
            } else {
                left = mid + 1;
            }
        }

        return left;
    }
};
```