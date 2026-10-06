#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int money, notes = 0;
    cin >> money;
 
    while(money >= 100) {
        notes += 1;
        money -= 100;
    }
    while(money >= 20) {
        notes += 1;
        money -= 20;
    }
    while(money >= 5) {
        notes += 1;
        money -= 5;
    }
    // Calculate rest
    notes += money;
 
    cout << notes;
}
