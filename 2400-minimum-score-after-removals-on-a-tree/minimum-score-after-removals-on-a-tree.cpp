class Solution {
public:
    std::vector<int> subtree_xor;
    std::vector<std::vector<int>> adj;
    std::vector<int> tin, tout;
    int timer;
    void dfs(int u, int p, const std::vector<int>& nums) {
        tin[u] = ++timer;
        subtree_xor[u] = nums[u];
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, nums);
                subtree_xor[u] ^= subtree_xor[v];
            }
        }
        tout[u] = ++timer;
    }
    bool is_ancestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }
    int minimumScore(std::vector<int>& nums, std::vector<std::vector<int>>& edges) {
        int n = nums.size();
        adj.assign(n, {});
        subtree_xor.assign(n, 0);
        tin.assign(n, 0);
        tout.assign(n, 0);
        timer = 0;
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        dfs(0, -1, nums);
        int total_xor = subtree_xor[0];
        int min_score_diff = INT_MAX;
        for (int i = 0; i < edges.size(); ++i) {
            for (int j = i + 1; j < edges.size(); ++j) {
                int u1 = edges[i][0], v1 = edges[i][1];
                int u2 = edges[j][0], v2 = edges[j][1];
                if (tin[u1] > tin[v1]) std::swap(u1, v1);
                if (tin[u2] > tin[v2]) std::swap(u2, v2);
                int child1 = v1;
                int child2 = v2;
                int score1, score2, score3;
                if (is_ancestor(child1, child2)) {
                    score1 = subtree_xor[child2];
                    score2 = subtree_xor[child1] ^ subtree_xor[child2];
                    score3 = total_xor ^ subtree_xor[child1];
                } else if (is_ancestor(child2, child1)) {
                    score1 = subtree_xor[child1];
                    score2 = subtree_xor[child2] ^ subtree_xor[child1];
                    score3 = total_xor ^ subtree_xor[child2];
                } else {
                    score1 = subtree_xor[child1];
                    score2 = subtree_xor[child2];
                    score3 = total_xor ^ score1 ^ score2;
                }
                int max_val = std::max({score1, score2, score3});
                int min_val = std::min({score1, score2, score3});
                min_score_diff = std::min(min_score_diff, max_val - min_val);
            }
        }
        return min_score_diff;
    }
};