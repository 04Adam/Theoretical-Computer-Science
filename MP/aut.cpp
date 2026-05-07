#include <bits/stdc++.h>
using namespace std;
const int s = 1e4*5+2;
vector<pair<int,bool>>G[s];
bool vis[s];
bool changed[s];
void change(int n){
    changed[n]=1;
    for(auto& x:G[n])
        x.second=!x.second;
}
void print(int n){
    for(int i = 1;i<=n;i++){
        cout << i << '\n';
        for(auto x:G[i])
            cout << x.first << ' ' << x.second << '\n';
    }

}
void clean(int n){
   for(int i = 1;i<=n;i++){
       vis[i]=0;
       changed[i]=0;
       G[i].clear();
   }

}
void bfs(int n,vector<int>&Ans){
    vis[n]=1;
    queue<int>Q;
    Q.push(n);
    while(!Q.empty()){
        n = Q.front();
        Q.pop();
        for(auto &x:G[n]){
            if(vis[x.first] && changed[x.first])
                x.second=!x.second;
            if(vis[x.first]==0){
                vis[x.first]=1;
                if(x.second==0){
                    x.second=!x.second;
                    Ans.push_back(x.first);
                    change(x.first);
                }
                Q.push(x.first);
            }
        }
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();
    int z;
    cin >> z;
    while(z--){
        int n,m;
        cin >> n >> m;
        int a,b;
        char c;
        for(int i = 0;i<m;i++){
            cin >> a >> b >> c;
            if(c=='+'){
                G[a].push_back({b,1});
                G[b].push_back({a,1});
            }
            else{
                G[a].push_back({b,0});
                G[b].push_back({a,0});
            }
        }
        vector<int>Ans;
        bfs(1,Ans);
        bool k=1;
      //  print(n);
        for(int i = 1;i<=n;i++){
            for(auto x:G[i])
                if(x.second==0)
                    k=0;
        }
        if(k==0)
            cout << "NIE\n";
        else{
            sort(Ans.begin(),Ans.end());
            for(auto x:Ans)
                cout << x << ' ';
            cout << '\n';
        }
        clean(n);
    }
    return 0;
}
