#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int houses, width;
    cin >> houses >> width;
    vector<int> people_no;
    people_no.resize(houses);
    for(int i = 0; i < houses; i++) {
        cin >> people_no[i];
    }
 
    int current_sum = 0, output;
 
    // Get first sum
    for(int j = 0; j < width; j++) {
        current_sum += people_no[j];
    }
 
    output = current_sum;
 
    // Do sliding window
    for(int k = 0; k < houses-width; k++) {
        current_sum -= people_no[k];
        current_sum += people_no[k+width];
        if(current_sum > output) {
            output = current_sum;
        }
    }
 
    cout << output;
}
