#include <bits/stdc++.h>
using namespace std;
const int s = 1e6+2;
int parent[s];
int depth[s];
vector<int>G[s];
bool vis[s];
int p[s]; // starting node in path to root
int len[s]; // length of path to root 
struct Ans{
    int val;
    int node1;
    int node2; 
};
Ans ans = {0,0,0};
void bfs(int n){
    vis[n]=1;
    queue<int>Q;
    Q.push(n);
    while(!Q.empty()){
        n = Q.front();
        Q.pop(); 
        for(auto x:G[n]){
            if(!vis[x]){
                vis[x]=1;
                parent[x]=n;
                Q.push(x);
            }
        }
    }
}
   
void dfs(int n){
    vis[n]=1;
    depth[n] = depth[parent[n]]+1;
    for(auto x:G[n]){
        if(!vis[x])
            dfs(x);
    }
    if(G[n].size()==1){
        p[n] = parent[n];
        if(n==0){
            len[n] = len[parent[n]];
            return;
        }
        len[n] = 1;
    }
    else if(G[n].size()==2&&n!=0){
        if(parent[n]!=G[n].back()){
            p[n] = p[G[n].back()];
            len[n] = len[G[n].back()];
            if(len[n]+1>ans.val)
                ans = {len[n]+1,p[n],n};
        }
        else{
            p[n] = p[G[n][0]];
            len[n] = len[G[n][0]];
            if(len[n]+1>ans.val)
                ans = {len[n]+1,p[n],n};
        }
    }
    else{ // atl two childs
        pair<int,int> max1={0,0};
        for(auto x:G[n]){
            if(parent[n]!=x && max1.first<len[x])
                max1 = {len[x],x};
        }
        pair<int,int> max2={0,0};
        for(auto x:G[n]){
            if(parent[n]!=x && max2.first<len[x] && x!=max1.second)
                max2 = {len[x],x};
        }
        max1.second = p[max1.second];
        max2.second = p[max2.second];
        len[n] = max1.first + G[n].size()-1 - (n!=0); // without parent and x
        p[n] = max1.second;
        int length = max1.first + max2.first + G[n].size()-2; // with parent of n
        if(ans.val<length){
            ans = {length,max1.second,max2.second};
        //    cout << length << ' ' << max1.second << ' ' << max2.second << '\n';
        //    cout << max1.first << ' ' << max2.first << '\n';
        }
    }
}
vector<int>find_path(int a,int b){
    vector<int>path;
    vector<int>fromB;
    if(depth[a]<depth[b])
       swap(a,b); 
    while(depth[a]!=depth[b]){
        path.push_back(a);
        a = parent[a];
    }
    if(a==b){
        path.push_back(a);
        return path;    
    }
    while(a!=b){
        path.push_back(a);
        fromB.push_back(b);
        a = parent[a];
        b = parent[b];
    }
    path.push_back(a);
    while(!fromB.empty()){
        path.push_back(fromB.back());
        fromB.pop_back();
    }
    return path;
}
void clear(int n){
    for(int i=0;i<=n;i++){
        vis[i]=0;
        parent[i]=0;
        len[i]=0;
        p[i]=0;
        depth[i]=0;
        G[i].clear();
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie();
    int t;
    cin >> t;
    while(t--){
        ans = {0,0,0};
        int n;
        cin >> n;
        vector<pair<int,int>>P(n);
        for(int i = 0;i<n;i++){
            int a,b;
            cin >> a >> b;
            P[i] = {a,b};
        }
        /*
        for(int i = 0;i<n;i++){
            if(P[i].first!=-1){
                parent[P[i].first]=i;
                G[i].push_back(P[i].first);
                G[P[i].first].push_back(i);
            }
            if(P[i].second!=-1){
                parent[P[i].second] = parent[i];
                G[parent[i]].push_back(P[i].second);
                G[P[i].second].push_back(parent[i]);
            }
        }
        */
        for(int i = 0; i < n; i++) {
            int child = P[i].first;
            while(child != -1) {
                G[i].push_back(child);
                G[child].push_back(i);
                child = P[child].second;
            }
        }
        /*
        for(int i = 0;i<n;i++){
            cout << i << ": ";
            for(auto x:G[i])
                cout << x << ' ';
            cout << '\n';
        }
        */
        bfs(0);
        for(int i = 0;i<=n;i++)
            vis[i]=0;
        dfs(0);
        if(n==2)
            ans = {1,0,0};
        cout << ans.val<<'\n';// << ' ' << ans.node1 << ' ' << ans.node2<<'\n';
        vector<int>path = find_path(ans.node1,ans.node2);
        cout << path.size() << ' ';
        for(auto x:path)
            cout << x << ' ';
        cout << '\n';
        clear(n);
    }     
    return 0;
}
