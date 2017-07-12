/*#include"bits/stdc++.h"

using namespace std;

const int MAXSZ = (int) 1e5 + 5;
struct BIT {
	BIT() {
		clearbit();
	}
	int bit[MAXSZ];

	void clearbit() {
		memset(bit, 0, sizeof(bit));
	}

	void add(int idx, int val) {
		idx++;
		while (idx <= MAXSZ) {
			bit[idx - 1] += val;
			idx += idx & -idx;
		}
	}

	int get(int idx) {
		idx++;
		int val = 0;
		while (idx) {
			val += bit[idx - 1];
			idx -= idx & -idx;
		}
		return val;
	}
} b1, b2;
int tsz, psz, t[MAXSZ], p[MAXSZ], mu1[MAXSZ], mu2[MAXSZ], f[MAXSZ];

void computePrefix() {
	int len = 0;
	b1.clearbit();
	b2.clearbit();
	//add(p[0],1);
	for (int i = 1; i < psz; i++) {
		b1.add(p[i], 1);
		b2.add(1e5 - p[i], 1);
		pair<int, int> r = { b1.get(p[i]), b2.get(1e5 - p[i]) };
		while (len && r != make_pair(mu1[len], mu2[len])) {
			for (int j = i - len; j < i - f[len - 1]; j++)
				b1.add(p[j], -1), b2.add(1e5 - p[j], -1);
			len = f[len - 1];
			r = {b1.get(p[i]),b2.get(1e5 - p[i])};
		}
		len++;
		f[i] = len;
	}
}

void match() {
	int len = 0;
	b1.clearbit();
	b2.clearbit();
	char *s = "";
	for (int i = 0; i < tsz; i++) {
		b1.add(t[i], 1);
		b2.add(1e5 - t[i], 1);
		pair<int, int> r = { b1.get(t[i]), b2.get(1e5 - t[i]) };
		while (len && r != make_pair(mu1[len], mu2[len])) {
			for (int j = i - len; j < i - f[len - 1]; j++)
				b1.add(t[j], -1), b2.add(1e5 - t[j], -1);
			len = f[len - 1];
			r = {b1.get(t[i]),b2.get(1e5 - t[i])};
		}
		len++;
		if (len == psz) {
			cout << s << i - psz + 1;
			s = " ";
			for (int j = i - len + 1; j < i - f[len - 1] + 1; j++)
				b1.add(t[j], -1), b2.add(1e5 - t[j], -1);
			len = f[len - 1];
		}
	}
	cout << endl;
}

int main() {
//	freopen("test.in", "rt", stdin);
	int T;
	scanf("%d", &T);
	while (T--) {
		b1.clearbit();
		b2.clearbit();
		scanf("%d", &psz);
		map<int, int> m;
		for (int i = 0; i < psz; i++) {
			scanf("%d", p + i);
			m[p[i]];
		}
		int cnt = 0;
		for (auto &e : m) {
			e.second = cnt++;
		}
		for (int i = 0; i < psz; i++) {
			p[i] = m[p[i]];
			b1.add(p[i], 1);
			b2.add(1e5 - p[i], 1);
			mu1[i] = b1.get(p[i]);
			mu2[i] = b2.get(1e5 - p[i]);
		}
		m.clear();
		scanf("%d", &tsz);
		for (int i = 0; i < tsz; i++)
			scanf("%d", t + i), m[t[i]];
		cnt = 0;
		for (auto &e : m) {
			e.second = cnt++;
		}
		for (int i = 0; i < tsz; i++) {
			t[i] = m[t[i]];
		}
		computePrefix();
		//for (int i = 0; i < psz; i++) {
		//	cout << p[i] << " " << mu[i] << " " << f[i] << endl;
		//}
		//puts("");
		match();

	}
	return 0;
}

*/
