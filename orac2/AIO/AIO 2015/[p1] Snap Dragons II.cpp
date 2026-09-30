#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int r, c, r_rose, c_rose, r_scarlet, c_scarlet;
    cin >> r >> c;
    cin >> r_rose >> c_rose;
    cin >> r_scarlet >> c_scarlet;
 
    int distance = abs(r_rose - r_scarlet) + abs(c_rose - c_scarlet);
    if(distance % 2 == 1) {
        cout << "ROSE";
    } else {
        cout << "SCARLET";
    }
}
