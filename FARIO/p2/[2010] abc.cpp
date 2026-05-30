// Probably too slow?
%:include <bits/stdc++.h>
%:include <immintrin.h>
%:pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;
%:define print(...) printf(__VA_ARGS__)
%:define val(x) cerr<<#x<<'='<<x<<endl;
%:define elif else if
%:define fio(in, out) freopen(in,"r",stdin);freopen(out,"w",stdout)
%:define ll long long

struct StringHash {
    string raw;
    int n;

    StringHash(const string& s) {
        raw = s;
        n = s.size();
    }
};

int io = [](){cin.tie(0)->sync_with_stdio(0);return 0;}();
int main() {
    int n; cin >> n;
    
    vector<string> dictionary_by_len[22];
    
    for(int i = 0; i < n; i++) {
        string input; cin >> input;
        dictionary_by_len[input.size()].push_back(input);
    }
    
    for(int i = 1; i <= 20; i++) {
        sort(dictionary_by_len[i].begin(), dictionary_by_len[i].end());
    }
    
    int m; cin >> m;
    vector<StringHash> message;
    for(int i = 0; i < m; i++) {
        string input; cin >> input;
        message.emplace_back(input);
    }

    for(StringHash &word : message) {
        if(binary_search(dictionary_by_len[word.n].begin(), dictionary_by_len[word.n].end(), word.raw)) {
            cout << word.raw << '\n';
            continue;
        }

        string variant = word.raw;
        string result = "?";
        bool found = false;

        for(int j = 0; j < word.n; j++) {
            char original_char = variant[j];
            
            for(char c = 'a'; c <= 'z'; c++) {
                if(c == original_char) continue;
                
                variant[j] = c;
                
                if(binary_search(dictionary_by_len[word.n].begin(), dictionary_by_len[word.n].end(), variant)) {
                    result = variant;
                    found = true;
                    break;
                }
            }
            if(found) break;
            variant[j] = original_char;
        }
        cout << result << '\n';
    }
}