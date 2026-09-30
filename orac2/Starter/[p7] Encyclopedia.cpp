#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> word_counts, questions;
    word_counts.resize(n); questions.resize(q);
 
    for(int i = 0; i < n; i++) {
        cin >> word_counts[i];
    }
    for (int i = 0; i < q; i++) {
        cin >> questions[i];
    }
 
    for(int i = 0; i < questions.size(); i++) {
        cout << word_counts[questions[i] - 1] << "\n";
    }
}
