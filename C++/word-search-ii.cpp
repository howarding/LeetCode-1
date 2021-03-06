// Time:  O(m * n * h), h is height of trie
// Space: O(26^h)

class Solution {
private:
    struct TrieNode {
        bool isString = false;
        unordered_map<char, TrieNode *> leaves;
        
        bool Insert(const string& s) {
            auto* p = this;
            for (const auto& c : s) {
                if (p->leaves.find(c) == p->leaves.cend()) {
                    p->leaves[c] = new TrieNode;
                }
                p = p->leaves[c];
            }
            
            // s already existed in this trie.
            if (p->isString) {
                return false;
            } else {
                p->isString = true;
                return true;
            }
        }
        
        ~TrieNode() {
            for (auto& kv : leaves) {
                if (kv.second) {
                    kv.second->~TrieNode();
                }
            }
        }
    };
    
public:
    /**
     * @param board: A list of lists of character
     * @param words: A list of string
     * @return: A list of string
     */
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        unordered_set<string> ret;
        vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
        string curr;
        TrieNode trie;
        for (const auto& word : words) {
            trie.Insert(word);
        }
        
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                findWordsDFS(board, visited, &trie, i, j, curr,  ret);
            }
        }
        
        return vector<string>(ret.begin(), ret.end());
    }
    
    void findWordsDFS(vector<vector<char>> &grid,
             vector<vector<bool>> &visited,
             TrieNode *trie,
             int i,
             int j,
             string curr,
             unordered_set<string> &ret) {
        // Invalid state.
        if (!trie || i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) {
            return;
        }
        
        // Not in trie or visited.
        if (!trie->leaves[grid[i][j] ] || visited[i][j]) {
            return;
        }
        
        // Get next trie nodes.
        TrieNode *nextNode = trie->leaves[grid[i][j]];
        
        // Update current string.
        curr.push_back(grid[i][j]);
        
        // Find the string, add to the answers.
        if (nextNode->isString) {
            ret.insert(curr);
        }
        
        // Marked as visited.
        visited[i][j] = true;
        
        // Try each direction.
        vector<pair<int, int>> direction{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        for (int k = 0; k < 4; ++k) {
            findWordsDFS(grid, visited, nextNode,
                          i + direction[k].first, j + direction[k].second, curr, ret);
        }
        
        visited[i][j] = false;
    }
};
