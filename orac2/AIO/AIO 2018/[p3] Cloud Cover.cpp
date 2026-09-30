#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int N, K;
    cin >> N >> K;
    vector<int> distances(N - 1);
    vector<int> Kdistances(N - K);
    for(int i = 0; i < N - 1; i++) cin >> distances[i];
 
    int current_sum = 0;
    for(int i = 0; i < K; i++) current_sum += distances[i];
    Kdistances[0] = current_sum;
 
    for(int i = 0; i < N - K - 1; i++) {
        current_sum -= distances[i];
        current_sum += distances[K + i];
        Kdistances[i + 1] = current_sum;
    }
 
    cout << *min_element(Kdistances.begin(), Kdistances.end()) << "\n";
}
