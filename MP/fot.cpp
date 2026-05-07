#include <bits/stdc++.h>
using namespace std;
int N = 1009;
int deleted = 0;
int added = 0;
vector<uint64_t> tab(N);
vector<int> points(N);

bool is_prime(int n){
    for(int i = 2;i*i<=n;i++)
        if(n%i==0)
            return false;
    return true;
}

int next_prime(int n){
    while(!is_prime(n))
        n++;
    return n;
}

uint64_t pack(char* str){
    uint64_t ans = 0;
    for(int i = 0 ;i<8;i++){
        ans = (ans << 8) | (uint8_t)str[i];
    }
    return ans;
}

void res(){
    int old_N = N;
    vector<uint64_t> old_tab = tab;
    vector<int> old_points = points;

    N *= 2;
    N = next_prime(N);
    tab.assign(N, 0); 
    points.assign(N, 0);

    int current_added = 0;
    for(int i = 0; i < old_N; i++){
        if(old_tab[i] > 1){ 
            uint64_t key = old_tab[i];
            int curr = key % N;
            int step = (key / N) % (N - 1) + 1;

            while(tab[curr] != 0){
                curr += step;
                curr %= N;
            }
            tab[curr] = key;
            points[curr] = old_points[i];
            current_added++;
        }
    }
    added = current_added;
    deleted = 0;
}

void clear(){
    for(int i = 0;i<N;i++){
        tab[i]=0;
        points[i]=0;
    }
    added = 0;
    deleted = 0;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int z;
    if(!(cin >> z)) return 0;
    while(z--){
        clear();
        int n;
        cin >> n;
        for(int i = 0;i<n;i++){
            string com;
            cin >> com;
            if(com=="INSERT"){
                char ch[8];
                for(int j=0;j<8;j++)
                    cin >> ch[j];
                int pts;
                cin >> pts;
                
                uint64_t key = pack(ch);
                int curr = key % N;
                int step = (key / N) % (N - 1) + 1;
                
                int first_del = -1;
                int start_curr = curr;

                while(tab[curr] > 0 && tab[curr] != key){
                    if(tab[curr] == 1 && first_del == -1)
                        first_del = curr;
                    curr += step;
                    curr %= N;
                    if(curr == start_curr) break;
                }
                
                if(tab[curr] == key){
                    points[curr] += pts;
                }
                else {
                    if(first_del != -1){
                        curr = first_del;
                        deleted--;
                    }
                    added++;
                    tab[curr] = key;
                    points[curr] = pts;
                }
            }
            else if(com=="FIND"){
                char ch[8];
                for(int j=0;j<8;j++)
                    cin >> ch[j];
                
                uint64_t key = pack(ch);
                int curr = key % N;
                int step = (key / N) % (N - 1) + 1;
                bool end = 0;
                int start_curr = curr;

                while(tab[curr] != 0 && tab[curr] != key){
                    curr += step;
                    curr %= N;
                    if(curr == start_curr){
                        end = 1;
                        break;
                    }
                }
                if(tab[curr] == 0)
                    end = 1;
                    
                cout << (end ? 0 : points[curr]) << '\n';
            }
            else if(com=="DELETE"){
                char ch[8];
                for(int j=0;j<8;j++)
                    cin >> ch[j];
                
                uint64_t key = pack(ch);
                int curr = key % N;
                int step = (key / N) % (N - 1) + 1;
                bool end = 0;
                int start_curr = curr;

                while(tab[curr] != 0 && tab[curr] != key){
                    curr += step;
                    curr %= N;
                    if(curr == start_curr){
                        end = 1;
                        break;
                    }
                }
                if(tab[curr] == 0)
                    end = 1;
                    
                if(end)
                    cout << "ERROR\n";
                else{
                    deleted++;
                    added--;
                    for(int i = 0;i<8;i++)
                        cout << ch[i];
                    cout << ' ' << points[curr] << '\n';
                    points[curr] = 0;
                    tab[curr] = 1;
                }
            }
            if(added + deleted > N / 2)
                res();
        }
    }
    return 0;
}
