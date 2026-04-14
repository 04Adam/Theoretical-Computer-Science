#include <bits/stdc++.h>
using namespace std;
const int s = 2002;
int ans=0;
int tab[s][s];
bool vis[s][s];
void dfs(int i,int j,int mid,int k){
    ans++;
    if(ans>=k)
        return;
    vis[i][j]=1;
    if(!vis[i+1][j]&&tab[i+1][j]<=mid)
        dfs(i+1,j,mid,k);
    if(!vis[i-1][j]&&tab[i-1][j]<=mid)
        dfs(i-1,j,mid,k);
    if(!vis[i][j+1]&&tab[i][j+1]<=mid)
        dfs(i,j+1,mid,k);
    if(!vis[i][j-1]&&tab[i][j-1]<=mid)
        dfs(i,j-1,mid,k);
}
bool fun(int mid,int k,int n,int m){
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            if(vis[i][j]==0&&tab[i][j]<=mid){
                ans = 0;
                dfs(i,j,mid,k);
                //cout <<  i << ' ' << j << ' ' << ans << '\n';
                if(ans>=k)
                    return true;
            }
        }
    }
    return false;
}
void clean(int n,int m){
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++)
            vis[i][j]=0;
    }
}
int main(){
    ios_base::sync_with_stdio(NULL);
    cin.tie();
    int z;
    cin >> z;
    while(z--){
        int n,m,k;
        cin >> n >> m >> k;
        for(int i = 0;i<=n+1;i++){
            for(int j=0;j<=m+1;j++)
                tab[i][j]=INT_MAX;
        }
        int Min = INT_MAX;
        int Max = -1;
        for(int i =1 ;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin >> tab[i][j]; 
                Min = min(Min,tab[i][j]);
                Max = max(Max,tab[i][j]);
            }
        }
        if(k>n*m){
            cout << 0 << '\n';
            continue;
        }
        while(Max>Min){
            int mid = (Max+Min)/2;
            if(fun(mid,k,n,m))
               Max = mid;
            else 
               Min = mid+1;
            clean(n,m);
        }
        cout << Min << '\n';
    }
    return 0;
}
