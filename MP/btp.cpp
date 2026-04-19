#include<iostream>
#include<string>
using namespace std;
#include "solution.h"


int main(){
   ios_base::sync_with_stdio(false);
   int z, n, k, number, number2;
   string name;
   map<int, string> T;

   cin >> z;
   while(z--) {
      cin >> n;
      while(n--) {
         string cmd;
         cin >> cmd;

         if (cmd == "INSERT")
         {
             cin >> number >> name;
             node<int, string>* a = T.find(number);
             if (a) cout << "ERROR" << endl; else T[number] = name;
         }
         if (cmd == "FIND") {
             cin >> number;
             node<int, string>* a = T.find(number);
             if (a) cout << "YES " << *a; else cout << "NO" << endl;
         }
         if (cmd == "DELETE") {
             cin >> number;
             if (T.delet(number)) cout << "OK" << endl;
             else cout << "ERROR" << endl;
         }
         if (cmd == "PRINT") T.print();

         if (cmd == "TEST") {
             cin >> number >> number2;
             cout << T.test(number, number2) << endl;
         }
         if (cmd == "SELECT") {
             cin >> k;
             node<int, string>* a = T.select(k);
             if (a) cout << *a; else cout << "ERROR" << endl;
         }
      }
      T.clean();
   }
   return 0;
}
