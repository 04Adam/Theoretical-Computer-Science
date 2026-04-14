#include <bits/stdc++.h>
using namespace std;
template <typename C, typename O>
class stackMin{
    private:
        unsigned int size;
        C*tab;
        C*Min;
        unsigned int ptr;
        unsigned int ptr_min;
        void resize() {
            unsigned int old_size = size;
            size *= 2;
            C* new_tab = new C[size];
            C* new_Min = new C[size];
            for(unsigned int i = 0; i < old_size; i++) {
                new_tab[i] = tab[i];
            }
            for(unsigned int i = 0; i < ptr_min; i++) {
                new_Min[i] = Min[i];
            }
            delete[] tab;
            delete[] Min;
            tab = new_tab;
            Min = new_Min;
        }
    public:
    stackMin(unsigned int size=4){
        this->size = size;
        tab = new C[size];
        Min = new C[size];
        ptr=0;
        ptr_min=0;
    }
    void push(C x){
        if(size==ptr)
            resize();
        tab[ptr++]=x;
        O comp;
        if(ptr_min==0)
            Min[ptr_min++] = x;
        else if(!comp(Min[ptr_min-1],x))
            Min[ptr_min++] = x;
    }
    bool pop(){
        if(ptr==0)
            return false;
        O comp;
        if(!comp(tab[ptr-1],Min[ptr_min-1])&&!comp(Min[ptr_min-1],tab[ptr-1]))
            ptr_min--;
        ptr--;
        return true;
    }
    C top(){
        return tab[ptr-1];
    }
    C min(){
        return Min[ptr_min-1];
    }
    bool empty(){
        return (ptr==0?true:false);
    }
    void clear(){
        ptr=0;
        ptr_min=0;
    }
    ~stackMin(){
        delete [] tab;
        delete [] Min;
    }
};
template<typename C>
class myPair{
public:
    C first;
    C second;
};
template<typename C>
class Pair{
public:
    int first;
    C second;
};
template<typename C,typename O>
void solveStack(stackMin<C, O> & S, int n){
    while(n--){
        string ins;
        cin >> ins;
        if(ins=="push"){
            C a;
            cin >> a;
            S.push(a);
        }
        else if(ins=="pop"){
            if(S.empty())
                cout << "ERROR\n";
            else{
                cout << S.top() << '\n';
                S.pop();
            }
        }
        else if(ins=="top"){
            if(S.empty())
                cout << "EMPTY\n";
            else
                cout << S.top() << '\n';
        }
        else if(ins=="min"){
            if(S.empty())
                cout << "EMPTY\n";
            else
                cout << S.min() << '\n';
        }
        else if(ins=="clear")
            S.clear();
        else if(ins=="empty")
            cout << (S.empty()?"YES\n":"NO\n");
    }
}
template<typename C, typename O>
class queueMin {
private:
    unsigned int max_size;
    C* tab;
    Pair<C>* Min;
    
    unsigned int head;
    unsigned int tail;
    unsigned int count;

    unsigned int head_min;
    unsigned int tail_min;
    unsigned int count_min;
    void resize() {
    unsigned int new_size = max_size * 2;
    C* new_tab = new C[new_size];
    Pair<C>* new_Min = new Pair<C>[new_size];

    for (unsigned int i = 0; i < count; i++) {
        new_tab[i] = tab[(head + i) % max_size];
    }

    for (unsigned int i = 0; i < count_min; i++) {
        new_Min[i] = Min[(head_min + i) % max_size];
    }

    delete[] tab;
    delete[] Min;

    tab = new_tab;
    Min = new_Min;

    head = 0;
    tail = count;

    head_min = 0;
    tail_min = count_min;

    max_size = new_size;
}

public:
    queueMin(unsigned int size = 4) {
        this->max_size = size;
        tab = new C[max_size];
        Min = new Pair<C>[max_size];
        
        head = 0;
        tail = 0;
        count = 0;
        
        head_min = 0;
        tail_min = 0;
        count_min = 0;
    }

    void enqueue(C x) {
        if(max_size==count)
            resize();
        O comp;
        int num = 0;
        
        while (count_min > 0) {
            unsigned int back_idx = (tail_min - 1 + max_size) % max_size;
            if (!comp(Min[back_idx].second, x)) {
                num += Min[back_idx].first + 1;
                tail_min = back_idx;
                count_min--;
            } else {
                break;
            }
        }
        
        Min[tail_min] = {num, x};
        tail_min = (tail_min + 1) % max_size;
        count_min++;

        tab[tail] = x;
        tail = (tail + 1) % max_size;
        count++;
    }

    bool dequeue() {
        if (count == 0)
            return false;

        if (Min[head_min].first == 0) {
            head_min = (head_min + 1) % max_size;
            count_min--;
        } else {
            Min[head_min].first--;
        }

        head = (head + 1) % max_size;
        count--;
        
        return true;
    }

    C front() {
        return tab[head];
    }

    C min() {
        return Min[head_min].second;
    }

    bool empty() {
        return count == 0;
    }

    void clear() {
        head = 0;
        tail = 0;
        count = 0;
        
        head_min = 0;
        tail_min = 0;
        count_min = 0;
    }

    ~queueMin() {
        delete[] tab;
        delete[] Min;
    }
};
template<typename C,typename O>
void solveQueue(queueMin<C, O> & S, int n){
    while(n--){
        string ins;
        cin >> ins;
        if(ins=="enqueue"){
            C a;
            cin >> a;
            S.enqueue(a);
        }
        else if(ins=="dequeue"){
            if(S.empty())
                cout << "ERROR\n";
            else{
                cout << S.front() << '\n';
                S.dequeue();
            }
        }
        else if(ins=="front"){
            if(S.empty())
                cout << "EMPTY\n";
            else
                cout << S.front() << '\n';
        }
        else if(ins=="min"){
            if(S.empty())
                cout << "EMPTY\n";
            else
                cout << S.min() << '\n';
        }
        else if(ins=="clear")
            S.clear();
        else if(ins=="empty")
            cout << (S.empty()?"YES\n":"NO\n");
    }
}

class CmpInt {
   public:
      bool operator()(const int & a, const int & b) {return abs(a) < abs(b);  }
};

class CmpString {
   public:
      bool operator()(const string& a, const string& b)  {
        if (a.size() == b.size())  return a < b;
        return a.size() < b.size();
      }
};
int main(){
    ios_base::sync_with_stdio(false);
   int z, n;
   string s, t;

   myPair<int> x;
   myPair< stackMin<int, CmpInt> > p;

   p.first.push(-5);
   p.first.push(-15);
   p.second.push(-7);
   p.second.push(3);

   cout << p.first.top() << " " << p.second.top() << endl;
   cout << p.first.min() << " " << p.second.min() << endl;

   cin >> z;
   while (z--) {
       cin >> n >> s >> t;
       if (t == "STACK") {
      switch(s[0]) {
         case 'I': { stackMin<int, CmpInt> S;    solveStack(S, n); break; }
         case 'S': { stackMin<string, CmpString> S; solveStack(S, n); break; }
         case 'D': { stackMin<double, greater<double> > S; solveStack(S, n); break; }
      }
       }
       else {      //if (t == "QUEUE")
      switch(s[0]) {
         case 'I': { queueMin<int, CmpInt> Q;    solveQueue(Q, n); break; }
         case 'S': { queueMin<string, CmpString> Q; solveQueue(Q, n); break; }
         case 'D': { queueMin<double, greater<double> > Q; solveQueue(Q, n); break; }
      }
       }
   }
   return 0;
}
