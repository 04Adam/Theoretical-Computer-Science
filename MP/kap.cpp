#include <bits/stdc++.h>
using namespace std;
long long merge_and_count(vector<int>& arr, vector<int>& temp, int left, int mid, int right, int k) {
    long long errors = 0;

    int p = mid + 1;
    for (int i = left; i <= mid; ++i) {
        while (p <= right && (long long)arr[i] + k < arr[p]) {
            p++;
        }
        errors += (p - (mid + 1));
    }

    int i = left;
    int j = mid + 1;
    int index = left;

    while (i <= mid && j <= right) {
        if (arr[i] >= arr[j]) {
            temp[index++] = arr[i++];
        } else {
            temp[index++] = arr[j++];
        }
    }
    while (i <= mid) {
        temp[index++] = arr[i++];
    }
    while (j <= right) {
        temp[index++] = arr[j++];
    }

    for (int i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return errors;
}

long long merge_sort(vector<int>& arr, vector<int>& temp, int left, int right, int k) {
    long long errors = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;

        errors += merge_sort(arr, temp, left, mid, k);
        errors += merge_sort(arr, temp, mid + 1, right, k);
        errors += merge_and_count(arr, temp, left, mid, right, k);
    }
    return errors;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie();
    int z;
    cin >> z;
    while(z--){
        int n,k;
        cin  >> n >> k;
        vector<int>tab(n);
        for(int i = 0;i<n;i++)
            cin >> tab[i];
        vector<int>temp(n);
        long long c = merge_sort(tab,temp,0,n-1,k);
        for(auto x:tab)
            cout << x << ' ';
        cout << '\n';
        cout << c << '\n';
    }
    return 0;
}
