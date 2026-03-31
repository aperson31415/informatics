#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    typedef long long ll;
    ll tickets, r, s, sitting, standing;
    cin >> r >> s >> tickets;
    if(r*s >= tickets) {
        sitting = tickets;
        standing = 0;
    } else {
        sitting = r*s;
        standing = tickets - (r*s);
    }
    cout << sitting << " " << standing;
}
