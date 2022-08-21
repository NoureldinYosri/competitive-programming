#include <iostream>
#include <vector>
using namespace std;

bool is_enough(long long t, vector<int>& w, int n) {
	long long need = 0, extra = 0;
	for (int i = 0; i < n; i++) {
		if (t >= w[i]) {
			extra += (t - w[i]) / 2;
		}
		else {
			need += w[i] - t;
		}
	}
	return extra >= need;
}

void solve() {
	int n, m; cin >> n >> m;
	vector<int> a(m), w(n, 0);
	for (int i  = 0; i < m; i++) {
		cin >> a[i];
		w[a[i] - 1] += 1;
	}
	long long l = 0, r = 2*m;
	while (l + 1  < r) {
		long long mid = (l + r) / 2;
		if (is_enough(mid, w, n)) {
			r = mid;
		}
		else {
			l = mid;
		}
	}
	cout << r << endl;
}

int main(){
	int t = 1;
	cin >> t;
	while (t--) {
		solve();
	}
}