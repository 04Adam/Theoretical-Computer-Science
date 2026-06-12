#include <bits/stdc++.h>
using namespace std;
inline int get_median(vector<int>&tab,int l,int r){
    if(l==r)
        return tab[l];
    sort(tab.begin()+l,tab.begin()+r+1);
    return tab[l+(r-l)/2];
}
int k_th(vector<int>&V,int l,int r,int k){
    if(l==r)
        return V[l];
    int n=r-l+1;
    vector<int>med;
    med.reserve(n/5+1);
    for(int i=0;i<n;i+=5){
        int sub_r=min(l+i+4,r);
        med.push_back(get_median(V,l+i,sub_r));
    }
    int piv;
    if(med.size()==1)
        piv=med[0];
    else
        piv=k_th(med,0,med.size()-1,med.size()/2);
    int lt=l,i=l,gt=r;
    while(i<=gt){
        if(V[i]<piv){
            swap(V[i],V[lt]);
            lt++;
            i++;
        }
        else if(V[i]>piv){
            swap(V[i],V[gt]);
            gt--;
        }
        else
            i++;
    }
    if(k>=lt&&k<=gt)
        return piv;
    else if(k<lt)
        return k_th(V,l,lt-1,k);
    else
        return k_th(V,gt+1,r,k);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int z;
    cin >> z;
        
    while(z--){ 
        int n,k;
        cin>>n>>k;
        vector<int>tab(n);
        for(int i=0;i<n;i++)
            cin>>tab[i];
        cout<<k_th(tab,0,n-1,k-1)<<'\n';
        }
    return 0; 
}
