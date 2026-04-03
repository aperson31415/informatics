// Heavily based on someone else's

#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n; cin >> n;
    int xbest, wbest, nbest = 0;
    cin >> xbest >> wbest;
    for (int i=1; i < n; i++){
        int x, w; cin >> x >> w;
        if (x <= xbest or (x + w > xbest and x < xbest + wbest)){
            xbest = x; wbest = w; nbest = i;
        }
    }
    cout << nbest + 1;
}
