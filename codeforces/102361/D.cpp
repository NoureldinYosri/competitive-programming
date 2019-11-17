#ifdef ACTIVE
#include <bits/stdc++.h>
using namespace std;


int vis[1000];

bool solve(int n) {
	for(int i = 0;i <= n;i++) vis[i] = 0;
	int r = 1;
	while(r && !vis[r]) {
		vis[r] = 1;
		r = (r*10)%n;
	}

	return r;
}

int main(){
	int T; cin >> T;
	while(T--) {
		int n; cin >> n;
		cout << (solve(n) ? "Yes" : "No") << endl;
	}
	return 0;
}
#endif
