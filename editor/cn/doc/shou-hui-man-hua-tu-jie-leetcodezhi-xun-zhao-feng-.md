## 1、正文
首先分析一下情况，如果 `mid` 一直比右侧的数小，那么 `mid` 处的值肯定不是峰值。
![在这里插入图片描述](https://pic.leetcode-cn.com/aa8b836b535fa186819d37f16417718c50c3ec111b447232ab263b189d1678ac.jpg)
确定一下 `left` 和 `right`，然后编写二分查找模板。

可以看到，如果 `nums[mid]>nums[mid+1]`，那么峰值一定在左侧，之所以没有等号，前面说过，题中强调没有重复数！
![在这里插入图片描述](https://pic.leetcode-cn.com/526a7ad7837e6dda80aa5cb31248cf7a55c85ce41079b7437acb0b2c7d54ad98.png)
## 2、代码
```c
int findPeakElement(int* nums, int numsSize){
    int left=0;
    int right=numsSize-1;
    while(left<right){
        int mid=left+(right-left)/2;
        if(nums[mid]>nums[mid+1]){
            right=mid;
        }
        else{
            left=mid+1;
        }
    }
    return left;
}
```
![在这里插入图片描述](https://pic.leetcode-cn.com/8750b9f984e7994db3812c447a0665554e363d96e4a58cb371ab5a35ec7ef3d7.png)
![在这里插入图片描述](https://pic.leetcode-cn.com/733bfca6d47492fb50aa1891f2e9679a28d5a70f35315db004deb4a08fb563ec.png)

> **如果有幸帮到你，请帮我点个【赞】，给个【关注】！如果能顺带【评论】给个鼓励，我将不胜感激。**

***欢迎关注 @我是管小亮，文字强迫症MAX~***