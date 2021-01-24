# 题意分析
拿到题目先分析思路。不同用户是否可以合并的唯一条件为：用户的邮箱列表中存在相同的邮箱。因此可以通过邮箱作为中转，将不同用户连接，最终能将所有用户构造出多少个连通图，就有多少个合并后的用户。
所以，这是一道非常经典的连通图问题，那么解法就是套用并查集的模板。

# 算法分析

第一步先把并查集的模板代码写出来：
```python3
n = len(accounts)
uf = list(range(n))

def union(a: int, b: int):
    uf[find(a)] = find(b)

def find(x: int) -> int:
    if uf[x] != x:
        uf[x] = find(uf[x])
    return uf[x]
```

既然要通过邮箱做连接用户，需要先初始化一个字典 `dict`，`key` 为邮箱名，`value` 为第一次出现该邮箱的 account 的位置索引。
当遍历 `accounts` 列表时：
- 如果 `accounts[i]` 中的邮箱是第一次出现，则把该 `email -> i` 映射存入字典中；
- 如果 `accounts[i]` 的邮箱不是第一次出现，则把第一次出现该邮箱的 account 索引和当前索引 `i` 做并查集的关联 `union(dict[email], i)`；

邮箱字典的初始化和并查集的初始化代码如下：

```python
# key is email, value is the `first` index of accounts which has the key email
email_dict = {}
for i in range(n):
    account = accounts[i]
    for j in range(1, len(account)):
        if account[j] not in email_dict:
            email_dict[account[j]] = i
        else:
            union(email_dict[account[j]], i)
```

在对 `accounts` 完成全部遍历后，每一个 `account` 的索引都已经写进并查集中了。接下来就需要统计，究竟有多少个连通图。是否联通的唯一条件为：祖先是否为同一个，将同一个祖先的 `account` 索引归集在同一个列表中。因此计算连通图的代码很好写出：

```python
graphs = collections.defaultdict(list)
for i in range(n):
    parent = find(i)
    graphs[parent].append(i)
```

最后，就需要将上面 `graphs` 中同一个祖先的用户连通图，合并为一个用户，塞进答案里：

```python
ans = []
for idx, idx_list in graphs.items():
    cur = [accounts[idx][0]]
    emails = set()
    for i in idx_list:
        emails.update(accounts[i][1:])
    emails = list(emails)
    emails.sort()
    cur.extend(emails)
    ans.append(cur)
```

# 最终代码

合并上面的代码段，最终 AC 的代码如下：

```python
class Solution:
    def accounts_merge(self, accounts: List[List[str]]) -> List[List[str]]:
        def union(a: int, b: int):
            uf[find(a)] = find(b)

        def find(x: int) -> int:
            if uf[x] != x:
                uf[x] = find(uf[x])
            return uf[x]

        n = len(accounts)
        uf = list(range(n))
        email_dict = {}  # key is email, value is the `first` index of accounts which has the key email
        for i in range(n):
            account = accounts[i]
            for j in range(1, len(account)):
                if account[j] not in email_dict:
                    email_dict[account[j]] = i
                else:
                    union(email_dict[account[j]], i)
        graphs = collections.defaultdict(list)
        for i in range(n):
            graphs[find(i)].append(i)
        ans = []
        for idx, idx_list in graphs.items():
            cur = [accounts[idx][0]]
            emails = set()
            for i in idx_list:
                emails.update(accounts[i][1:])
            emails = list(emails)
            emails.sort()
            cur.extend(emails)
            ans.append(cur)
        return ans
```

![WechatIMG16.jpeg](https://pic.leetcode-cn.com/1610974881-mpHJeJ-WechatIMG16.jpeg)
