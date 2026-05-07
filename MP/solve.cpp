#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n >> n;
    map<string,int>M;
    string str;
    int num;
    for(int i = 0;i<n;i++){
        string ch;
        cin >> ch;
        if(ch=="INSERT"){
            cin >> str;
            cin >> num;
            M[str]+=num; 
        }
        else if(ch=="FIND"){
            cin >> str;
            if(M.find(str)==M.end())
                cout << 0 << '\n';
            else
                cout << M[str] << '\n'; 
        }
        else{
            cin >> str;
            if(M.find(str)==M.end())
                cout << "ERROR" << '\n';
            else{
                cout << str << ' ' << M[str] << '\n';
                M.erase(str);
            }
        }
    }
    return 0;
}
