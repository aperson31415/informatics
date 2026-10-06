#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int target_x, target_y;
    cin >> target_x >> target_y;
    
    int curr_x = 0, curr_y = 0, curr_page = 0, curr_len = 0, len_at = 0, dir_cycle = 3;
    vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    while(true) {
        if(curr_len == len_at) {
            len_at = 0;
            if(dir_cycle == 1 or dir_cycle == 3) ++curr_len;
            dir_cycle++; dir_cycle %= 4;
        } else {
            if(curr_x == target_x and curr_y == target_y) {
                cout << curr_page;
                return 0;
            }
            curr_x += directions[dir_cycle].first;
            curr_y += directions[dir_cycle].second;
            ++curr_page;
            ++len_at;
        }
    }
}
