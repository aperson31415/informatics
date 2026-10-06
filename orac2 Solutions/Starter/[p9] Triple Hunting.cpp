#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n;
    cin >> n;
 
    vector<int> numbers;
    numbers.resize(n);
    vector<int> output;
 
    // I could've just combined this loop with the next one,
    // also saving a buncha memory but too bad...
    for(int i = 0; i < n; i++) {
        cin >> numbers[i];
    }
 
    // Actually do processing
    for(int i = 0; i < n; i++) {
        if(numbers[i] % 3 == 0) {
            output.push_back(i + 1);
        }
    }
 
    //Output
    if(output.size() == 0) {
        cout << "Nothing here!";
    } else {
        cout << output.size() << "\n";
        for(int i: output) {
            cout << i << " ";
        }
    }
}
