#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int D, C0, P1, C1, P2, C2, current_max = 0;
    cin >> D >> C0 >> P1 >> C1 >> P2 >> C2;
 
    int op1 = 0, op2 = 0, op3 = 0, op4 = 0, op5 = 0;
    // Try None
    op1 = D * C0; // Days * Factory 1
    // Try F1 (If possible, when available)
    int days_until_get = ceil((double)P1/C0);
    int days_left = D - days_until_get;
    op2 = (days_until_get * C0 - P1) + days_left * (C0 + C1);
    if(days_until_get >= D) {
        op2 = 0;
    }
    // Try F2 (If possible, when available)
    days_until_get = ceil((double)P2/C0);
    days_left = D - days_until_get;
    op3 = (days_until_get * C0 - P2) + days_left * (C0 + C2);
    if(days_until_get >= D) {
        op3 = 0;
    }
    // Try F1, F2 (If possible, when available)
    int days_until_get_first = ceil((double)P1/C0);
    int days_until_get_second = ceil((double)(P2 - (days_until_get_first*C0 - P1))/(C0 + C1));
    op4 = (days_until_get_second*(C0 + C1) - (P2 - (days_until_get_first*C0 - P1))) + (D - (days_until_get_first + days_until_get_second))*(C0 + C1 + C2);
    if(days_until_get_first + days_until_get_second >= D) {
        op4 = 0;
    }
 
    // Try F2, F1 (If possible, when available)
    days_until_get_first = ceil((double)P2/C0);
    days_until_get_second = ceil((double)(P1 - (days_until_get_first*C0 - P2))/(C0 + C2));
    op5 = (days_until_get_second*(C0 + C2) - (P1 - (days_until_get_first*C0 - P2))) + (D - (days_until_get_first + days_until_get_second))*(C0 + C1 + C2);
    if(days_until_get_first + days_until_get_second >= D) {
        op5 = 0;
    }
 
    cout << max({op1, op2, op3, op4, op5});
}
