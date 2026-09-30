#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int N;
    cin >> N;
    vector<int> problems; problems.resize(N);
    for(int i = 0; i < N; i++) {
        cin >> problems[i];
    }
 
    map<int, int> frequencies;
    for(int i = 0; i < N; i++) {
        if(frequencies.count(problems[i]) == 1) {
            // Already exists
            frequencies[problems[i]]++;
        } else {
            // Doesnt exist yet
            frequencies[problems[i]] = 1;
        }
    }
 
    int current_answer = 0, answer = 0, proccessed_curr_ans = 0;
    // Then do the loop of finding maximums of stuff
    for(int i = problems[problems.size() - 1]; i > 0; i--) {
        // Calculate current_answer
        if(frequencies.count(i) == 1) {
            // Yay some occurences to add on
            current_answer += frequencies[i];
        }
        // current_answer now needs to be processed by adding i and floor div 2
        proccessed_curr_ans = floor((double)current_answer/2) + i;
 
        // And then compare with answer
        answer = max(answer, proccessed_curr_ans);
    }
 
    cout << answer;
}
