#include <bits/stdc++.h>
using namespace std;
 
int main() {    
    int N;
    cin >> N;
    int goal;
    output = "NO";
    int team1 = 0;
    int team2 = 0;
 
    for(int i = 0; i < N; i++) {
        cin >> goal;
        if(goal == 1) team1++;
        else team2++;
      
        if(team1 > team2) output = "YES";
    }
 
    cout << output;
}
