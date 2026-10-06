#include <bits/stdc++.h>
using namespace std;
 
#define len(x) (int) x.size()
#define sort(x) sort(x.begin(), x.end())
#define ll long long
template<class T=int> struct range{T a,b,s; struct it{T v,s; T operator*()const{return v;} it&operator++(){v+=s;return *this;} bool operator!=(it o)const{return s>0?v<o.v:v>o.v;}}; it begin()const{return {a,s};} it end()const{return {b,s};} range(T b):a(0),b(b),s(1){} range(T a,T b,T s=1):a(a),b(b),s(s){} };
inline static int ceildiv(const int& a, const int& b) {return a / b + (a % b != 0);}
#define pow(a, n) ([](auto base, auto exp){ long long res=1; while(exp>0){ if(exp&1) res*=base; base*=base; exp>>=1; } return res; }((a),(n)))
 
signed main() noexcept {
    static int R, S;
    cin >> R >> S;
    vector<int> r_cards(R), s_cards(S);
    for(auto i : range<int>(0, R)) cin >> r_cards[i];
    for(auto i : range<int>(0, S)) cin >> s_cards[i];
 
    static unordered_map<int, int> r_count, s_count;
    for(auto card : r_cards) {
        if(r_count.find(card) != r_count.end()) ++r_count[card];
        else r_count[card] = 1;
    }
    for(auto card : s_cards) {
        if(s_count.find(card) != s_count.end()) ++s_count[card];
        else s_count[card] = 1;
    }
 
    static int snap_pairs = 0;
    for(auto& pair : r_count) {
        if(s_count.find(pair.first) != s_count.end()) {
            snap_pairs += r_count[pair.first]*s_count[pair.first];
        }
    }
 
    cout << snap_pairs;
}
