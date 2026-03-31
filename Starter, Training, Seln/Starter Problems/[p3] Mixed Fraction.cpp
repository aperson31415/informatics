#include <bits/stdc++.h>
using namespace std;
 
int main() {
    typedef long long ll;
    ll n, d, a, b;
    cin >> n >> d;
    a = floor(n/d);
    b = n - (a*d);
    if(b == 0) {
        cout << a;
    } else {
        cout << a << " " << b << "/" << d;
    }
}
