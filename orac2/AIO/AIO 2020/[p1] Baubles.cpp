#include<bits/stdc++.h>
using namespace std;
int main() {
 
	int ro, bo, s, rp, bp;
	cin >> ro >> bo >> s >> rp >> bp; 
 
	if(rp == 0) {
		cout << max(0, (s+bo)-(bp-1));
	} else if(bp == 0) {
		cout << max(0, (s+ro)-(rp-1));
	} else if(ro >= rp and bo >= bp) {
		int x = min(ro-(rp-1), bo-(bp-1));
		cout << x + s << endl;
	} else if(ro < rp or bo < bp) {
		int c = max(0, rp-ro) + max(0, bp-bo);
		cout << max(0, s-(c-1)) << endl;
	} 
}
