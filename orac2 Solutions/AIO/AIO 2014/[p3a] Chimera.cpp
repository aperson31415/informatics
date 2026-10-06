#include <bits/stdc++.h>
using namespace std;
// sub2

int main() {
  int n; cin >> n;
  string a, b, c; cin >> a >> b >> c;
  int ABC=0,ABB=0,BAB=0,BBA=0,AAA=0;
  for(int i = 0; i < n; i++) {
    if(a[i] == b[i] and b[i] == c[i]) {
      AAA++;
    }
    else if(b[i] == c[i] and a[i] != b[i]) {
      ABB++;
    }
    else if(a[i] == c[i] and a[i] != b[i]) {
      BAB++;
    }
    else if(a[i] == b[i] and b[i] != c[i]) {
      BBA++;
    }
    else {
      ABC++;
    }
  }

  //cout << a << ' ' << b << ' ' << c << ' ' << ABC << " " << ABB << " " << BAB << " " << BBA << " " << AAA;

  int res = 0;
  // Use AAA
  res += AAA;
  AAA = 0;
  // Use cyclic 2s
  int cyclic2 = min({ABB, BAB, BBA});
  res += cyclic2 * 2;
  ABB -= cyclic2;
  BAB -= cyclic2;
  BBA -= cyclic2;
  // Use remaining ones
  int val1 = min(ABC, ABB);
  res += val1; ABC -= val1; ABB -= val1;
  int val2 = min(ABC, BAB);
  res += val2; ABC -= val2; BAB -= val2;
  int val3 = min(ABC, BBA);
  res += val3; ABC -= val3; BBA -= val3;
  // Use doubles
  res += ABB/2;
  ABB %= 2;
  res += BAB/2;
  BAB %=2;
  res += BBA/2;
  BBA %= 2;
  // Cyclic 3s
  res += ABC/3;
  ABC %= 3;
  // Edge case bit
  res += (ABB+BAB+BBA)/2;
  cout << res;
}
