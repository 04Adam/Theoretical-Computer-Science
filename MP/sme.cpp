#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct dom {
    int id;
    int left;
    int right;
    int s;
    int s_d;
    int d_l;
    int d_g;
};

vector<int> order;
vector<dom> tab;

void dfs_order(int n, int& v) {
    if (n == 0)
        return;
    if (v == -1)
        order.push_back(n);
    dfs_order(tab[n].left, v);
    if (v == 0)
        order.push_back(n);
    dfs_order(tab[n].right, v);
    if (v == 1)
        order.push_back(n);
}

void dfs(int n, int f) {
    if (n == 0)
        return;
    tab[n].d_g = tab[n].d_l + (f == 0 ? 0 : tab[f].d_g);
    dfs(tab[n].left, n);
    dfs(tab[n].right, n);
    if (f != 0)
        tab[f].s_d += tab[n].s + tab[n].s_d;
}

int main() {
    int z;
    cin >> z;
    while (z--) {
        int n;
        cin >> n;
        
        tab.assign(n + 1, dom());
        ll SG = 0;
        for (int i = 1; i <= n; i++) {
            int l, r, s, d;
            cin >> l >> r >> s >> d;
            SG += s;
            tab[i].id = i;
            tab[i].left = l;
            tab[i].right = r;
            tab[i].s = s;
            tab[i].s_d = 0;
            tab[i].d_l = d;
            tab[i].d_g = 0;
        }
        
        string str;
        cin >> str;
        int v;
        if (str == "PREORDER")
            v = -1;
        else if (str == "INORDER")
            v = 0;
        else
            v = 1;
            
        dfs(1, 0);
        dfs_order(1, v);
        
        for (auto x : order)
            cout << tab[x].d_g << ' ';
        cout << '\n';
        
        for (auto x : order)
            cout << tab[x].s_d << ' ';
        cout << '\n';
        
        for (auto x : order) {
            ll l = (tab[x].left == 0 ? 0 : (tab[tab[x].left].s_d + tab[tab[x].left].s));
            ll r = (tab[x].right == 0 ? 0 : (tab[tab[x].right].s_d + tab[tab[x].right].s));
            if (l * 2 <= SG && r * 2 <= SG && (l + r + tab[x].s) * 2 >= SG) {
                cout << tab[x].id << '\n';
                break;
            }
        }
        
        // Czyszczenie wektorów dla następnego zestawu danych
        order.clear();
        tab.clear();
    }
    return 0;
}
