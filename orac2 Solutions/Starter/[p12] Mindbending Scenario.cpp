#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int left1, bottom1, right1, top1;
    int left2, bottom2, right2, top2;
    cin >> left1 >> bottom1 >> right1 >> top1;
    cin >> left2 >> bottom2 >> right2 >> top2;
 
    int interleft, interbottom, interright, intertop;
    interleft = max(left1, left2);
    interbottom = max(bottom1, bottom2);
    interright = min(right1, right2);
    intertop = min(top1, top2);
 
    int interarea = 0;
    if(interleft < interright && interbottom < intertop) {
        interarea = (interright - interleft) * (intertop - interbottom);
    }
 
    int area1 = (right1 - left1) * (top1 - bottom1);
    int area2 = (right2 - left2) * (top2 - bottom2);
 
    int totalarea = area1 + area2 - interarea;
    cout << totalarea;
}
