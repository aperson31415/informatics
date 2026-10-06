// There are acrtually many ways to do this problem, some are WAY faster, and some are WAY smaller code.

#include <bits/stdc++.h>
using namespace std;
 
vector<int> processed;
int N;
int prev_prime = 1;
 
int next_prime() {
    for(int j = prev_prime + 1; j <= N; j++) {
        if(processed[j] == 0) return j;
    }
    return -1;
}
 
int main() noexcept{
    freopen("primein.txt", "r", stdin);
    freopen("primeout.txt", "w", stdout);
    
    cin >> N;
    /* Erastosthenes sieve of whatever [Why are so many of these problems c++ only] */
    processed.resize(N + 1);
    processed[1] = 1;
    processed[0] = 1;
 
    while(true) {
        int newprime = next_prime();
        if(newprime == -1) {
            return 0;
        }
        cout << newprime << "\n";
        
        for(int i = 1; i <= N / newprime; i++) {
            processed[i * newprime] = 1;
        }
 
        prev_prime = newprime;
    }
}
