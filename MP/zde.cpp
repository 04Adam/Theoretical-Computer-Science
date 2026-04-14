#include <bits/stdc++.h>
using namespace std;
void push(deque<pair<int,int>>&Q,int x){
    int num=0;
    while(!Q.empty()&&Q.back().second>x){
        num+=Q.back().first+1;
        Q.pop_back();
    }
    Q.push_back({num,x});
}
void pop(deque<pair<int,int>>&Q){
    if(Q.empty())
        return;
    if(Q.front().first==0)
        Q.pop_front();
    else
        Q.front().first--;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie();
    int z;
    cin >> z;
    while(z--){
        int n,k;
        cin >> n >> k;
        if(n==1){
            int a;
            cin >> a;
            cout << a << ' ' << 0 << ' ' <<0 <<  '\n';
            continue;
        }

        deque<pair<int,int>>Q;
        int a;
        int size=0;
        pair<int,int>ind={-1,-1};
        int ans=INT_MAX;
        for(int i = 0;i<n;i++){
            cin >> a;
            if(size<k){
                if(Q.empty()){
                    push(Q,a);
                    size++;
                    continue;
                }
                if(ans>Q.front().second+a){
                    ans=Q.front().second+a;
                    ind = {Q.front().first,i};
                }
                push(Q,a);
                size++;
            }
            else{
                if(ans>Q.front().second+a){
                    ans=Q.front().second+a;
                    ind = {i-k+Q.front().first,i};
                }
                pop(Q);
                push(Q,a);
                
            }
        }
        cout << ans << ' ' << ind.first << ' ' << ind.second << '\n';
    }
    return 0;    
}
