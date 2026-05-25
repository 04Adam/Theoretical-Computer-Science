#include <bits/stdc++.h>
using namespace std;
const int s = 1e6+2;
int in[s];
int out[s];
vector<int>G[s];
vector<int>Ans;

void dfs(int n){
    while(!G[n].empty()){
        int x = G[n].back();
        G[n].pop_back();
        dfs(x);
    }
    Ans.push_back(n);
}
void clear(int n){
    Ans.clear();
    for(int i = 1;i<=n;i++){
        G[i].clear();
        in[i]=0;
        out[i]=0;
    }
}
int main(){
    ios_base::sync_with_stdio(NULL);
    cin.tie();
    int z;
    cin >> z;
    while(z--){
        int n,m;
        cin >> n >> m;
        int a,b;
        for(int i = 0;i<m;i++){
            cin >> a >> b;
            G[a].push_back(b);
            out[a]++;
            in[b]++;
        }
       // for(int i = 1;i<=n;i++)
       //     reverse(G[i].begin(),G[i].end());
        bool ok=1;
        for(int i = 1;i<=n;i++){
            if(in[i]!=out[i])
                ok=0; 
        }
        for(int i = 1;i<=n;i++){
            if(out[i]!=0){
                dfs(i);
                break;
            }
        }
        if(!ok || Ans.size()!=m+1){
            cout << "NIE\n";
            clear(n);
            continue;
        }
        cout << "TAK ";
        for(int i = Ans.size()-1;i>0;i--)
            cout << Ans[i] << ' ';
        cout << '\n';
        clear(n);
    }
    return 0;
}
