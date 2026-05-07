#include <bits/stdc++.h>
using namespace std;
int main(){
    srand(time(NULL));
    int n=rand()%10+4;
    cout << 1<<' '<< n << '\n';
    vector<string>V;
    for(int i = 0;i<n;i++){
        int ch=rand()%3;
        if(ch==0){
            string str="";
            int num=rand()%10;
            for(int j=0;j<8;j++)
                str+='A'+int(rand())%26;
            cout << "INSERT " << str << ' ' << num << '\n';
            V.push_back(str);
        }
        else if(ch==1){
            string str="";
            for(int j=0;j<8;j++)
                str+='A'+int(rand())%26;
            cout << "FIND " << str << '\n';
        }
        else{
            string str="00000000";
            if(rand()%2==0&&V.size()>0)
                str = V[rand()%V.size()];
            cout << "DELETE " << str << '\n';
        }
    }
    return 0;
}
