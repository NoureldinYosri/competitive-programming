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

const int mod = 1e9 + 7;
int add(int a, int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a, int b) {
	return (a*(ll)b)%mod;
}

int n, Q;
int A[1 << 20];
int B[1 << 20];

int have[1 << 20];

int bf(int l, int r) {
	vector<tuple<int, int, int>> edges;
	for(int i = l; i <= r; i++) if(B[i] < 0) {
		for(int j = l; j <= r; j++) if(B[j] > 0) {
			loop(a, -B[i]) loop(b, B[j])
				edges.emplace_back(abs(A[i] - A[j]), i, j);
		}
	}
	for(int i = l; i <= r; i++) have[i] = abs(B[i]);
	sort(all(edges));
	int ans = 0;
	for(auto [c, i, j] : edges) {
		int d = min({1, have[i], have[j]});
		ans = add(ans, mul(d, c));
		cerr << i << " " << j << ": " << d << " " << c << endl;
		have[i] -= d;
		have[j] -= d;
	}
	return ans;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &Q);
	loop(i, n) scanf("%d", A + i + 1);
	loop(i, n) scanf("%d", B + i + 1);
	while(Q--) {
		int l, r; scanf("%d %d", &l, &r);
		printf("%d\n", bf(l, r));
	}
	return 0;
}
