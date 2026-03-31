#include <bits/stdc++.h>
using namespace std;
 
int N, querytype, query1, query2;
vector<vector<int>> direct_adj;
vector<bool> visited;
stack<int> stk;
bool finished = false;
 
vector<vector<int>> adj; // Adjacency list
 
void dfs(int node) {
	if(visited[node]) return; // There is a cycle
	visited[node] = true;
	for(auto neighbour : direct_adj[node]) {
		dfs(neighbour);
	}
}
 
int main() {
    cin >> N;
    direct_adj.resize(N + 1);
    for(int i = 1; i <= N; i++) {
        cin >> querytype;
        if(querytype == 1) {
            if(i != N) {
                direct_adj[i] = {i + 1};
            } else {
                direct_adj[i] = {};
            }
        } else if(querytype == 2) {
            cin >> query1;
            direct_adj[i] = {query1};
        } else if(querytype == 3) {
            cin >> query1 >> query2;
            direct_adj[i] = {query1, query2};
        }
    }
 
    visited.resize(N + 1, false);
    dfs(1);
 
    int not_visited = N;
 
    for(int i = 1; i <= N; i++) {
        if(visited[i]) {not_visited--;}
    }
 
    cout << not_visited;
}
