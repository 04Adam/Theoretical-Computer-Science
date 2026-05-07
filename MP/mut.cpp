#include <bits/stdc++.h>
using namespace std;
vector<int>Hash(string str,long long P=31,int M=1e9+9){
    long long ans=0;
    long long base=1;
    vector<int>vec;
    for(auto x:str){
        ans+=base*x;
        base*=P;
        ans%=M;
        base%=M;
        vec.push_back(ans);
    }
    return vec;
}
bool check(int mid,vector<int>&v1,vector<int>&v2,int l,int M=1e9+9){
    if((M+v1[mid]-v1[l+1])%M==(M+v2[mid]-v2[l+1])%M)
        return true;
    return false;
}
int judge(vector<int>&v1,vector<int>&v2){
    if(v1.size()!=v2.size())
        return -1;
    if(v1.back()==v2.back())
        return 0;
    int l=0;
    int p=v1.size()-1;
    while(l<p){
        int mid=(l+p)/2;
        if(v1[mid]!=v2[mid])
            p=mid;
        else
            l=mid+1;
    }
    l--;
    if(((int)1e9+9+v1.back()-v1[l+1])%((int)1e9+9)==((int)1e9+9+v2.back()-v2[l+1])%(int)(1e9+9))
        return 1;
    int l1=l+2;
    int p1=v1.size()-1;
    while(l1<p1){
        int mid=(p1+l1)/2;
        if(check(mid,v1,v2,l))
            l1=mid+1;
        else
            p1=mid;
    }
    l1--;
    if((((int)1e9+9+v1.back()-v1[l1+1])%((int)1e9+9)==((int)1e9+9+v2.back()-v2[l1+1])%(int)(1e9+9)))
        return 2;
    return -1;
}
int main(){
    int z;
    cin >> z;
    while(z--){
        int n,k,m;
        cin >> n >> k;
        vector<vector<int>>hashes;
        string str;
        for(int i = 0;i<n;i++){
            cin >> str;
            hashes.push_back(Hash(str));
        } 
        cin >> m;
        for(int i = 0;i<m;i++){
            cin >> str;
            int same=0;
            int diff1=0;
            int diff2=0; 
            vector<int>hash_str = Hash(str);
            for(auto &v:hashes){
                int res=judge(hash_str,v);
                if(res==0)
                    same++;
                else if(res==1)
                    diff1++;
                else if(res==2)
                    diff2++;
            }
            cout << same << ' ' << diff1 << ' ' << diff2 << '\n';
            if (same == 0 && diff1 == 0 && diff2 == 0)
                hashes.push_back(hash_str);
        } 
    }
    return 0;
}
