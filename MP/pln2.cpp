#include <bits/stdc++.h>
using namespace std;
const int s=1e6+2;
int sem[s];
int in[s];
int vis[s];   // 0 - not vis, 1 - on stack, 2 - vis
bool cycle=0;
vector<int>spec;

bool dfs(vector<list<int>>&G,int n){
    vis[n]=1;
    for(auto x:G[n]){
        if(vis[x]==1){
            cycle=1;
            return false;
        }
        if(vis[x]==0)
            if(!dfs(G,x))
                return false;
    }
    vis[n]=2;
    spec.push_back(n);
    return true;
}

void clear(int n){
    spec.clear();
    for(int i=1;i<=n;i++){
        sem[i]=0;
        in[i]=0;
        vis[i]=0;
    }
    cycle=0;
}

int main(){
    int z;
    cin >> z;
    while(z--){
        int n,m;
        cin >> n >> m;
        vector<list<int>>G(n+1);
        int a,b;
        for(int i=0;i<m;i++){
            char ch;
            cin >> a >> ch >> b;
            G[a].push_back(b);
            in[b]++;
        }
        for(int i=1;i<=n&&!cycle;i++)
            if(vis[i]==0)
                dfs(G,i);
        if(cycle){
            cout << "NIE\n";
            clear(n);
            continue;
        }
        for(int i=spec.size()-1;i>=0;i--){
            int u=spec[i];
            for(auto v:G[u])
                sem[v]=max(sem[v],sem[u]+1);
        }
        vector<vector<int>>sorted(n);
        int Max=0;
        for(int i=1;i<=n;i++){
            sorted[sem[i]].push_back(i);
            Max=max(Max,sem[i]);
        }
        cout << "TAK " << Max+1 << '\n';
        for(int i=0;i<=Max;i++){
            cout << sorted[i].size();
            for(auto x:sorted[i])
                cout << ' ' << x;
            cout << '\n';
        }
        clear(n);
    }
    return 0;
}
