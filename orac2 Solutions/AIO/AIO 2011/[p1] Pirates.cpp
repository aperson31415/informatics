#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int length, mypos, enempos;
    cin >> length >> mypos >> enempos;
 
    int goright, goleft;
    goleft = mypos+enempos;
    goright = length-mypos + length-enempos;
 
    cout << min(goleft, goright);
}
