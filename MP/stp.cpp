#include <bits/stdc++.h>
using namespace std;
struct road{
    int v;
    int a;
    int b;
    int id;
};
struct hlp{
    int v;
    int w;
    bool k;
};
const int M = 1<<19;
int tree[M*2];
void insert(int x,int a){
    a += M;
    while(a!=0){
        tree[a]+=x;
        a/=2;
    }
}
void print(int n){
    for(int i = 0;i<=n;i++)
        cout<<tree[i+M] << ' ';
    cout << '\n';
}
int query(int a,int b){
    a+=M;
    b+=M;
    if(a==b)
        return tree[a];
    int ans=tree[a]+tree[b];
    while(a/2!=b/2){
        if(a%2==0)
            ans+=tree[a+1];
        if(b%2==1)
            ans+=tree[b-1];
        a/=2;
        b/=2;
    }
    return ans;
}
bool comp(road&a,road&b){
    if(a.v<b.v)
        return true;
    return false;
}
bool comp1(hlp&a,hlp&b){
    return a.v < b.v;
}
const int s = 1e5+2;
int ans[s];
void solve(vector<hlp>&po, vector<road>&ar,int m){
    for(int i=1;i<=m;i++){
        vector<int>V;
        while(!po.empty()&&po.back().v==i){
            // add beginnings
            if(po.back().k==0){
            //  cout << "adding\n";
                insert(1,po.back().w);
             // print(m);
            }
            else // save ends
                V.push_back(po.back().w);
            po.pop_back();
        }
        while(ar.back().v==i){
            ans[ar.back().id]=query(ar.back().a,ar.back().b);
            ar.pop_back();
        }
        
        // add ends
        for(auto x:V){
        //  cout << (V.empty()?"":"deleting\n");
            insert(-1,x);
         // print(m);
        }
        V.clear();
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
        vector<hlp>we;
        vector<hlp>sn;
        vector<road>ver;
        vector<road>hor;
        for(int i = 0;i<n;i++){
            int x1,y1,x2,y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if(x1==x2){
                int b = y1;
                y1 = min(y1,y2);
                y2 = max(b,y2);
                sn.push_back({y1,x1,0});
                sn.push_back({y2,x1,1});
                ver.push_back({x1,y1,y2,i});
            }
            else if(y1==y2){
                int b = x1;
                x1 = min(x1,x2);
                x2 = max(x2,b);
                we.push_back({x1,y1,0});
                we.push_back({x2,y1,1});
                hor.push_back({y1,x1,x2,i});
            }
        }
        sort(sn.begin(),sn.end(),comp1);
        sort(we.begin(),we.end(),comp1);
        sort(hor.begin(),hor.end(),comp);
        sort(ver.begin(),ver.end(),comp);
        reverse(sn.begin(),sn.end());
        reverse(we.begin(),we.end());
        reverse(hor.begin(),hor.end());
        reverse(ver.begin(),ver.end());
        // WEST -> EAST
        solve(we,ver,m);
        // SOUTH -> NORTH
        solve(sn,hor,m);
        for(int i = 0;i<n;i++)
            cout << ans[i] << '\n';
    }     return 0;
}
