#include <bits/stdc++.h>
using namespace std;
 
int N;
vector<vector<int>> adj;
vector<bool> visited;
 
void dfs(int node) {
	if(visited[node]) return; // There is a cycle
	visited[node] = true;
 
	for(auto neighbour : adj[node]) {
		dfs(neighbour);
	}
}
 
bool connected(int node1, int node2) {
    dfs(node1);
    if(visited[node2]) {
        visited.clear();
        visited.resize(N, false);
        return true;
    } else {
        visited.clear();
        visited.resize(N, false);
        return false;
    }
}
 
int main() {
    cin >> N;
    int a, b;
    adj.resize(N);
    while(true) {
        cin >> a >> b;
        if(a == -1 and b == -1) {break;}
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    visited.resize(N, false);
    while(true) {
        cin >> a >> b;
        if(a == -1 and b == -1) {return 0;}
        if(connected(a, b)) {cout << "yes\n";}
        else {cout << "no\n";}
    }
}
