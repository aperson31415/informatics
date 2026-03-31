#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int r, s, n;
    cin >> r >> s >> n;
    if(r*s < n) {
        cout << (r*s) << " " << n-(r*s);
    } else {
        cout << n << " 0";
    }
}
