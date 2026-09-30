// Probably not correct bcuz test input (singular) are SUPER SHEET
 
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    freopen("convin.txt", "r", stdin); freopen("convout.txt", "w", stdout);
 
    int N; cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; i++) cin >> A[i];
 
    int curr = 1;
    deque<int> stk1;
    deque<int> stk2;
    for(auto elem : A) {
        if(elem == curr) {
            if(stk1.empty()) cout << 1 << "\n";
            else if(stk2.empty()) cout << 2 << "\n";
            else cout << "huh?\n";
        } else {
            if(!stk1.empty()) if(stk1.front() == curr) stk1.pop_front();
            if(!stk2.empty()) if(stk2.front() == curr) stk2.pop_front();
 
            if(!stk1.empty()) {
                if(stk1.back() < elem) {
                    stk1.push_back(elem); cout << 1 << "\n"; continue;
                }
            }
            if(stk1.empty()) {
                stk1.push_back(elem); cout << 1 << "\n"; continue;
            }
 
            if(!stk2.empty()) {
                if(stk2.back() < elem) {
                    stk2.push_back(elem); cout << 2 << "\n"; continue;
                }
            }
            if(stk2.empty()) {
                stk2.push_back(elem); cout << 2 << "\n"; continue;
            }
        }
    }
}