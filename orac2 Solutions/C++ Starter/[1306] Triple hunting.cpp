#include <bits/stdc++.h>
using namespace std;
 
int main() {
    vector<int> triples;
    int n, x; cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x;
        if(x%3 == 0) triples.push_back(i + 1);
    }
 
    if(!triples.empty()) {
        cout << (int) triples.size() << "\n";
        for(auto triple : triples) cout << triple << " ";
    } else {
        cout << "Nothing here!";
    }
}
