#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int s = 1e6+2;
ll dis[s];
vector<pair<int,int>>G[s];
bool vis[s];
void radix_sort_256(vector<ll>& V) {
    int n = V.size();
    if (n <= 1) return;
    
    vector<ll> temp(n);
    for (int i = 0; i < 8; i++) {
        int count[256] = {0};
        for (int j = 0; j < n; j++) {
            int b = (V[j] >> (8 * i)) & 255;
            count[b]++;
        }
        for (int j = 1; j < 256; j++) 
            count[j] += count[j - 1];

        for (int j = n - 1; j >= 0; j--) {
            int b = (V[j] >> (8 * i)) & 255;
            temp[count[b] - 1] = V[j];
            count[b]--;
        }
        for (int j = 0; j < n; j++) 
            V[j] = temp[j];
    }
}
void bfs(int n){
    queue<int>Q;
    Q.push(n);
    vis[n]=1;
    while(!Q.empty()){
        n = Q.front();
        Q.pop();
        for(auto &p:G[n]){
            if(!vis[p.first]){
                Q.push(p.first);
                vis[p.first]=1;
                dis[p.first]=dis[n]+p.second;
            }
        }
    }
}
void clear(int n){
    for(int i=0;i<=n;i++){
        G[i].clear();
        vis[i]=0;
        dis[i]=0;
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int z;
    cin >> z;
    while(z--){
        int t,n;
        cin >> t >> n;
        int a,b,c;
        for(int i = 0;i<n-1;i++){
            cin >> a >> b >> c;
            G[a].push_back({b,c}); 
            G[b].push_back({a,c});
        }
        bfs(0);
        vector<ll>V(t);
        vector<ll>V2;
        for(int i = 1;i<=t;i++)
            V[i-1]=dis[i];
        radix_sort_256(V);
        for(ll& x:V)
            cout << x++ << ' ';
        cout << '\n';
        for(int i = 0;i<t;i++){
            if(i!=0&&V[i]<=V[i-1])
                V[i]=V[i-1]+1;
        }
        for(int i = t+1;i<=2*t;i++)
            V2.push_back(dis[i]);
        radix_sort_256(V2);
        for(ll& x:V2)
            cout << x << ' ';
        cout << '\n';
        ll ans = 0;
        for(int i = 0;i<t;i++){
            ans = max(ans,V[i]+V2[t-i-1]);
        }
        cout << ans << '\n';
        clear(n);
    }
    return 0;
}
