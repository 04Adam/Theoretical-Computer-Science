#include <bits/stdc++.h>
using namespace std;
const int s = 1e6+2;
int in[s];
int out[s];
int pre[s];
int nxt[s];
int U[s];
int V[s];
bool vis[s];

struct edge{
    int target;
    vector<int>vert;
};

vector<edge>G[s];
vector<int>Ans;
unordered_map<long long, int> edge_id;

void dfs(int n){
    while(!G[n].empty()){
        edge ed = G[n].back();
        G[n].pop_back();
        dfs(ed.target);
        for(int i = ed.vert.size()-1;i>=0;i--){
            Ans.push_back(ed.vert[i]);
        }
    }
    Ans.push_back(n);
}

void clear(int n, int m){
    Ans.clear();
    edge_id.clear();
    for(int i = 1;i<=n;i++){
        G[i].clear();
        in[i]=0;
        out[i]=0;
    }
    for(int i = 1;i<=m;i++){
        pre[i]=0;
        nxt[i]=0;
        vis[i]=0;
        U[i]=0;
        V[i]=0;
    }
}

int main(){
    ios_base::sync_with_stdio(NULL);
    cin.tie(NULL);
    int z;
    cin >> z;
    while(z--){
        int n,m;
        cin >> n >> m;
        int a,b;
        for(int i = 1;i<=m;i++){
            cin >> a >> b;
            U[i] = a;
            V[i] = b;
            out[a]++;
            in[b]++;
            long long hash = 1LL * a * s + b;
            edge_id[hash] = i;
        }
        
        int k;
        cin >> k;
        bool ok=1;
        
        for(int i = 0;i<k;i++){
            int d;
            cin >> d;
            vector<int> seq(d);
            for(int j = 0;j<d;j++) 
                cin >> seq[j];
            
            vector<int> seq_edges;
            for(int j = 0;j<d-1;j++){
                long long hash = 1LL * seq[j] * s + seq[j+1];
                int e = edge_id[hash];
                if(e==0) ok=0;
                seq_edges.push_back(e);
            }
            
            if(!ok) continue;
            
            for(int j = 0;j<(int)seq_edges.size()-1;j++){
                int e1 = seq_edges[j];
                int e2 = seq_edges[j+1];
                
                if(nxt[e1]!=0 && nxt[e1]!=e2) ok=0;
                if(pre[e2]!=0 && pre[e2]!=e1) ok=0;
                
                nxt[e1] = e2;
                pre[e2] = e1;
            }
        }
        
        for(int i = 1;i<=n;i++){
            if(in[i]!=out[i])
                ok=0; 
        }
        
        if(ok){
            for(int i = 1;i<=m;i++){
                if(pre[i]==0){
                    int ptr = i;
                    vis[ptr]=1;
                    edge ed;
                    int start_node = U[ptr];
                    int current_end = V[ptr];
                    
                    while(nxt[ptr]!=0){
                        ptr = nxt[ptr];
                        if(vis[ptr]){ ok=0; break; }
                        vis[ptr]=1;
                        ed.vert.push_back(current_end);
                        current_end = V[ptr];
                    }
                    ed.target = current_end;
                    G[start_node].push_back(ed);
                }
            }
            
            for(int i = 1;i<=m;i++){
                if(!vis[i] && ok){
                    int ptr = i;
                    vis[ptr]=1;
                    edge ed;
                    int start_node = U[ptr];
                    int current_end = V[ptr];
                    
                    while(nxt[ptr]!=0 && nxt[ptr]!=i){
                        ptr = nxt[ptr];
                        if(vis[ptr]){ ok=0; break; }
                        vis[ptr]=1;
                        ed.vert.push_back(current_end);
                        current_end = V[ptr];
                    }
                    ed.target = current_end;
                    G[start_node].push_back(ed);
                }
            }
        }
        
        if(!ok){
            cout << "NIE\n";
            clear(n,m);
            continue;
        }
        int start_node = 1;
        for(int i = 1;i<=n;i++){
            if(!G[i].empty()){
                start_node = i;
                break;
            }
        } 
        dfs(start_node);
        
        if(Ans.size()!=m+1){
            cout << "NIE\n";
        } else {
            cout << "TAK ";
            for(int i = Ans.size()-1;i>0;i--)
                cout << Ans[i] << ' ';
            cout << '\n';
        }
        clear(n,m);
    }
    return 0;
}
