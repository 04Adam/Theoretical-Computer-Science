#include <bits/stdc++.h>
using namespace std;
vector<int>heap;
void add(int x){
    heap.push_back(x);
    int in = heap.size()-1;
    while(heap[in]<heap[(in-1)/2]){
        swap(heap[in],heap[(in-1)/2]);
        in=(in-1)/2;
    }
}
void rem(){
    if(heap.empty())
        return;
    int in = heap.size()-1;
    swap(heap[0], heap[in]);
    heap.pop_back();
    in = 0;
    int n = heap.size();
    while(true){
        int left = in * 2 + 1;
        int right = in * 2 + 2;
        int smallest = in;
        if(left < n && heap[left] < heap[smallest])
            smallest = left;
        if(right < n && heap[right] < heap[smallest])
            smallest = right;
        if(smallest != in){
            swap(heap[in], heap[smallest]);
            in = smallest;
        }
        else 
            break;
    }
}
bool mov(){
    if(heap.empty())
        return false;
    heap[0]--;
    if(heap[0]==0){
        rem();
        return true;
    }
    return false;
}
int main(){
    ios_base::sync_with_stdio(NULL);
    cin.tie();
    int z;
    cin >> z;
    while(z--){
        int n,a,b;
        cin >> n;
        vector<pair<int,int>>tab(n);
        for(int i = 0;i<n;i++){
            cin >> a >> b;
            tab[i] = {a,b};
        }
        sort(tab.begin(),tab.end());
        int h = tab.back().first;
        int ans=0;
        while(h>0){
            while(!tab.empty()&&tab.back().first==h){
                add(tab.back().second);
                tab.pop_back();
            }
         //   cout << h << ": " << heap[0] << '\n';
            if(mov())
                ans++;
            h--;
        }
        cout << ans << '\n';
        heap.clear();
    }
    return 0;
}
