#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n;
    cin >> n;
    vector<int> positions;
    positions.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> positions[i];
    }
 
    sort(positions.begin(), positions.end());
 
    int start = positions[0], end = positions[positions.size() - 1];
 
    cout << end-start+1;
}
