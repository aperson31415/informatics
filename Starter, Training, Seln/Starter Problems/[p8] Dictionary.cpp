#include <bits/stdc++.h>
using namespace std;
 
int main() {
    typedef long long ll;
    unordered_map<string, string> translations;
    vector<string> output;
    int d, w;
    string part_a, part_b;
    string query;
 
    cin >> d >> w;
 
    // Translations
    for(int i = 0; i < d; i++) {
        cin >> part_a >> part_b;
        translations[part_a] = part_b;
    }
 
    //Questions
    for(int i = 0; i < w; i++) {
        cin >> query;
        try {
            output.push_back(translations.at(query));
        } catch (...) {
            output.push_back("C?");
        }
    }
 
    //Output
 
    for(string i : output) {
        cout << i << "\n";
    }
}
