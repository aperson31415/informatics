#include <bits/stdc++.h>
using namespace std;
 
signed main() noexcept {
    int N;
    cin >> N;
    string word;
    cin >> word;
 
    int output = 0;
    char current_letter = ' ';
    int score = 0;
 
    for(char letter : word) {
        if(letter == current_letter or letter == '?') {
            score++;
        } else {
            output += score;
            score = 0;
            current_letter = letter;
        }
    }
    output += score;
 
    cout << output;
}
