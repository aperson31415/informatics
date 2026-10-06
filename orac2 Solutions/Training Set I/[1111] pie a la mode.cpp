#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int P, x; cin >> P;
    map<int, int> freq;
 
    int max_amount = 0, max_holder;
    for(int i = 0; i < P; i++) {
        cin >> x;
        freq[x]++;
        if(freq[x] > max_amount) {
            max_amount = freq[x];
            max_holder = x;
        }
    }
 
    cout << max_holder << " " << max_amount;
}
