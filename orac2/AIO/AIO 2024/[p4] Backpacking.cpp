#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

typedef long long ll;

template <typename T>
vector<int> closestSmallRight(const vector<T>& elems) {
    int n = (int)elems.size();
    vector<int> res(n);
    stack<int> stk;
    for (int i = n - 1; i >= 0; i--) {
        while (!stk.empty() && elems[stk.top()] >= elems[i]) {
            stk.pop();
        }
        res[i] = stk.empty() ? n : stk.top();
        stk.push(i);
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N; ll K; 
    cin >> N >> K;
    
    vector<ll> distances(N - 1);
    for(int i = 0; i < N - 1; i++) cin >> distances[i];
    
    vector<ll> positions(N, 0);
    for(int i = 0; i < N - 1; i++) positions[i + 1] = positions[i] + distances[i];
    
    vector<ll> costs(N);
    for(int i = 0; i < N; i++) cin >> costs[i];

    vector<int> next_cheapest = closestSmallRight(costs);
    
    ll total_cost = 0;
    int i = 0;
    ll current_cans = 0;

    while(i < N - 1) {
        if(next_cheapest[i] < N && (positions[next_cheapest[i]] - positions[i]) <= K) {
            int target = next_cheapest[i];
            ll dist_needed = positions[target] - positions[i];
            
            if (current_cans < dist_needed) {
                total_cost += (dist_needed - current_cans) * costs[i];
                current_cans = dist_needed;
            }
            
            current_cans -= dist_needed;
            i = target;
        } 
        else {
            ll dist_to_end = positions[N - 1] - positions[i];
            
            if(dist_to_end <= K) {
                if (current_cans < dist_to_end) {
                    total_cost += (dist_to_end - current_cans) * costs[i];
                }
                break; 
            } else {
                // Fill to max 
                total_cost += (K - current_cans) * costs[i];
                current_cans = K - distances[i];
                i++;
            }
        }
    }

    cout << total_cost;
}