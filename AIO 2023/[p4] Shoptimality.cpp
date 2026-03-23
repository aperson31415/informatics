#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
 
    int N, M; cin >> N >> M;
    vector<int> H(N), S(M), P(M);
    for(int i = 0; i < N; i++) cin >> H[i]; 
    for(int i = 0; i < M; i++) cin >> S[i];
    for(int i = 0; i < M; i++) cin >> P[i];
 
    vector<int> pref_markets(M), suff_markets(M);
    for(int i = 0; i < M; i++) pref_markets[i] = P[i] + max(H[N-1], S[M-1]) - S[i];
    for(int i = 0; i < M; i++) suff_markets[i] = P[i] + S[i];
 
    vector<int> pref_markets_min(M + 1), suff_markets_min(M + 2);
    pref_markets_min[0] = INT_MAX - 1; suff_markets_min[M + 1] = INT_MAX - 1;
    for(int i = 0; i < M; i++) pref_markets_min[i + 1] = min(pref_markets_min[i], pref_markets[i]);
    for (int i = M; i >= 1; i--) {suff_markets_min[i] = min(suff_markets_min[i + 1], suff_markets[i - 1]);}
    map<int, int> housepos_toidx, marketpos_toidx;
    for(int i = 0; i < N; i++) housepos_toidx[H[i]] = i;
    for(int i = 0; i < M; i++) marketpos_toidx[S[i]] = i;
 
    for(int i = 0; i < N; i++) {
        if(upper_bound(S.begin(), S.end(), H[i]) == S.end()) {
            int left_start = S.size() - 1;
            int minbad_left = pref_markets_min[left_start + 1] - (max(H[N-1], S[M-1]) - H[i]);
            cout << minbad_left << " ";
        } else if(upper_bound(S.begin(), S.end(), H[i]) == S.begin()) {
            int right_start = marketpos_toidx[*upper_bound(S.begin(), S.end(), H[i])];
            int minbad_right = suff_markets_min[right_start + 1] - H[i];
            cout << minbad_right << " ";
        } else {
            int right_start = marketpos_toidx[*upper_bound(S.begin(), S.end(), H[i])];
            int left_start = marketpos_toidx[*upper_bound(S.begin(), S.end(), H[i])] - 1;
            int minbad_right = suff_markets_min[right_start + 1] - H[i];
            int minbad_left = pref_markets_min[left_start + 1] - (max(H[N-1], S[M-1]) - H[i]);
 
            cout << min(minbad_left, minbad_right) << " ";
        }
    }
}
