#include <bits/stdc++.h>
using namespace std;
 
#define len(x) (int) x.size()
#define llen(x) (ll) x.size()
#define iter(x) x.begin(), x.end()
#define tag(x) x:
#define elif else if
template<typename T=int>
struct range{T a,b,c; range(T b):a(0),b(b),c(1){} range(T a,T b):a(a),b(b),c(1){} range(T a,T b,T c):a(a),b(b),c(c){} struct it{T v,s; T operator*()const{return v;} it& operator++(){v+=s;return *this;} bool operator!=(const it&o)const{return s>0?v<o.v:v>o.v;}}; it begin()const{return {a,c};} it end()const{return {b,c};}};
typedef long long ll;
#define what_is(x) cerr << #x << " is " << x << endl;
 
static int N, M, L;
static vector<int> shop_pos, house_pos, pamphlet_nums;
 
int check(int R) {
    // Go through each house, return 1 if >, 0 if <, else -1 ig
    vector<int> counts(M);
    for(int i : range{M}) {
        counts[i] = upper_bound(shop_pos.begin(), shop_pos.end(), house_pos[i] + R) - 
                    lower_bound(shop_pos.begin(), shop_pos.end(), house_pos[i] - R);
    }
    sort(counts.begin(), counts.end());
    for(int i : range{M}) {
        if(counts[i] > pamphlet_nums[i]) return -1;
        elif(counts[i] < pamphlet_nums[i]) return 1;
    }
    return 0;
}
 
int main() {
    cin >> N >> M >> L;
    shop_pos.resize(N);
    house_pos.resize(M);
    pamphlet_nums.resize(M);
    for(int i : range{N}) cin >> shop_pos[i];
    for(int i : range{M}) cin >> house_pos[i];
    for(int i : range{M}) cin >> pamphlet_nums[i];
 
    static int lo = 0, hi = L + 1, mid;
    static int res;
    int ans = -1;
    while(lo <= hi) {
        mid = (hi + lo) / 2;
        res = check(mid);
        if(res == 1) {lo = mid + 1;} // R needs to reduce
        elif(res == -1) {hi = mid - 1;} // R needs to increase
        elif(res == 0) {ans = mid; break;}
    }
 
    cout << ans;
}
