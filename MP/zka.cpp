#include <iostream>
#include <string>

using namespace std;

template <typename T>
class node {
public:
    T v;
    node<T>* p1;
    node<T>* p2;

    node(T val) : v(val), p1(nullptr), p2(nullptr) {}

    void rl(node<T>* o, node<T>* n) {
        if (p1 == o) p1 = n;
        else if (p2 == o) p2 = n;
    }
};

template <typename T>
class doubleList {
public:
    string name;
    node<T>* h;
    node<T>* t;

    doubleList() : name(""), h(nullptr), t(nullptr) {}
    doubleList(string n) : name(n), h(nullptr), t(nullptr) {}

    void addFirst(T& nm) {
        node<T>* n = new node<T>(nm);
        addFirst(n);
    }

    void addFirst(node<T>* n) {
        if (!h) {
            h = t = n;
            n->p1 = n->p2 = nullptr;
        } else {
            h->rl(nullptr, n);
            n->p1 = h;
            n->p2 = nullptr;
            h = n;
        }
    }

    void addLast(T& nm) {
        node<T>* n = new node<T>(nm);
        addLast(n);
    }

    void addLast(node<T>* n) {
        if (!t) {
            h = t = n;
            n->p1 = n->p2 = nullptr;
        } else {
            t->rl(nullptr, n);
            n->p1 = t;
            n->p2 = nullptr;
            t = n;
        }
    }

    node<T>* detachFront() {
        if (!h) return nullptr;
        node<T>* r = h;
        if (h == t) {
            h = t = nullptr;
        } else {
            node<T>* nx = (h->p1 != nullptr) ? h->p1 : h->p2;
            if (nx) nx->rl(h, nullptr);
            h = nx;
        }
        r->p1 = r->p2 = nullptr;
        return r;
    }

    node<T>* detachLast() {
        if (!t) return nullptr;
        node<T>* r = t;
        if (h == t) {
            h = t = nullptr;
        } else {
            node<T>* pr = (t->p1 != nullptr) ? t->p1 : t->p2;
            if (pr) pr->rl(t, nullptr);
            t = pr;
        }
        r->p1 = r->p2 = nullptr;
        return r;
    }

    void reverse() {
        std::swap(h, t);
    }

    void unionn(doubleList<T>& L) {
        if (!L.h) return;
        if (!h) {
            h = L.h;
            t = L.t;
        } else {
            t->rl(nullptr, L.h);
            L.h->rl(nullptr, t);
            t = L.t;
        }
        L.h = L.t = nullptr;
    }

    void clean() {
        node<T>* c = h;
        node<T>* p = nullptr;
        while (c) {
            node<T>* nx = (c->p1 != p) ? c->p1 : c->p2;
            delete c;
            p = c;
            c = nx;
        }
        h = t = nullptr;
    }
};

struct GS {
    doubleList<string> tr[20];
    bool ac[20];

    GS() {
        for (int i = 0; i < 20; ++i) ac[i] = false;
    }

    int f(const string& n) {
        for (int i = 0; i < 20; ++i) {
            if (ac[i] && tr[i].name == n) return i;
        }
        return -1;
    }

    int fs() {
        for (int i = 0; i < 20; ++i) {
            if (!ac[i]) return i;
        }
        return -1;
    }

    void cl() {
        for (int i = 0; i < 20; ++i) {
            if (ac[i]) {
                tr[i].clean();
                ac[i] = false;
            }
        }
    }
};

void solve() {
    int n;
    if (!(cin >> n)) return;

    GS st;

    for (int i = 0; i < n; ++i) {
        string c, t1, t2, p;
        cin >> c;

        if (c == "NEW") {
            cin >> t1 >> p;
            int s = st.fs();
            st.ac[s] = true;
            st.tr[s].name = t1;
            st.tr[s].addLast(p);
        } 
        else if (c == "BACK") {
            cin >> t1 >> p;
            st.tr[st.f(t1)].addLast(p);
        } 
        else if (c == "FRONT") {
            cin >> t1 >> p;
            st.tr[st.f(t1)].addFirst(p);
        } 
        else if (c == "PRINT") {
            cin >> t1;
            int s = st.f(t1);
            cout << "\"" << t1 << "\":\n";
            node<string>* cur = st.tr[s].h;
            node<string>* pr = nullptr;
            while (cur) {
                cout << cur->v;
                node<string>* nx = (cur->p1 != pr) ? cur->p1 : cur->p2;
                if (nx) cout << "<-";
                pr = cur;
                cur = nx;
            }
            cout << "\n";
        } 
        else if (c == "REVERSE") {
            cin >> t1;
            st.tr[st.f(t1)].reverse();
        } 
        else if (c == "UNION") {
            cin >> t1 >> t2;
            int s2 = st.f(t2);
            st.tr[st.f(t1)].unionn(st.tr[s2]);
            st.ac[s2] = false;
        } 
        else if (c == "DELFRONT") {
            // DELFRONT Train1 Train2 -> t1 to nowy, t2 to źródło
            cin >> t1 >> t2;
            int s2 = st.f(t2);
            node<string>* nd = st.tr[s2].detachFront();
            if (!st.tr[s2].h) st.ac[s2] = false;

            int s1 = st.fs();
            st.ac[s1] = true;
            st.tr[s1].name = t1;
            st.tr[s1].addFirst(nd);
        } 
        else if (c == "DELBACK") {
            // DELBACK Train2 Train1 -> t1 to źródło, t2 to nowy
            cin >> t1 >> t2;
            int src = st.f(t1);
            node<string>* nd = st.tr[src].detachLast();
            if (!st.tr[src].h) st.ac[src] = false;

            int dst = st.fs();
            st.ac[dst] = true;
            st.tr[dst].name = t2;
            st.tr[dst].addFirst(nd);
        }
    }
    st.cl();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int z;
    if (cin >> z) {
        while (z--) solve();
    }
    return 0;
}
