#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int d;
    cin >> d;
    vector<int> number;
    number.resize(d);
    for(int i = 0; i < d; i++) {
        cin >> number[i];
    }
 
    // Do the processing
    int output = 0;
    for(int i = d-1; i >= 0; i--) {
        if(number[i] == 0) {
            output += 1;
        } else {
            break;
        }
    }
 
    cout << output;
}
