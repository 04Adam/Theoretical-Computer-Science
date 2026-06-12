#include <bits/stdc++.h>
using namespace std;
mt19937 rng(1337);
pair<int, int> lomuto(vector<int>& tab, int l, int r) {
    uniform_int_distribution<int> dist(l, r);
    swap(tab[dist(rng)], tab[r]);
    int pivot = tab[r];
    int i = l;
    int p = l;
    int q = r;

    while (i <= q) {
        if (tab[i] < pivot) {
            swap(tab[p], tab[i]);
            p++;
            i++;
        } else if (tab[i] > pivot) {
            swap(tab[i], tab[q]);
            q--;
        } else {
            i++;
        }
    }
    return {p, q};
}
void quick_sort(vector<int>&tab,int l,int r){
    if(l>=r)
        return;
    pair<int,int> ind = lomuto(tab,l,r);
    quick_sort(tab,l,ind.first-1);
    quick_sort(tab,ind.second+1,r);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie();
    int z;
    cin >> z;
    while(z--){
        int n;
        cin >> n;
        vector<int> tab1(n);
        vector<int> tab2(n);
        for(int i = 0;i<n;i++)
            cin>> tab1[i];
        for(int i = 0;i<n;i++)
            cin>> tab2[i];
        quick_sort(tab1,0,n-1);
        quick_sort(tab2,0,n-1);
        for(auto x:tab1)
            cout << x << ' ';
        cout << '\n';
        for(auto x:tab2)
            cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
