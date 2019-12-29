#include <bits/stdc++.h>
#ifdef TOPOLOGY
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
using namespace std;
 
int n, p[200003], inv[200003], tree[200003];
long long dp[200003];
 
void add(int i, int diff) {
	for (int j = i; j <= n; j += j & -j) {
		tree[j] += diff;
	}
}
 
int sum(int i) {
	int res = 0;
	for (int j = i; j; j -= j & -j) {
		res += tree[j];
	}
	return res;
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> p[i];
		inv[p[i]] = i + 1;
	}
	for (int i = 1; i <= n; i++) {
		int s = sum(inv[i]);
		add(inv[i], 1);
		dp[i] = dp[i - 1] + i - 1 - s;
		debug("%lld\n", dp[i]);
	}
	memset(tree, 0, sizeof(tree));
	map<int, int> mp;
	long long ans = 0LL;
	int cinv = -1, ccinv = -1;
	for (int i = 1; i <= n; i++) {
		if (i > 1) cout << ' ';
		// debug("fuck\n");
		if (i % 2 == 1 && i > 1) ccinv = next(mp.lower_bound(cinv))->first;
		else ccinv = cinv;
		// debug("Fuck\n");
		int s = sum(inv[i]);
		mp[inv[i]] = i;
		if (s * 2 < i - 1) {
			ans -= s;
			int cl = sum(cinv) - 1;
			int af = cinv - inv[i] - 1 - (cl - s);
			ans += af;
			if (cinv == ccinv) cinv = prev(mp.lower_bound(cinv))->first;
		} else if (s * 2 > i - 1) {
			ans -= i - 1 - s;
			int cr = sum(ccinv);
			int af = inv[i] - ccinv - 1 - (s - cr);
			ans += af;
			if (cinv < ccinv) cinv = ccinv;
		} else {
			ans -= s;
			cinv = inv[i];
		}
		add(inv[i], 1);
		cout << ans + dp[i];
	}
	cout << '\n';
	return 0;
}
