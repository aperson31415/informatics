#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
vector<ll> safe(const vector<ll>& v, ll T) {
    size_t n = v.size();
    size_t p = 0;
    while (p < n && 2 * v[p] < T) p++;
    
    vector<ll> out(n);
    long long l = (long long)p - 1;
    size_t r = p, k = 0;
    
    while (l >= 0 && r < n) {
        ll dl = T - 2 * v[l];
        ll dr = 2 * v[r] - T;
        if (dl <= dr) {
            out[k++] = dl;
            l--;
        } else {
            out[k++] = dr;
            r++;
        }
    }
    while (l >= 0) {
        out[k++] = T - 2 * v[l];
        l--;
    }
    while (r < n) {
        out[k++] = 2 * v[r] - T;
        r++;
    }
    return out;
}
 
bool checkT(const vector<ll>& a, const vector<ll>& b, ll T) {
    vector<ll> X = safe(a, T);
    vector<ll> Y = safe(b, T);
    return X == Y;
}
 
bool solve(const vector<ll>& A, const vector<ll>& Bq) {
    vector<ll> as_, bs_;
    size_t i = 0, j = 0;
    
    while (i < A.size() && j < Bq.size()) {
        if (A[i] == Bq[j]) {
            i++;
            j++;
        } else if (A[i] < Bq[j]) {
            as_.push_back(A[i++]);
        } else {
            bs_.push_back(Bq[j++]);
        }
    }
    while (i < A.size()) as_.push_back(A[i++]);
    while (j < Bq.size()) bs_.push_back(Bq[j++]);
    
    if (as_.empty()) return true;
 
    ll T1;
    if (as_[0] < bs_[0]) T1 = as_[0] + bs_.back();
    else T1 = bs_[0] + as_.back();
    
    if (checkT(as_, bs_, T1)) return true;
 
    ll T2;
    if (as_.back() > bs_.back()) T2 = as_.back() + bs_[0];
    else T2 = bs_.back() + as_[0];
    return checkT(as_, bs_, T2);
}
 
bool tryD(const vector<ll>& A, const vector<ll>& B, ll D) {
    size_t n = B.size();
    vector<ll> Bp(n);
    for (size_t k = 0; k < n; k++) Bp[k] = B[k] + D;
    return solve(A, Bp);
}
 
bool tryS(const vector<ll>& A, const vector<ll>& B, ll S) {
    size_t n = B.size();
    vector<ll> Bp(n);
    for (size_t k = 0; k < n; k++) Bp[k] = S - B[n - 1 - k];
    return solve(A, Bp);
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n; cin >> n;
 
    vector<ll> A(n), B(n);
    for (auto& x : A) cin >> x;
    for (auto& x : B) cin >> x;
 
    bool ok = tryD(A, B, A[0] - B[0]) ||
              tryS(A, B, A[n - 1] + B[0]) ||
              tryD(A, B, A[n - 1] - B[n - 1]) ||
              tryS(A, B, A[0] + B[n - 1]);
 
    cout << (ok ? "YES\n" : "NO\n");
}
