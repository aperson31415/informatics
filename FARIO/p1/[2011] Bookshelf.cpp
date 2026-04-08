#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M, I; cin >> N >> M >> I;
    vector<int> heights(N);
    for(int i = 0; i < N; i++) cin >> heights[i];
    vector<int> start_infected(M);
    for(int i = 0; i < M; i++) cin >> start_infected[i];
    for(int i = 0; i < M; i++) start_infected[i]--;
    sort(start_infected.begin(), start_infected.end());

    vector<int> irreplacable_raw(I);
    for(int i = 0; i < I; i++) cin >> irreplacable_raw[i];
    for(int i = 0; i < I; i++) irreplacable_raw[i]--;
    sort(irreplacable_raw.begin(), irreplacable_raw.end());
    vector<bool> irreplacable(N, false);
    for(int i = 0; i < N; i++) {
        auto stuff = lower_bound(irreplacable_raw.begin(), irreplacable_raw.end(), i);
        if(stuff == irreplacable_raw.end()) continue;
        if(*stuff == i) irreplacable[i] = true;
    }

    vector<bool> infected(N);
    for(int elem : start_infected) infected[elem] = true;

    int curr;
    for(int i = 0; i < M; i++) {
        int start_pos = start_infected[i];
        // Go as far left as you can, until you reach start or another infected
        if(start_pos != 0) {
            if(heights[start_pos - 1] >= heights[start_pos]) {
                curr = start_pos - 1;
                infected[curr] = true;
                while(curr > 0) {
                    if(heights[curr - 1] >= heights[curr] and !infected[curr - 1]) {
                        curr--;
                        infected[curr] = true;
                    } else {
                        break;
                    }
                }
            }
        }

        // Go as far right as you can, until you reach end or another infected
        if(start_pos != N - 1) {
            if(heights[start_pos + 1] >= heights[start_pos]) {
                curr = start_pos + 1;
                infected[curr] = true;
                while(curr < N - 1) {
                    if(heights[curr + 1] >= heights[curr] and !infected[curr + 1]) {
                        curr++;
                        infected[curr] = true;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    int res = 0;
    for(int i = 0; i < N; i++) {
        if(irreplacable[i] and infected[i]) {
            res++;
        }
    }

    cout << res;
}