#include <bits/stdc++.h>
using namespace::std;
int main() {
    int n;
    int s;
    int m;
    cin >> n;
    vector<int> skill(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> skill[i];
    }
    cin >> s;
    vector<int> student(s, 0);
    for (int i = 0; i < s; i++) {
        cin >> student[i];
    }
    cin >> m;
    vector<int> master(m, 0);
    for (int i = 0; i < m; i++) {
        cin >> master[i];
    }
    sort(skill.begin(), skill.end());
    sort(student.begin(), student.end());
    sort(master.begin(), master.end());
    int st = 0;
    int ma = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        while (st < s && student[st] < skill[i]) {
            st++;
        }
        if (st == s) {
            break;
        }
        st++;
        count++;
 
    }
    sort(master.begin(), master.end(), greater<int>());
    sort(skill.begin(), skill.end(), greater<int>());
    for (int i = 0; i < n; i++) {
        while (ma < m && master[ma] > skill[i]) {
            ma++;
        }
        if (ma == m) {
            break;
        }
        ma++;
        count++;
    }
    cout << min(count, n);
 
