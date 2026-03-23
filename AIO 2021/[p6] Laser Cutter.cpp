#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int N; cin >> N;
    vector<char> lower(2*N), upper(2*N);
    for(int i = 0; i < 2*N; i++) cin >> lower[i];
    for(int i = 0; i < 2*N; i++) cin >> upper[i];
 
    int res = 0;
    int leftbound = 0, rightbound = 0, upbound = 0, lowbound = 0;
 
    for(int i = 0; i < 2*N; i++) {
        if (lower[i] == 'R') leftbound++;
        else if (lower[i] == 'D') lowbound++;
 
        if (upper[i] == 'R') rightbound++;
        else if(lower[i] == 'D') upbound++;
 
        res = max(res, min(abs(rightbound-leftbound), abs(upbound-lowbound)));
    }
 
    cout << res;
}
