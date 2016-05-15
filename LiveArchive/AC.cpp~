
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long m;
vector<int> v, p;

void gao(int n, int i, long long k) {
	v.push_back(k);
	for (int j = i; p[j] <= n; ++j) {
		gao(n - p[j], j, (k * p[j]) % m);
	}
}

int main() {
	int re, n;

	for (int i = 2; i < 100; ++i) {
		bool f = true;
		for (int j = 2; j * j <= i; ++j) {
			f &= i % j != 0;
		}
		if (f) {
			p.push_back(i);
		}
	}
	scanf("%d", &re);
	for (int ri = 1; ri <= re; ++ri) {
		scanf("%d%lld", &n, &m);
		v.clear();
		gao(n, 0, 1);
		sort(v.begin(), v.end());
		printf("%lu\n", unique(v.begin(), v.end()) - v.begin());
	}
	
	return 0;
}
