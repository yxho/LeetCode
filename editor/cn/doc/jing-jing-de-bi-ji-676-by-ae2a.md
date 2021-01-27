### 解题思路
used记录是否替换过字母


### 代码

```cpp
class Trie{
public:
    bool isEnd;
    Trie* next[26];
    Trie(){
        isEnd=false;
        memset(next,0,sizeof(next));
    }
};
class MagicDictionary {
public:
    Trie* root;
    /** Initialize your data structure here. */
    MagicDictionary() {
        root=new Trie();
    }
    
    void buildDict(vector<string> dictionary) {
        for(auto& w:dictionary){
            Trie* node=root;
            for(auto& c:w){
                if(!node->next[c-'a'])
                    node->next[c-'a']=new Trie();
                node=node->next[c-'a'];
            }
            node->isEnd=true;
        }
    }
    bool find(string& word,int index,bool used,Trie* node){
        if(index==word.size())
            return node->isEnd&&used;
        if(!node->next[word[index]-'a']){
            if(used)
                return false;
            //如果找不到word[index]则替换
            else{
                for(int i=0;i<26;i++){
                    if(node->next[i]&&find(word,index+1,true,node->next[i]))
                        return true;
                }
                return false;
            }
        }
        else{
            //找到了word[index],不替换
            if(find(word,index+1,used,node->next[word[index]-'a']))
                return true;
            //找到了word[index],但是替换
            if(!used){
                for(int i=0;i<26;i++){
                    if(i!=word[index]-'a'&&node->next[i]&&find(word,index+1,true,node->next[i]))
                        return true;
                }
                return false;
            }
        }
        return false;
    }
    bool search(string searchWord) {
        return find(searchWord,0,false,root);
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */
```