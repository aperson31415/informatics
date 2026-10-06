#include <iostream>
#include <algorithm>
using namespace std;
 
int main() {
    int c, r, v;
    cin >> c >> r >> v;
 
    int x = 0, y = 0, z = 0; // x: rice+veg, y: curry+veg, z: curry+rice
 
    while (true) {
        // Create array of {count, label}
        pair<int, char> items[3] = {{c, 'c'}, {r, 'r'}, {v, 'v'}};
        sort(items, items + 3);
 
        // Pick top two items
        auto first = items[2];
        auto second = items[1];
 
        // If either is 0, we can't make a mouthful
        if (first.first == 0 || second.first == 0) break;
 
        // Use one scoop from each
        if ((first.second == 'r' && second.second == 'v') || (first.second == 'v' && second.second == 'r')) {
            x++;
            r--;
            v--;
        } else if ((first.second == 'c' && second.second == 'v') || (first.second == 'v' && second.second == 'c')) {
            y++;
            c--;
            v--;
        } else if ((first.second == 'c' && second.second == 'r') || (first.second == 'r' && second.second == 'c')) {
            z++;
            c--;
            r--;
        }
    }
 
    cout << x << " " << y << " " << z << endl;
    return 0;
}
