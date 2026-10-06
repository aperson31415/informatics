#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
 
string normalize(string s) {
    int mapping[10];
    memset(mapping, -1, sizeof(mapping));
    int next_id = 0;
    string res = s;
    for (int i = 0; i < s.length(); ++i) {
        int group = s[i] - '0';
        if (mapping[group] == -1) mapping[group] = next_id++;
        res[i] = mapping[group] + '0';
    }
    return res;
}
 
string read_arrangement(int n) {
    string s(n, ' ');
    int group_id = 0, count = 0, val;
    while (count < n) {
        if (!(cin >> val)) break;
        if (val == 0) {
            group_id++;
        } else {
            s[val - 1] = group_id + '0';
            count++;
        }
    }
    return normalize(s);
}
 
int main() {
    freopen("socialin.txt", "r", stdin);
    freopen("socialout.txt", "w", stdout);
 
    int n; cin >> n;
 
    string start = read_arrangement(n);
    string target = read_arrangement(n);
 
    if (start == target) {
        cout << 0 << endl;
        return 0;
    }
 
    queue<pair<string, int>> q;
    q.push({start, 0});
    unordered_map<string, int> visited;
    visited[start] = 0;
 
    while (!q.empty()) {
        string curr = q.front().first;
        int dist = q.front().second;
        q.pop();
 
        if (curr == target) {
            cout << dist << endl;
            return 0;
        }
 
        int num_groups = 0;
        for (char c : curr) num_groups = max(num_groups, (c - '0') + 1);
 
        for (int g = 0; g < num_groups; ++g) {
            vector<int> members;
            for (int i = 0; i < n; ++i) if (curr[i] - '0' == g) members.push_back(i);
            
            if (members.size() >= 2) {
                string next = curr;
                int mid = (members.size() + 1) / 2; // Younger half gets the extra student
                for (int i = mid; i < (int)members.size(); ++i) {
                    next[members[i]] = num_groups + '0';
                }
                string norm = normalize(next);
                if (visited.find(norm) == visited.end()) {
                    visited[norm] = dist + 1;
                    q.push({norm, dist + 1});
                }
            }
        }
 
        for (int g1 = 0; g1 < num_groups; ++g1) {
            for (int g2 = g1 + 1; g2 < num_groups; ++g2) {
                string next = curr;
                for (int i = 0; i < n; ++i) 
                    if (next[i] - '0' == g2) next[i] = g1 + '0';
                
                string norm = normalize(next);
                if (visited.find(norm) == visited.end()) {
                    visited[norm] = dist + 1;
                    q.push({norm, dist + 1});
                }
            }
        }
 
        for (int g1 = 0; g1 < num_groups; ++g1) {
            for (int g2 = 0; g2 < num_groups; ++g2) {
                if (g1 == g2) continue;
                int oldest_g1 = -1, youngest_g2 = -1;
                for (int i = n - 1; i >= 0; --i) if (curr[i] - '0' == g1) { oldest_g1 = i; break; }
                for (int i = 0; i < n; ++i) if (curr[i] - '0' == g2) { youngest_g2 = i; break; }
 
                if (oldest_g1 != -1 && youngest_g2 != -1) {
                    string next = curr;
                    // Swap the group assignments of these specific students
                    char temp = next[oldest_g1];
                    next[oldest_g1] = next[youngest_g2];
                    next[youngest_g2] = temp;
 
                    string norm = normalize(next);
                    if (visited.find(norm) == visited.end()) {
                        visited[norm] = dist + 1;
                        q.push({norm, dist + 1});
                    }
                }
            }
        }
    }
}