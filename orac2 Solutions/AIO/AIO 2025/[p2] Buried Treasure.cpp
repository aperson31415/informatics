#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int N, L;
    int Ai, Bi;
 
    cin >> N >> L;
    vector<int> A(N), B(N);
 
    int top = 2*10e9, bottom = -1;
 
    for(int i; i < N; i++) {
        cin >> Ai >> Bi;
        bottom = max(Ai, bottom);
        top = min(Bi, top);
    }
    cout << max(0, top-bottom+1);
}
