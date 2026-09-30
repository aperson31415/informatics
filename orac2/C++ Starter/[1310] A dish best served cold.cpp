#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n, x;
    cin >> n;
    int minimum = 1e9, maximum = 0, summation = 0;
    for(int i = 0; i < n; i++) {
        cin >> x;
        minimum = min(minimum, x);
        maximum = max(maximum, x);
        summation += x;
    }
    summation /= n;
    cout << minimum << " " << maximum << " " << summation;
}
