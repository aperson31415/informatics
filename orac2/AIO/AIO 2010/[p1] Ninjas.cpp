#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n, k;
    cin >> n >> k;
    int caught;
    caught = ceil((double)n/(double)(k+1.0));
    cout << n-caught;
}
