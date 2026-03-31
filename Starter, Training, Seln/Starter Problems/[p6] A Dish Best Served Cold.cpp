#include <bits/stdc++.h>
using namespace std;
 
int main() {
    long long n, min = pow(10, 6), max = -1, sum = 0, current;
    cin >> n;
 
    for(int i = 0; i < n; i++) {
        cin >> current;
        sum += current;
        if(current < min) {
            min = current;
        }
        if(current > max) {
            max = current;
        }
    }
 
    cout << min << " " << max << " " << floor(sum/n);
}
