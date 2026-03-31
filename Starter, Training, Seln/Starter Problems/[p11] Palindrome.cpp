#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n;
    cin >> n;
    char input[n];
    cin >> input;
 
    // Actually do the proccessing
    char output[n];
 
    for(int i = 0; i < floor(n/2); i++) {
        if(input[i] == input[n-i-1]) {
            // Nothing happens
            output[i] = input[i];
            output[n-i-1] = input[n-i-1];
        } else if(input[i] > input[n-i-1]) {
            // Replace both by 2nd number
            output[i] = input[n-i-1];
            output[n-i-1] = input[n-i-1];
        } else if(input[i] < input[n-i-1]) {
            // Replace both by 1st number
            output[i] = input[i];
            output[n-i-1] = input[i];
        }
    }
 
    if(n%2 == 1) {
        int thingy = floor(n/2);
        output[thingy] = input[thingy];
    }
 
    for(char letter : output) {
        cout << letter;
    }
}
