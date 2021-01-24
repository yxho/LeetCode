### 解题思路
没用并查集

### 代码

```java
class Solution {
    public List<List<String>> accountsMerge(List<List<String>> accounts) {
        List<List<String>> res = new ArrayList<>();
        Map<String, Integer> map = new HashMap<>();
        List<String> name = new ArrayList<>();
        List<Set<String>> new_accounts = new ArrayList<>();
        Set<Integer> abandon = new HashSet<>();
        int index = 0;
        for (List<String> account : accounts) {
            List<Integer> indexes = new ArrayList<>();
            for (int j = 1; j < account.size(); j++) {
                if (map.containsKey(account.get(j))&&!indexes.contains(map.get(account.get(j))))
                    indexes.add(map.get(account.get(j)));
            }
            if (indexes.isEmpty()) {
                Set<String> set = new HashSet<>();
                name.add(account.get(0));
                for (int j = 1; j < account.size(); j++) {
                    map.put(account.get(j), index);
                    set.add(account.get(j));
                }
                new_accounts.add(set);
                index++;
            } else {
                Collections.sort(indexes);
                int index0 = indexes.get(0);
                for (int j = 1; j < account.size(); j++) {
                    map.put(account.get(j), index0);
                    new_accounts.get(index0).add(account.get(j));
                }
                for (int l = 1; l < indexes.size(); l++) {
                    int cur_index = indexes.get(l);
                    abandon.add(cur_index);
                    for (String str : new_accounts.get(cur_index)) {
                        new_accounts.get(index0).add(str);
                        map.put(str, index0);
                    }
                }
            }
        }
        for (int i = 0; i < name.size(); i++) {
            if (abandon.contains(i))
                continue;
            List<String> temp = new ArrayList<>(new_accounts.get(i));
            Collections.sort(temp);
            temp.add(0, name.get(i));
            res.add(temp);
        }
        return res;
    }
}
```