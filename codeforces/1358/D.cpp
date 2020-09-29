#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int A[1 << 20], n;
ll pref[1 << 20], sum[1 << 20], target;
ll S(ll x) {
	return (x*(x+1)) >> 1;
}

ll f(int x, int i) {
	ll taken = A[i] - x + 1;
	if(taken >= target) return x*target + S(target - 1);
	ll ret = x*taken + S(taken - 1);
	ll rem = target - taken;

	int s = i + 1, e = 2*n - 1;
	while(s < e) {
		int m = (s + e ) >> 1;
		if(pref[m] - pref[i] >= rem) e = m;
		else s = m+1;
	}
	// cerr << s << " rem is " << rem << " " << ret << endl;
	ret += sum[e-1] - sum[i];
	rem -= pref[e-1] - pref[i];
	ret += S(rem);
	// cerr << x << " " << i << " " << ret << endl;
	return ret;
}

int main(){
	scanf("%d %lld", &n, &target);
	for(int i = 0; i < n; i++) {
		scanf("%d", A + i);
		A[i + n] = A[i];
	}
	for(int i = 0; i < 2*n; i++) {
		pref[i] = A[i%n] + (i ? pref[i-1] : 0);
		sum[i] = S(A[i%n]) + (i ? sum[i-1] : 0);
	}
	// for(int i = 0; i < 2*n; i++)
	// 	cerr << A[i%n] << " " << pref[i] << " " << sum[i] << endl;

	ll ans = 0;
	for(int i = 0; i < n; i++) {
		int s = 1, e = A[i];
		while(e - s > 1) {
			int m1 = s + (e-s+1)/3;
			int m2 = m1 + (e-s+1)/3;
			if(f(m1, i) < f(m2, i)) s = m1 + 1;
			else e = m2 - 1;
		}
		ans = max(ans, max(f(s, i), f(e, i)));
	}

	cout << ans << endl;
	return 0;
}