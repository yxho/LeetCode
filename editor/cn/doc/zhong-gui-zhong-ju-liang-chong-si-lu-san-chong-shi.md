### 解题思路
思路1：直接map统计频率排序。

思路2： 统计频率，但用堆基于map合并后的结果排序。速度更快。

### 代码

```cpp
// O(NlgN) algorithm, where N is length of string s
class Solution1 {
public:
    string frequencySort(string s) {
        unordered_map<char, int> mp;
        for (const auto& ch : s) {
            mp[ch]++;
        }

        auto cmp = [&](const auto& a, const auto& b) {
            return mp[a] > mp[b] || (mp[a] == mp[b] && a < b);
        };

        sort(s.begin(), s.end(), cmp);
        return s;
    }
};

// O(Nlg(26 + 26)) = O(N) algorithm, assume only lower and upper case letters.
// Where N is length of string s
// customized priority_queue
class Solution2 {
public:
    string frequencySort(string s) {
        unordered_map<char, int> mp;
        for (const auto& ch : s) {
            mp[ch]++;
        }

        typedef pair<char, int> PCI;
        auto cmp = [&](const auto& a, const auto& b) {
            return a.second < b.second || (a.second == b.second && a > b);
        };

        priority_queue<PCI, vector<PCI>, decltype(cmp)> pq(cmp);
        for (const auto& m : mp) {
            pq.push(m);
        }

        string res;
        while (!pq.empty()) {
            auto cur = pq.top(); pq.pop();
            res += string(cur.second, cur.first);
        }

        return res;
    }
};

// O(Nlg(26 + 26)) = O(N) algorithm, assume only lower and upper case letters.
// Where N is length of string s
// No customized priority_queue
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> mp;
        for (const auto& ch : s) {
            mp[ch]++;
        }

        priority_queue<pair<int, char>> pq;
        for (const auto& m : mp) {
            pq.push({m.second, m.first});
        }

        string res;
        while (!pq.empty()) {
            auto cur = pq.top(); pq.pop();
            res += string(cur.first, cur.second);
        }

        return res;
    }
};
```