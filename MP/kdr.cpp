#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
int A[MAXN], B[MAXN];

int* pre_arr = nullptr;
int* in_arr = nullptr;
int* post_arr = nullptr;

struct Node {
    int val;
    int idx;
    bool operator<(const Node& other) const {
        return val < other.val;
    }
};
Node lookup[MAXN];
int n;

int find_idx(int val) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (lookup[mid].val == val) return lookup[mid].idx;
        if (lookup[mid].val < val) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

void solve_pre_in(int pre_st, int pre_en, int in_st, int in_en) {
    if (pre_st > pre_en) return;
    if (pre_st == pre_en) {
        cout << "()";
        return;
    }
    int root = pre_arr[pre_st];
    int idx = find_idx(root);
    int L_size = idx - in_st;
    int R_size = in_en - idx;

    if (L_size > 0 && R_size > 0) {
        cout << "(";
        solve_pre_in(pre_st + 1, pre_st + L_size, in_st, idx - 1);
        cout << ",";
        solve_pre_in(pre_st + L_size + 1, pre_en, idx + 1, in_en);
        cout << ")";
    } else if (L_size > 0) {
        cout << "(";
        solve_pre_in(pre_st + 1, pre_st + L_size, in_st, idx - 1);
        cout << ")";
    } else if (R_size > 0) {
        cout << "(";
        solve_pre_in(pre_st + L_size + 1, pre_en, idx + 1, in_en);
        cout << ")";
    }
}

void solve_post_in(int post_st, int post_en, int in_st, int in_en) {
    if (post_st > post_en) return;
    if (post_st == post_en) {
        cout << "()";
        return;
    }
    int root = post_arr[post_en];
    int idx = find_idx(root);
    int L_size = idx - in_st;
    int R_size = in_en - idx;

    if (L_size > 0 && R_size > 0) {
        cout << "(";
        solve_post_in(post_st, post_st + L_size - 1, in_st, idx - 1);
        cout << ",";
        solve_post_in(post_st + L_size, post_en - 1, idx + 1, in_en);
        cout << ")";
    } else if (L_size > 0) {
        cout << "(";
        solve_post_in(post_st, post_st + L_size - 1, in_st, idx - 1);
        cout << ")";
    } else if (R_size > 0) {
        cout << "(";
        solve_post_in(post_st + L_size, post_en - 1, idx + 1, in_en);
        cout << ")";
    }
}

void solve_pre_post(int pre_st, int pre_en, int post_st, int post_en) {
    if (pre_st > pre_en) return;
    if (pre_st == pre_en) {
        cout << "()";
        return;
    }
    int left_child_root = pre_arr[pre_st + 1];
    int idx = find_idx(left_child_root);
    int L_size = idx - post_st + 1;
    int R_size = (pre_en - pre_st) - L_size;

    if (L_size > 0 && R_size > 0) {
        cout << "(";
        solve_pre_post(pre_st + 1, pre_st + L_size, post_st, idx);
        cout << ",";
        solve_pre_post(pre_st + L_size + 1, pre_en, idx + 1, post_en - 1);
        cout << ")";
    } else {
        cout << "(";
        solve_pre_post(pre_st + 1, pre_en, post_st, post_en - 1);
        cout << ")";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int z;
    if (!(cin >> z)) return 0;
    
    while (z--) {
        cin >> n;
        string type1, type2;
        
        cin >> type1;
        for (int i = 0; i < n; ++i) cin >> A[i];
        
        cin >> type2;
        for (int i = 0; i < n; ++i) cin >> B[i];

        pre_arr = in_arr = post_arr = nullptr;

        if (type1 == "PREORDER") pre_arr = A;
        else if (type1 == "INORDER") in_arr = A;
        else if (type1 == "POSTORDER") post_arr = A;

        if (type2 == "PREORDER") pre_arr = B;
        else if (type2 == "INORDER") in_arr = B;
        else if (type2 == "POSTORDER") post_arr = B;

        int* target_arr = (in_arr != nullptr) ? in_arr : post_arr;
        for (int i = 0; i < n; ++i) {
            lookup[i].val = target_arr[i];
            lookup[i].idx = i;
        }
        
        sort(lookup, lookup + n);

        if (pre_arr && in_arr) solve_pre_in(0, n - 1, 0, n - 1);
        else if (post_arr && in_arr) solve_post_in(0, n - 1, 0, n - 1);
        else solve_pre_post(0, n - 1, 0, n - 1);

        cout << "\n";
    }
    
    return 0;
}
