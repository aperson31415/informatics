#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

struct point {
    int x, y;
    bool operator<(const point& o) const {
        return tie(x, y) < tie(o.x, o.y);
    }
    bool operator==(const point& o) const {
        return x == o.x && y == o.y;
    }
    point operator+(const point& o) const {
        return {x + o.x, y + o.y};
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int R, C, N;
    cin >> R >> C >> N;

    set<point> usable;
    point curr = {0, 0};
    usable.insert(curr);

    for(int i = 0; i < N; i++) {
        char dir; cin >> dir;
        if(dir == 'N') curr.y++;
        else if(dir == 'E') curr.x++;
        else if(dir == 'S') curr.y--;
        else if(dir == 'W') curr.x--;
        usable.insert(curr);
    }

    point target = curr;
    queue<point> q;
    map<point, int> dist;

    map<point, point> prev;
    
    q.push({0, 0});
    dist[{0, 0}] = 0;

    int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

    while(!q.empty()) {
        point s = q.front(); q.pop();

        if(s == target) {
            cout << dist[s] << "\n";
            goto end;
        }

        for(int i = 0; i < 4; i++) {
            point next = {s.x + dx[i], s.y + dy[i]};
            if(usable.count(next) && dist.find(next) == dist.end()) {
                prev[next] = s;
                dist[next] = dist[s] + 1;
                q.push(next);
            }
        }
    }

    end:
    vector<char> moves;
    while(true) {
        if(!prev.count(target)) break;

        if(prev[target] == target + point{0, 1}) {
            target = prev[target];
            moves.push_back('N');
        } else if(prev[target] == target + point{0, -1}) {
            target = prev[target];
            moves.push_back('S');
        } else if(prev[target] == target + point{1, 0}) {
            target = prev[target];
            moves.push_back('E');
        } else if(prev[target] == target + point{-1, 0}) {
            target = prev[target];
            moves.push_back('W');
        }
    }

    for(char thing : moves) {
        cout << thing;
    }
}