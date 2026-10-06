#include <bits/stdc++.h>
using namespace std;
 
int main() noexcept {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    static int N;
    cin >> N;
    static vector<int> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];
 
    unordered_map<int, int> B;
 
    for(int elem : A) {
        if(B.find(elem) == B.end()) {
            B[elem] = 0;
        }
        B[elem]++;
    }
 
    string c = "YES";
 
    for(const auto &pair : B) {
        if(B[pair.first] % pair.first != 0) c = "NO";
    }
 
    cout << c;
}
