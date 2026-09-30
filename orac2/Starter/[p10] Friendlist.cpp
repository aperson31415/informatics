// Pretty inefficient but this is a starter prob
// So probably doesnt matter :)
 
#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int f, a, b;
    cin >> f;
    unordered_map<int, int> friend_count;
 
    // Proccess people
    for(int i = 0; i < f; i++) {
        cin >> a >> b;
 
        if(friend_count.find(a) != friend_count.end()) {
            friend_count[a] += 1;
        } else {
            friend_count[a] = 1;
        }
 
        if(friend_count.find(b) != friend_count.end()) {
            friend_count[b] += 1;
        } else {
            friend_count[b] = 1;
        }
    }
 
    //Get maximum
    set<int> max_holders;
    int max_amount = -1;
 
    for(auto pair: friend_count) { // name: friends
        if(pair.second > max_amount) {
            max_holders = {pair.first};
            max_amount = pair.second;
        } else if(pair.second == max_amount) {
            max_holders.insert(pair.first);
        }
    }
 
    //Output
 
    for(int id: max_holders) {
        cout << id << "\n";
    }
}
