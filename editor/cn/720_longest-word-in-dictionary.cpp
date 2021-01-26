//给出一个字符串数组words组成的一本英语词典。从中找出最长的一个单词，该单词是由words词典中其他单词逐步添加一个字母组成。若其中有多个可行的答案，则返
//回答案中字典序最小的单词。 
//
// 若无答案，则返回空字符串。 
//
// 
//
// 示例 1： 
//
// 输入：
//words = ["w","wo","wor","worl", "world"]
//输出："world"
//解释： 
//单词"world"可由"w", "wo", "wor", 和 "worl"添加一个字母组成。
// 
//
// 示例 2： 
//
// 输入：
//words = ["a", "banana", "app", "appl", "ap", "apply", "apple"]
//输出："apple"
//解释：
//"apply"和"apple"都能由词典中的单词组成。但是"apple"的字典序小于"apply"。
// 
//
// 
//
// 提示： 
//
// 
// 所有输入的字符串都只包含小写字母。 
// words数组长度范围为[1,1000]。 
// words[i]的长度范围为[1,30]。 
// 
// Related Topics 字典树 哈希表 
// 👍 120 👎 0

#include "include/headers.h"

using namespace std;

//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    class Trie {
    private:
        bool isEnd;
        Trie *next[26];
    public:
        Trie() {
            isEnd = false;
            memset(next, 0, sizeof(next));
        }

        void insert(string &words) {
            Trie *node = this;
            for (auto &c:words) {
                if (node->next[c - 'a'] == nullptr) {
                    node->next[c - 'a'] = new Trie();
                }
                node = node->next[c - 'a'];
            }
            node->isEnd = true;
        }

        bool search(string &s) {
            Trie *node = this;
            for (auto &c:s) {
                if (node->next[c - 'a'] == nullptr) {
                    return false;
                }
                if (! node->next[c - 'a']->isEnd) {
                    return false;
                }
                node = node->next[c - 'a'];
            }
            return true;
        }
    };


    string longestWord(vector<string> &words) {
        Trie *t = new Trie();
        for (auto &s:words) {
            t->insert(s);
        }
        string res = "";
        for (auto &s:words) {
            if (t->search(s)) {
                if (s.size() > res.size() || (s.size() == res.size() && s < res)) {
                    res = s;
                }
            }
        }
        return res;
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