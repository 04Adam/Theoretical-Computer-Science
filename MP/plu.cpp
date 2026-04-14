#include <bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie();
    int z;
    cin >> z;
    while(z--){
        int n,r;
        cin >> n >> r;
        int left[n+1]={0};
        int right[n+1]={0};
        for(int i = 1;i<=n;i++){
            cin >> left[i];
            cin >> right[i];
        }
        int p = r;
        int q = -1;
        int prev = 0;
        while(p!=-1){
            if(p == 0){
                p = q;
                q = 0;
            }
            else{
                if(prev != p)
                    cout << p << ' ';
                prev = p; 
                int tmp = left[p];
                left[p] = right[p];
                right[p] = q;
                q = p;
                p = tmp;
            }
        }
        cout << '\n';
    }
    return 0;
}

