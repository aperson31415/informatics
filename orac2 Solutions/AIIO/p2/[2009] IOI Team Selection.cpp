#include <bits/stdc++.h>
using namespace std;
 
int main() {
    
    freopen("teamin.txt","r",stdin); freopen("teamout.txt", "w",stdout);
 
    int n;
    long long k;
    cin >> n >> k;
 
    long long ans[4];
 
    int people[4] = {1, 2, 3, 4};
    int cnt = 4;
    int pos = 0;
 
    for (int t = 0; t < 4; ++t) {
        pos = (pos + (k - 1) % cnt) % cnt;
 
        ans[t] = people[pos];
 
        for (int j = pos; j + 1 < cnt; ++j) {
            people[j] = people[j + 1];
        }
 
        --cnt;
 
        if (cnt > 0)
            pos %= cnt;
    }
 
    for (int m = 5; m <= n; ++m) {
        long long shift = k % m;
 
        for (int i = 0; i < 4; ++i) {
            ans[i] = ((ans[i] - 1 + shift) % m) + 1;
        }
    }
 
    cout << ans[0] << ' '
         << ans[1] << ' '
         << ans[2] << ' '
         << ans[3];
}
