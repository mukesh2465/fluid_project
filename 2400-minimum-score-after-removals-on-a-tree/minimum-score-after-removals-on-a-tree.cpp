class Solution {
public:
    //dfs to compute in/out time n subtree Xor
    void dfs(int node,int parent,vector<int>&subtreeXor,vector<int>&inTime,vector<int>&outTime,int&time,vector<int>& nums,unordered_map<int,vector<int>>&adj){
        subtreeXor[node]=nums[node];//initially, XOR is the node's own value
        inTime[node]=time;//store time when entering that node
        time++;
        for(int&neigh:adj[node]){//go over all neighs
            //visit children
            if(neigh!=parent){
                dfs(neigh,node,subtreeXor,inTime,outTime,time,nums,adj);
                // XOR frm all child subtrees
                subtreeXor[node]=subtreeXor[node]^subtreeXor[neigh];
            }
        }
        outTime[node]=time;//store time when exiting that node
        time++;
    }
    //check if u is an ancestor of v using Euler Tour technique
    bool isAncestor(int u,int v,vector<int>&inTime,vector<int>&outTime){
        return inTime[v]>=inTime[u] && outTime[v]<=outTime[u];
    }
    // Score fnc = max - min of 3 xors
    int getScore(int a,int b,int c){
        int maxXor=max({a,b,c});
        int minXor=min({a,b,c});
        return maxXor-minXor;
    }
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        int n=nums.size();
        unordered_map<int,vector<int>> adj;
        for(auto &e:edges){
            int u=e[0]; int v=e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> subtreeXor(n,0);//subtreeXor[i] = XOR of values in subtree rooted at i
        //store time we reach that node in dfs call
        vector<int> inTime(n,0);//inTime[i] = time when DFS enters node i
        vector<int> outTime(n,0);//outTime[i] = time when DFS exits node i
        int time=0;
        //dfs start frm root=0,parent=-1 to fill in subtree XORs and Euler tour timings
        dfs(0,-1,subtreeXor,inTime,outTime,time,nums,adj);
        int res=INT_MAX;
        //go for all possible pair of nodes n explore them
        // Try all pairs (u, v) where u, v are nodes != root (0)
        for(int u=1;u<n;u++){
            for(int v=u+1;v<n;v++){
                int xor1; int xor2; int xor3;
                //is u an ancestor of v
                if(isAncestor(u,v,inTime,outTime)){//so get xor of(v) first
                // then u's xor well get frm xor of v w itslef
                    xor1=subtreeXor[v];//xor of v's subtree
                    xor2=subtreeXor[u]^subtreeXor[v];//u's subtree minus v
                    xor3=subtreeXor[0]^xor1^xor2;//3rd component -root^xor(l subtre)^r subtee
                }else if(isAncestor(v,u,inTime,outTime)){//v is ancestor of u 
                    xor1=subtreeXor[u];//xor of u's subtree
                    xor2=subtreeXor[v]^subtreeXor[u];//v's subtree minus u
                    xor3=subtreeXor[0]^xor1^xor2;
                }else{
                    xor1=subtreeXor[u];
                    xor2=subtreeXor[v];
                    xor3=subtreeXor[0]^xor1^xor2;
                }
                //update res w min score
                res=min(res,getScore(xor1,xor2,xor3));
            }
        }
        return res;
    }
};