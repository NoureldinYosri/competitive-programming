#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using vp = std::vector<pi>;
using ll = long long;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
void tc();
auto test_cases = [](){
	int T; scanf("%d", &T);
	while(T--) tc();
};
using namespace std;

const int MAX = 1024;
char G[MAX][MAX];
int m, n;

map<pi, pi> S[4];

bool cmp(pi A, pi B) {
	auto [a, b] = A;
	auto [c, d] = B;
	return a <= c && b <= d;
}

void insert(map<pi, pi> & S, pi A, pi B) {
	static vp toDelete;
	toDelete.clear();
	bool doInsert = true;
	for(auto [k, _] : S) {
		if(cmp(k, A)) toDelete.push_back(k);
		if(cmp(A, k)) doInsert = false;
	}
	for(auto k : toDelete) S.erase(k);
	if(doInsert) S[A] = B;
}

void tc() {
	scanf("%d %d", &m, &n);
	loop(i, m) scanf("%s", G[i]);
	loop(i, 4) S[i].clear();
	loop(i, m) loop(j, n) if(G[i][j] == 'B'){
		insert(S[0], pi(i, j), pi(i, j));
		insert(S[1], pi(i, -j), pi(i, j));
		insert(S[2], pi(-i, j), pi(i, j));
		insert(S[3], pi(-i, -j), pi(i, j));
	}
	static vp CH;
	CH.clear();
	loop(c, 4) {
		for(auto [_, p] : S[c]) CH.push_back(p);
	}
	sort(all(CH));
	CH.resize(unique(all(CH)) - CH.begin());
	pair<int, pi> ans(INT_MAX, pi(0, 0));
	int prvRow = INT_MAX;
	int minx = m-1, miny = n-1;
	int maxx = 0, maxy = 0;
	for(auto [x, y] : CH) {
		minx = min(minx, x);
		miny = min(miny, y);
		maxx = max(maxx, x);
		maxy = max(maxy, y);
	}
	for(int i = minx; i <= maxx; i++) {
		int prv = INT_MAX;
		for(int j = miny; j <= maxy; j++) {
			int d = 0;
			for(auto p : CH) {
				auto [x, y] = p;
				d = max(d, abs(x - i) + abs(y - j));
			}
			ans = min(ans, mp(d, pi(i, j)));
			if(d > prv) break;
			prv = d;
		}
		if(prv > prvRow) break;
		prvRow = prv;
	}
	auto [x, y] = ans.second;
	printf("%d %d\n", x + 1, y + 1);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
