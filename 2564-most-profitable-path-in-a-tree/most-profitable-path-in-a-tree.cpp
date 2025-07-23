class Solution {
public:
            //  TC - O(N) & SC - O(N)

int ans = INT_MIN;               // contain answer
unordered_map<int, int> mp;      // node -> distance

bool pathTileZero(int bob, int cnt, unordered_map<int, vector<int>> &adjList,
vector<int> &visitedB){
    visitedB[bob] = 1;
    if(bob == 0){
        mp[bob] = cnt;
        return 1;
    }

    for(auto pa:adjList[bob]){
        if(!visitedB[pa]){
            bool flag = pathTileZero(pa, cnt+1, adjList, visitedB);
            if(flag){
                mp[pa] = cnt;
                return 1;
            }
        }
    }
    return 0;
}


void solve( int alice, int cnt, int sum, unordered_map<int, vector<int>> &adjList,
vector<int> &visitedA, vector<int>& amount){

    visitedA[alice] = 1;
    cnt++;
    
    if(adjList[alice].size() == 1 && alice != 0){
        ans = max(ans, sum);
        return;
    }

    for(auto pa:adjList[alice]){
        if(!visitedA[pa]){
            int addedVal = 0;
            
        // if Node come in the path of bob to 0 then we have 3 case
        // case 1 : mp[pa] > cnt i.e. bob not visited yet.
        // case 2 : mp[pa] < cnt i.e. bob already visited so add 0.
        // case 3 : mp[pa] == cnt i.e. bob and alice visited together
            if(mp.find(pa) != mp.end()){  
                if(mp[pa] == cnt)
                addedVal = amount[pa] / 2;
                if(mp[pa] > cnt)
                addedVal = amount[pa];
            }
            else  // node not occur in bob to 0 path.
            addedVal = amount[pa];
            
            solve(pa, cnt, sum + addedVal, adjList, visitedA, amount);
        }
    }
}

    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        int size = edges.size() + 1; // no. of node
        unordered_map<int, vector<int>> adjList; 

        for(int i=0 ;i<edges.size() ;i++){
            int u = edges[i][0];
            int v = edges[i][1];
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        vector<int> visitedA(size, 0), visitedB(size, 0);

        pathTileZero(bob, 1, adjList, visitedB); // Find the path from bob to 0 and insert into map as node -> no. of step need to reach at particular node
        mp[bob] = 0;

        solve(0, 0, amount[0], adjList, visitedA, amount);
        
        return ans;
    }
};