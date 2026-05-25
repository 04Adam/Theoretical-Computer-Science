#include <bits/stdc++.h>
using namespace std;

const int s = 2e5+20; 
vector<int>G[s];
vector<int>Gr[s];
vector<vector<int>>SCC;
bool vis[s];

void dfs_ord(int n, stack<int>&ord){
    vis[n] = 1;
    for(auto x : G[n]){
        if(!vis[x])
            dfs_ord(x, ord);
    }
    ord.push(n);
}

void dfs(int n, vector<int>&C){
    vis[n] = 1;
    C.push_back(n);
    for(auto x : Gr[n]){
        if(!vis[x])
            dfs(x, C);
    }
}

void clear_vis(int n){
    for(int i = 1; i <= 2*n; i++)
        vis[i] = 0;
}

void clear_all(int n){
    clear_vis(n);
    SCC.clear();
    for(int i = 1; i <= n*2; i++){
        G[i].clear();
        Gr[i].clear();
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int z;
    cin >> z; 
    while(z--){
        int n, m;
        cin >> n >> m;
        int a, b;
        bool is_special; 
        
        for(int i = 0; i < m; i++){
            cin >> a >> b >> is_special;
            if(is_special){
                G[a].push_back(b+n);
                G[b+n].push_back(a);
                Gr[a].push_back(b+n);
                Gr[b+n].push_back(a);
            }
            else{
                G[a].push_back(b);
                G[b+n].push_back(a+n);
                Gr[b].push_back(a);
                Gr[a+n].push_back(b+n);
            }
        }
        
        stack<int> ord;
        for(int i = 1; i <= n*2; i++){
            if(!vis[i])
                dfs_ord(i, ord);
        }
        
        
        clear_vis(n);
        while(!ord.empty()){
            int x = ord.top();
            ord.pop();
            vector<int> C;
            if(!vis[x])
                dfs(x, C);
            if(!C.empty())
                SCC.push_back(C);
        }
        
        vector<int> SCC_org_nodes(SCC.size());
        vector<int> which_SCC(2*n + 1); 
        
        clear_vis(n);
        for(int i = 0; i < SCC.size(); i++){
            for(auto x : SCC[i]){
                which_SCC[x] = i;
                vis[x] = 1;
                if(x <= n && !vis[x+n])
                    SCC_org_nodes[i]++;
                if(x > n && !vis[x-n])
                    SCC_org_nodes[i]++;
            }
            for(auto x : SCC[i])
                vis[x] = 0;
        }
        
        for(int i = 1; i <= n; i++)
            cout << SCC_org_nodes[which_SCC[n+i]] - 1 << ' ';
        cout << '\n';

        clear_all(n); 
    }
    return 0;
}
