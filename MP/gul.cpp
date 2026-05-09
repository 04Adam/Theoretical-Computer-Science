#include <bits/stdc++.h>
using namespace std;
const int s = 1e6+2;
vector<int>G[s];
bool vis[s];
int safeness[s];
int safeness_min[s];
int dis_x[s];
int dis_y[s];
int parent[s];
int parent_x[s];
int parent_y[s];
void bfs_safe(vector<int>V){
    queue<int>Q;
    for(auto x:V){
        vis[x]=1;
        Q.push(x);
    }
    while(!Q.empty()){
        int n = Q.front();
        Q.pop();
        for(auto x:G[n]){
            if(!vis[x]){
                safeness[x]=safeness[n]+1;
                vis[x]=1;
                Q.push(x);
            }
        }
    }
}
void bfs_path(int n){
    vis[n]=1;
    queue<int>Q;
    Q.push(n);
    while(!Q.empty()){
        n=Q.front();
        Q.pop();
        for(auto x:G[n]){
            if(safeness[x]==0)
                continue;
            if(!vis[x]){
                dis_x[x]=dis_x[n]+1;
                safeness_min[x] = min(safeness_min[n],safeness[x]); 
                parent[x]=n;
                vis[x]=1;
                Q.push(x);
            }
            else if(dis_x[x]==dis_x[n]+1){
                if(safeness_min[x]<min(safeness_min[n],safeness[x])){
                    safeness_min[x]=min(safeness_min[n],safeness[x]);
                    parent[x]=n;
                }
            }
        }
    }
         
}
void bfs_final(int n,bool is_x){
    vis[n]=1;
    queue<int>Q;
    Q.push(n);
    while(!Q.empty()){
        n = Q.front();
        Q.pop();
        for(auto x:G[n]){
            if(!vis[x]){
                if(safeness[x]!=0)
                    Q.push(x);
                if(is_x){
                    dis_x[x]=dis_x[n]+1;
                    parent_x[x]=n;
                }
                else{
                    dis_y[x]=dis_y[n]+1;
                    parent_y[x]=n;
                }
                vis[x]=1;
            }
        }
    }
}
void clear_vis(int n){
    for(int i=0;i<=n;i++)
        vis[i]=0;
}
void clear_all(int n){
    for(int i=0;i<=n;i++){
        G[i].clear();
        vis[i]=0;
        parent[i]=0;
        parent_x[i]=0;
        parent_y[i]=0;
        dis_x[i]=0;
        dis_y[i]=0;
        safeness[i]=0;
        safeness_min[i]=0;
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie();
    int z;
    cin >> z;
    while(z--){
        int n,m;
        cin >> n >> m;
        int x,y;
        cin >> x >> y;
        int k;
        cin >> k;
        vector<int>cyf(k);
        for(int i = 0;i<k;i++)
            cin >> cyf[i];
        int a,b;
        for(int i = 0;i<m;i++){
            cin >> a >> b;
            G[a].push_back(b);
            G[b].push_back(a);
        }
        bfs_safe(cyf);
        safeness_min[x]=safeness[x];
        clear_vis(n);
        bfs_path(x);
        if(vis[y]){
            cout << "TAK " << safeness_min[y] << '\n';
            vector<int>path;
            int p = y;
            while(p!=x){
               path.push_back(p);
               p = parent[p]; 
            }
            path.push_back(p);
            reverse(path.begin(),path.end());
            cout << path.size() << ' ';
            for(auto x:path)
                cout << x << ' ';
            cout << '\n';
        }
        else{
           clear_vis(n); 
           bfs_final(x,true);
           clear_vis(n);
           bfs_final(y,false);
           pair<int,int>min_path = {INT_MAX,0};
           for(auto x:cyf){
                if(dis_x[x]>0&&dis_y[x]>0&&dis_x[x]+dis_y[x]<min_path.first)
                    min_path = {dis_x[x]+dis_y[x],x};
           }
           if(min_path.first==INT_MAX){
               cout << "NIE\n";
               clear_all(n);
               continue;
           }
           else
               cout << "TAK 0" << '\n';
           vector<int>path;
           int p = min_path.second;
           while(p!=x){
               path.push_back(p);
               p = parent_x[p];
           }
           path.push_back(p);
           reverse(path.begin(),path.end());
           p = min_path.second;
           while(p!=y){
               p = parent_y[p];
               path.push_back(p);
           }
           cout << path.size() << ' ';
           for(auto x:path)
               cout << x << ' ';
           cout << '\n';
        }
        clear_all(n);
    }
    return 0;
}
