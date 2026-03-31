#include <bits/stdc++.h>
using namespace std;
 
bool comp(int a, int b) {
    return abs(a) < abs(b);
}
 
int main() {
    int N; cin >> N;
    vector<int> nums(N);
    for(int i = 0; i < N; i++) cin >> nums[i];
    sort(nums.begin(), nums.end(), comp);
    for(auto elem : nums) {
        cout << elem << "\n";
    }
}
