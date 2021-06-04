//public List<List<String>> findLadders(String beginWord, String endWord, List<String> wordList) {
//    List<List<String>> result = new ArrayList<List<String>>();
//
//    Set<String> words = new HashSet<>(wordList);
//    if(!words.contains(endWord))
//        return result;
//
//    Set<String> beginSet = new HashSet<>();
//    Set<String> endSet = new HashSet<>();
//    beginSet.add(beginWord);
//    endSet.add(endWord);
//
//    //HashSet to store all possible transformations.
//    HashMap<String, List<String>> map = new HashMap<>();
//    //bidirectional BFS method.
//    biBFS(beginSet, endSet, words, map, false);
//
//    //if(!hasSequence) return result;
//
//    List<String> temp = new ArrayList<String>(Arrays.asList(beginWord));
//    DFS(beginWord, endWord, map, result, temp);
//
//    return result;
//}
//
//private void  biBFS(Set<String> beginSet, Set<String> endSet, Set<String> words, HashMap<String, List<String>> map, boolean reverse){
//
//    if (beginSet.size() > endSet.size()) {
//        biBFS(endSet, beginSet, words, map, !reverse);
//        return;
//    }
//
//    boolean found = false;
//    words.removeAll(beginSet);
//    Set<String> nextSequence = new HashSet<>();
//
//    //BFS from beginSet.
//    for(String oldWord : beginSet){
//        char[] charSet = oldWord.toCharArray();
//        for(int i=0; i< charSet.length; i++){
//            char c = charSet[i];
//            for(char j='a'; j<= 'z'; j++){
//                charSet[i] = j;
//                String newWord = new String(charSet);
//
//                if(words.contains(newWord)){
//                    if(endSet.contains(newWord)){
//                        found = true;
//                    }else{
//                        nextSequence.add(newWord);
//                    }
//                    // build the map in the direction of shorter set to longer set depending on the size of the set.
//
//                    String key = reverse ? newWord : oldWord;
//                    String val = reverse ? oldWord : newWord;
//
//                    if (!map.containsKey(key)) {
//                        map.put(key, new ArrayList());
//                    }
//                    map.get(key).add(val);
//                }
//            }
//            charSet[i] = c;
//        }
//    }
//    if(!found && !nextSequence.isEmpty()){
//        biBFS(nextSequence,endSet, words, map, reverse);
//    }
//}
//
//private void DFS(String beginWord, String endWord, HashMap<String, List<String>> map, List<List<String>> result, List<String> temp){
//    if(beginWord.equals(endWord)) { //boundary case.
//        result.add(new ArrayList<String>(temp));
//    }
//
//    if(!map.containsKey(beginWord)) return; //if the beginWord is not in map, then it is not the shortest path to the endWord.
//
//    for(String s : map.get(beginWord)){
//        temp.add(s);
//        DFS(s, endWord, map, result, temp);
//        temp.remove(temp.size()-1); //remove the added word.
//    }
//}
//
//class Solution
//{
//public:
//    // DFS function to find out every possible path
//    void dfs(unordered_map<string,vector<string>>&m,vector<vector<string>>&ans,vector<string>tmp,string node,string end)
//    {
//        tmp.push_back(node);
//        if(node==end)
//        {
//            ans.push_back(tmp);
//            return;
//        }
//        for(auto it:m[node])
//        {
//            dfs(m,ans,tmp,it,end);
//        }
//    }
//    vector<vector<string>>findLadders(string begin,string end,vector<string>&word)
//    {
//        unordered_set<string>dict(word.begin(),word.end()); // for faster lookup
//        // If the endWord doesn't exist in the list then return an emty list.
//        if(dict.find(end)==dict.end())
//        {
//            return {};
//        }
//        vector<vector<string>>ans; // For storing the answer
//        unordered_map<string,int>dist; // for stroing the level in graph
//        queue<string>q; // for BFS
//        unordered_map<string,vector<string>>m; // adjacency list
//        q.push(begin);   // start with the beginWord
//        dist[begin]=1;   // the beginWord is always at the level = 1
//        while(!q.empty())
//        {
//            string node=q.front();
//            q.pop();
//            // If we've found the endWord the we can break
//            if(node==end)
//            {
//                break;
//            }
//            else
//            {
//                for(int i=0;i<node.length();i++)
//                {
//                    string newWord=node;
//                    // try to fill with all the alphabets
//                    for(char c='a';c<='z';c++)
//                    {
//                        newWord[i]=c;
//                        // If the newWord is present in the list then add the edge
//                        if(dict.find(newWord)!=dict.end())
//                        {
//                            if(dist.find(newWord)==dist.end())
//                            {
//                                q.push(newWord); // push it to the queue
//                                dist[newWord]=dist[node]+1; //update the level
//                                m[node].push_back(newWord); // add the edge
//                            }
//                            else if(dist[newWord]==dist[node]+1)
//                            {
//                                m[node].push_back(newWord);
//                            }
//                        }
//                    }
//                }
//            }
//        }
//        // If endWord is not included in the graph finally then return an empty list
//        if(dist.find(end)==dist.end())
//        {
//            return {};
//        }
//        // apply dfs to find out every possible path.
//        dfs(m,ans,{},begin,end);
//        return ans;
//    }
//};
vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
    vector<vector<string>> ans;
    unordered_set<string> dict(wordList.begin(),wordList.end());
    if(!dict.count(endWord))return ans;
    map<string,vector<string>> m;
    unordered_set<string> set1({beginWord}),set2({endWord}), tmp;
    vector<string> path ={beginWord};

    bool set1IsFront = true, found = false;
    while (!set1.empty() && !set2.empty()) {
        for (auto s: set1) {
            dict.erase(s);
            string s1 = s;
            for (auto &c : s1) {
                const char origin = c;
                for (c = 'a'; c < 'z';   c++) {
                    if (set2.count(s1)) {
                        set1IsFront ? m[s].push_back(s1) : m[s1].push_back(s);
                        found = true;

                    } else if (!found && dict.count(s1)) {
                        set1IsFront ? m[s].push_back(s1) : m[s1].push_back(s);
                        tmp.insert(s1);
                    }
                }
                c = origin;
            }
        }
        if (found) break;
        for(auto w :tmp) dict.erase(w);
        if(tmp.size() > set2.size()){
            swap(tmp, set2);
            set1IsFront =!set1IsFront;
        }
        set1 = move(tmp); tmp.clear();


    }
    if(found) genLadders(beginWord,endWord,m,path,ans);
    return ans;
}

void genLadders(string start, string end, map<string,vector<string>> &m, vector<string> &path, vector<vector<string>> &ans) {
    if (start == end) {
        ans.push_back(path);
        return;
    }
    for (auto s :m[start]) {
        path.push_back(s);
        genLadders(s, end, m, path, ans);
        path.pop_back();
    }
}