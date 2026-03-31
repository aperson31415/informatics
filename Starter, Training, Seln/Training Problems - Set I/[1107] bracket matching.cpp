#include <bits/stdc++.h>
using namespace std;
#define elif else if
 
int main() {
    int N; cin >> N;
    int track1 = 0, track2 = 0, track3 = 0;
    char bracket;
    stack<char> stk;
    for(int i = 0; i < N; i++) {
        cin >> bracket;
        if(!stk.empty()) {
            if(bracket == ')' and stk.top() != '(') {cout << "NO"; return 0;}
            if(bracket == ')' and stk.top() == '(') {stk.pop(); goto tracks;}
            if(bracket == ']' and stk.top() != '[') {cout << "NO"; return 0;}
            if(bracket == ']' and stk.top() == '[') {stk.pop(); goto tracks;}
            if(bracket == '}' and stk.top() != '{') {cout << "NO"; return 0;}
            if(bracket == '}' and stk.top() == '{') {stk.pop(); goto tracks;}
        }
        stk.push(bracket);
 
        tracks:
        if(bracket == '(') ++track1;
        else if(bracket == ')') --track1;
        else if(bracket == '[') ++track2;
        else if(bracket == ']') --track2;
        else if(bracket == '{') ++track3;
        else if(bracket == '}') --track3;
 
        if(track1 < 0 or track2 < 0 or track3 < 0) {cout << "NO"; return 0;}
    }
    if(track1 == 0 and track2 == 0 and track3 == 0) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}
