%:include <bits/stdc++.h>
%:include <immintrin.h>
%:pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;
%:define print(...) printf(__VA_ARGS__)
%:define val(x) cerr<<#x<<'='<<x<<endl;
%:define elif else if
%:define fio(in, out) freopen(in,"r",stdin);freopen(out,"w",stdout)

inline int _lg(int& x) {return 31-__builtin_clz(x);}
inline int _lg(long long& x) {return 63-__builtin_clzll(x);}

struct competitor {
    int num, lastround, challenger;
    bool operator<(const competitor& other) const {
        if(lastround != other.lastround) return lastround < other.lastround;
        if(challenger != other.challenger) return challenger < other.challenger;
        return num < other.num;
    }
};

int io = [](){cin.tie(0)->sync_with_stdio(0);fio("busin.txt", "busout.txt");return 0;}();
int main() {
    int n, k; cin >> n >> k;
    vector<int> skill(n), lastround(n, -1), challenger(n, -1), important(k);
    set<int> important_set;
    for(int i = 0; i < n; i++) cin >> skill[i];
    for(int i = 0; i < k; i++) {cin >> important[i]; important[i]--; important_set.insert(important[i]);}

    // Stimulate rounds
    int rounds = _lg(n);
    vector<int> prev_round(n), this_round(n/2);
    for(int i = 0; i < n; i++) prev_round[i] = i;
    for(int i = 0; i < rounds; i++) {
        for(int j = 0; j < (int) prev_round.size() / 2; j++) {
            int driverA = prev_round[2*j];
            int driverB = prev_round[2*j + 1];

            if (skill[driverA] > skill[driverB]) {
                this_round[j] = driverA;
                lastround[driverB] = i + 1;
                challenger[driverB] = driverA;
            } else {
                this_round[j] = driverB;
                lastround[driverA] = i + 1;
                challenger[driverA] = driverB;
            }
        }

        // Get ready for next round
        prev_round.resize(this_round.size());
        for(int ii = 0; ii < (int) prev_round.size(); ii++) prev_round[ii] = this_round[ii];
        if (this_round.size() > 1) this_round.resize(this_round.size() / 2, -1);
    }

    // Fix bug with last match
    int ultimate_winner = -1;
    int runner_up = -1;

    for(int i = 0; i < n; i++) {
        if (lastround[i] == -1) ultimate_winner = i;
        if (lastround[i] == rounds) runner_up = i;
    }

    if (ultimate_winner != -1 && runner_up != -1) {
        lastround[ultimate_winner] = rounds;
        challenger[ultimate_winner] = runner_up;
    }

    // Add important drivers to list
    set<competitor> to_see;
    for(int i = 0; i < k; i++) {
        int driver = important[i];
        to_see.insert({driver, lastround[driver], challenger[driver]});
    }

    // Get ones who were eliminated in earlier rounds first
    vector<bool> cleared(n, false);
    int res = 0;

    while(!to_see.empty()) {
        competitor curr = *to_see.begin();
        to_see.erase(to_see.begin());

        if (cleared[curr.num]) continue;

        res++;
        cleared[curr.num] = true;

        if (important_set.find(curr.challenger) != important_set.end()) {
            cleared[curr.challenger] = true;
        }
    }

    cout << res;
}