#include <bits/stdc++.h>
using namespace std;
const int s=1e6+2;
int sem[s];
int in[s];
bool vis[s];
void bfs(vector<list<int>>&G,int N){
    queue<int>Q;
    for(int i = 1;i<=N;i++){
        if(in[i]==0)
            Q.push(i);
    }
    while(!Q.empty()){
        int n = Q.front();
        Q.pop();
        vis[n]=1;
        for(auto x:G[n]){
            in[x]--;
            if(in[x]==0){
                Q.push(x);
                sem[x] = sem[n]+1;
            }
        }
    }
}
void clear(int n){
    for(int i = 1;i<=n;i++){
        sem[i]=0;
        in[i]=0;
        vis[i]=0;
    }
}
int main(){
    int z;
    cin >> z;
    while(z--){
        int n,m;
        cin >> n >> m;
        vector<list<int>>G(n+1);
        int a,b;
        for(int i = 0;i<m;i++){
           char ch;
           cin >> a >> ch >> b;
           G[a].push_back(b);
           in[b]++;
        }
        bfs(G,n);
        bool k=1;
        for(int i = 1;i<=n;i++){
            if(!vis[i])
                k=0;
        }
        if(!k){
            cout << "NIE\n";
            clear(n);
            continue;
        }
        
        vector<vector<int>>sorted(n);
        int Max=0;
        for(int i = 1;i<=n;i++){
           sorted[sem[i]].push_back(i); 
           Max = max(Max,sem[i]);
        }
        cout << "TAK " << Max+1 << '\n';
        for(auto v:sorted){
            if(!v.empty())
                cout << v.size() << ' ';
            for(auto x:v)
                cout << x << ' ';
            if(!v.empty())
                cout << '\n';
        }
        clear(n);
    }
    return 0;
}
