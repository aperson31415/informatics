#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int N, S, K; cin >> N >> S >> K;
    int position = S;
    int a, b;
    for(int i = 0; i < K; i++) {
        cin >> a >> b;
        if (a < position and b >= position) {
            position--;
        } else if(a > position and b <= position) {
            position++;
        } else if(a == position) {
            position = b;
        }
    }
 
    cout << position;
}
