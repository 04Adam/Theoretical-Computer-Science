#include <bits/stdc++.h>
using namespace std;

const int s = 1e6+2;
vector<int>G[s];
bool vis[s];
vector<int> paths;

void clear(int n){
    for(int i = 0;i<=n;i++){
       G[i].clear();
       vis[i]=0;
    }
    paths.clear();
}

int bfs(int start, int n){
    for(int i = 0;i<=n;i++)
        vis[i]=0;
    queue<int>Q;
    Q.push(start);
    vis[start]=1;
    int furthest = start;
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        furthest = u;
        for(auto x:G[u]){
            if(!vis[x]){
                vis[x]=1;
                Q.push(x);
            }
        }
    }
    return furthest;
}

int dfs(int u, int p){
    vector<int> child_heights;
    for(auto x:G[u]){
        if(x != p){
            child_heights.push_back(dfs(x, u));
        }
    }
    if(child_heights.empty())
        return 1;
    sort(child_heights.rbegin(), child_heights.rend());
    for(int i = 1; i < child_heights.size(); i++){
        paths.push_back(child_heights[i]);
    }
    return child_heights[0] + 1;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int t;
    if(cin >> t){
        while(t--){
            int n,k;
            cin >> n >> k;
            int a,b;
            for(int i = 1;i<n;i++){
                cin >> a >> b;
                G[a].push_back(b);
                G[b].push_back(a);
            }
            int root = bfs(1, n);
            int longest_main_path = dfs(root, 0);
            paths.push_back(longest_main_path);
            
            sort(paths.rbegin(), paths.rend());
            
            long long ans = 0;
            int limit = min((int)paths.size(), 2 * k - 1);
            for(int i = 0; i < limit; i++){
                ans += paths[i];
            }
            
            cout << ans << '\n';
            clear(n);
        }
    }
    return 0;
}
