#include <bits/stdc++.h>
using namespace std;
 
signed int main() {
    int N, K, x, t;
    cin >> N >> K;
    map<int, int> freq_table;
    int current_max = 1, current_data;
    for(int i = 0; i < N; i++) {
        cin >> x >> t;
        current_data = (x*K) -t;
        freq_table[current_data]++;
 
        if(freq_table[current_data] > current_max) {
            current_max = freq_table[current_data];
        }
    }
    cout << current_max;
}
