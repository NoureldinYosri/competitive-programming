#define rep(i,a,b) for(int i = a;i < b;i++)

const int maxn = 200010, maxlg = 18; // maxlg = ceil(log_2(maxn))
pair<pair<int,int>, int> L[maxn]; // O(n * log n) space
int P[maxlg+1][maxn], stp, cnt, sa[maxn];
int LCP[maxn];
struct suffix_array {
	int n;
	suffix_array(){}
	suffix_array(const string& s) : n(s.size()) { // O(n * log n)
		rep(i,0,n) P[0][i] = s[i];
		sa[0] = 0; // in case n == 1
		for (stp = 1, cnt = 1; cnt < n; stp++, cnt <<= 1) {
			rep(i,0,n) L[i] = {{P[stp-1][i], i + cnt < n ? P[stp-1][i+cnt] : -1}, i};
			std::sort(L, L + n);
			rep(i,0,n)
				P[stp][L[i].second] = i>0 && L[i].first == L[i-1].first ? P[stp][L[i-1].second] : i;
		}
		rep(i,0,n) sa[i] = L[i].second;
		loop(i,n - 1) LCP[i] = this->lcp(sa[i],sa[i + 1]);	
	}
	int lcp(int x, int y) { // time log(n); x, y = indices into string, not SA
		int k, ret = 0;
		if (x == y) return n - x;
		for (k = stp - 1; k >= 0 && x < n && y < n; k --)
			if (P[k][x] == P[k][y])
				x += 1<<k, y += 1<<k, ret += 1<<k;
		return ret;
	}

};



