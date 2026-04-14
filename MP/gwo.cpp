#include <bits/stdc++.h>
using namespace std;
inline bool fun(vector<pair<int,int>>&tab,vector<int>&gwo,int mid,int Max){
    vector<int>V(Max+1,0);
    for(int i = 0;i<=mid;i++)
        V[gwo[i]]=1;
//    cout << '\n';
//    for(auto x:V)
//        cout << x << ' ';
//    cout << '\n';
    for(int i = 1;i<V.size();i++)
        V[i] = V[i-1]+V[i];
    vector<int>ok(tab.size(),0);
    for(int i = 0;i<tab.size();i++){
        if(V[tab[i].first-1]!=V[tab[i].second])
            ok[i]=1;
        else
            return false;

    } 
    return true;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int z;
    cin >> z;
    while(z--){
        int n,m;
        cin >> n >> m;
        vector<pair<int,int>>tab;
        int Max = -1;
        for(int i = 0;i<n;i++){
            int a,b;
            cin >> a >> b;
            Max = max(Max,b);
            tab.push_back({a,b}); 
        }
        vector<int>gwo(m);
        for(int i = 0;i<m;i++){
            cin >> gwo[i];
            Max = max(Max,gwo[i]);
        }
        int p=m-1;
        int l=0;
        if(fun(tab,gwo,gwo.size()-1,Max)==0)
            cout << "ERROR\n";
        else{
            while(l<p){
                int mid = (p+l)/2;
                if(fun(tab,gwo,mid,Max)) // ok
                    p = mid;
                else
                    l = mid+1;
            }
            cout << l+1 << '\n';
        }
    }
    return 0;
}
