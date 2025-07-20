class Solution {
public:
    struct TrieNode {
        unordered_map<string, TrieNode*> children;
        string name;
        bool toDelete = false;
    };

    unordered_map<string, int> freq; 

    // Step 1: Insert path into Trie
    void insert(TrieNode* root, const vector<string>& path) {
        TrieNode* node = root;
        for (const string& folder : path) {
            if (!node->children.count(folder)) {
                node->children[folder] = new TrieNode();
                node->children[folder]->name = folder;
            }
            node = node->children[folder];
        }
    }

    // Step 2: Serialize each subtree
    string serialize(TrieNode* node) {
        if (node->children.empty()) return "";

        vector<string> subs;
        for (auto& [name, child] : node->children) {
            subs.push_back(name + "(" + serialize(child) + ")");
        }

        sort(subs.begin(), subs.end());  // Ensure serialization
        string serial = accumulate(subs.begin(), subs.end(), string());
        freq[serial]++;
        return serial;
    }

    // Step 3: Mark duplicates
    string mark(TrieNode* node) {
        if (node->children.empty()) return "";

        vector<string> subs;
        for (auto& [name, child] : node->children) {
            subs.push_back(name + "(" + mark(child) + ")");
        }

        sort(subs.begin(), subs.end());
        string serial = accumulate(subs.begin(), subs.end(), string());

        if (freq[serial] > 1) {
            node->toDelete = true;
        }

        return serial;
    }

    // Step 4: Collect valid paths (non-deleted)
    void collect(TrieNode* node, vector<string>& currentPath, vector<vector<string>>& result) {
        for (auto& [name, child] : node->children) {
            if (child->toDelete) continue;

            currentPath.push_back(name);
            result.push_back(currentPath);
            collect(child, currentPath, result);
            currentPath.pop_back();
        }
    }

    // Main function
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        TrieNode* root = new TrieNode();

        // 1. Build Trie from paths
        for (const auto& path : paths) {
            insert(root, path);
        }

        // 2. Serialize to count duplicate structures
        for (auto& [name, child] : root->children) {
            serialize(child);
        }

        // 3. Mark duplicates
        for (auto& [name, child] : root->children) {
            mark(child);
        }

        // 4. Collect result
        vector<vector<string>> result;
        vector<string> currentPath;
        collect(root, currentPath, result);

        return result;
    }
};