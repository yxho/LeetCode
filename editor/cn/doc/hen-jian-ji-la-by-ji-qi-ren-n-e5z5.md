cur(也就是dp[i])表示从开头到位置i有多少种解码方式,pre是dp[i-1]
```
class Solution {
    public int numDecodings(String s) {
        int pre = 1;
        int cur = 1;
        //第一个字母
        if(s.charAt(0)=='0') return 0;
        for(int i=1;i<s.length();i++){
            int b = cur;
            if(s.charAt(i)=='0'){
                cur = 0;
            }
            int tmp = (s.charAt(i-1)-'0')*10+s.charAt(i)-'0';//如果用Integer.parseInt时间要慢很多
            if(tmp>=10&&tmp<=26) {
                cur += pre;
            }
            pre = b;
        }
        return cur;
    }
}
```
