#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n;
    cin >> n;
 
    if(n >= 6) {
        cout << "1 2 " << n-3;
    } else {
        cout << "0 0 0";
    }
}
