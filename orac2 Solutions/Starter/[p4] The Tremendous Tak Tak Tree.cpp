#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int fruits, full_moons = 0;
    cin >> fruits;
    int fruits_at_time = fruits;
 
    // So basically wait until it is equal to 1 (mod 11)
    // I think u could do a modular arithmetic using some maths
    // But only if this fails cuz this wont be too slow i think
 
    // So just stimulate this
    while(true) {
        if(fruits_at_time % 11 == 1) {
            break;
        }
        full_moons += 1;
        fruits_at_time *= 2;
    }
 
    //Output
    cout << full_moons << " " << fruits_at_time;
 
}
