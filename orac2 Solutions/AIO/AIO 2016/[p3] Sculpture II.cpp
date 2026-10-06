#include <bits/stdc++.h>
using namespace std;
 
bool is_ontop(tuple<int, int, int> a, tuple<int, int, int> b) {
    auto a_time = get<0>(a); auto a_width = get<1>(a);
    auto b_time = get<0>(b); auto b_width = get<1>(b);
    int a_right = a_time, b_right = b_time;
    int b_left = b_time + b_width;
    return (a_right >= b_right and a_right < b_left);
}
 
int main() {
    int max_height = 1, height = 0;
    int t, w, h;
    stack<int> stk;
    int n;
    cin >> n;
    vector<tuple<int, int, int>> stuff(n);
    for(int i = 0; i < n; i++) {
        cin >> t >> w >> h;
        stuff[i] = {t, w, h};
 
        while(!stk.empty()) {
            if(is_ontop(stuff[i], stuff[stk.top()])) {
                break;
            } else {
                height -= get<2>(stuff[stk.top()]);
                stk.pop();
            }
        }
 
        stk.push(i);
        height += get<2>(stuff[stk.top()]);
        max_height = max(max_height, height);
    }
    cout << max_height;
}
