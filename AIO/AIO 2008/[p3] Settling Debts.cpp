// Just realised u can use prefix min instead of sparse table. oh well

#include <bits/stdc++.h>
using namespace std;

int op(int a, int b) {return min(a, b);}
int _lg(int& x) {return 31 - __builtin_clz(x);}

// hehe bash but slow & lots of memory used
template <typename T>
struct SparseTable {
    int n;
    vector<vector<T>> st;
    SparseTable() {}
    SparseTable(vector<T>& arr) {
        n = arr.size();
        if (n == 0) return;
        int levels = _lg(n) + 1;
        st.assign(levels, vector<T>(n));
        for (int i = 0; i < n; i++) {
            st[0][i] = arr[i];
        }
        for (int j = 1; j < levels; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = op(st[j - 1][i],
                st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T query(int L, int R) {
        int len = R - L + 1;
        int j = _lg(len);
        return op(st[j][L], st[j][R - (1 << j) + 1]);
    }
};

int main() {
    int N; cin >> N;
    vector<int> money_needed(N);
    for(int i = 0; i < N; i++) {
        cin >> money_needed[i];
        money_needed[i] *= -1;
    }
    vector<int> psums(N, money_needed[0]);
    for(int i = 1; i < N; i++) psums[i] = psums[i - 1] + money_needed[i];

    SparseTable min_table(psums);

    if(min_table.query(0, N - 1) >= 0) {
        cout << 1;
        return 0;
    }

    for(int start = 1; start < N; start++) {
        int half1 = min_table.query(start, N - 1) - psums[start - 1];
        int half2 = min_table.query(0, start - 1) + psums[N - 1] - psums[start - 1];

        //cout << half1 << " " << half2 << endl;

        if(half1 >= 0 and half2 >= 0) {
            cout << start + 1;
            break;
        }
    }
}