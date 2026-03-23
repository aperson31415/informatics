// Completely not my code

#include <bits/stdc++.h>
 
using namespace std;
 
// Directions: 0: North, 1: East, 2: South, 3: West
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
 
struct State {
    int x, y, dir;
    string path;
};
 
int main() {
    int targetX, targetY;
    cin >> targetX >> targetY;
    
    int curX = 0, curY = 0;
    int curDir = 0;
    string result = "";
 
    while (curX != targetX || curY != targetY) {
        // left
        int leftDir = (curDir + 3) % 4;
        int nextLX = curX + dx[leftDir];
        int nextLY = curY + dy[leftDir];
 
        // right
        int rightDir = (curDir + 1) % 4;
        int nextRX = curX + dx[rightDir];
        int nextRY = curY + dy[rightDir];
 
        int distL = abs(targetX - nextLX) + abs(targetY - nextLY);
        int distR = abs(targetX - nextRX) + abs(targetY - nextRY);
 
        if (distL < distR) {
            curX = nextLX; curY = nextLY; curDir = leftDir;
            result += 'L';
        } else if (distR < distL) {
            curX = nextRX; curY = nextRY; curDir = rightDir;
            result += 'R';
        } else {
            if (abs(targetX - nextLX) > abs(targetY - nextLY)) {
                curX = nextLX; curY = nextLY; curDir = leftDir;
                result += 'L';
            } else {
                curX = nextRX; curY = nextRY; curDir = rightDir;
                result += 'R';
            }
        }
    }
    cout << result;
}
