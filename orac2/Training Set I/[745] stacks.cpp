#include <bits/stdc++.h>
using namespace std;
 
int main() {
    freopen("stacksin.txt", "r", stdin);
    freopen("stacksout.txt", "w", stdout);
    
    vector<int> data(100);
    int end = -1;
    int x;
 
    while(true) {
        cin >> x;
        if(x == -1) {
            if(end == -1) {cout << "stack is empty!";}
            end -= 1;
            data[end + 1] = 0;
            if(end == -1) {cout << "stack is empty!";}
        } else if(x == -2) {
            return 0;
        } else {
            end += 1;
            data[end] = x;
        }
 
        for(int i = 0; i <= end; i++) {
            cout << data[i] << " ";
        }
 
        cout << "\n";
    }
}
