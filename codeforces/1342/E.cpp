#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

vi cols;
vector<set<vector<vi>>> cnt;
vector<vi> grid;

vector<vi> get_transpose(){
	int n = sz(grid);
	vector<vi> ret(grid);
	loop(i, n) loop(j, n) ret[i][j] = grid[j][i];
	return ret;
}

void bt(int r, int k){
	if(r == sz(cols)) {
		cnt[k].emplace(grid);
		cnt[k].emplace(get_transpose());
		return ;
	}
	loop(c, sz(cols)){
		cols[c] ++;
		assert(grid[r][c] == 0);
		grid[r][c] = 1;
		bt(r + 1, k + (cols[c] > 1));
		grid[r][c] = 0;
		cols[c] --;
	}
}

void bf(int n){
	cols.clear();
	cols.resize(n, 0);
	cnt.clear();
	cnt.resize((n*(n-1))/2 + 1);
	grid.clear();
	grid.resize(n, vi(n, 0));
	bt(0, 0);
	loop(i, sz(cnt)) printf("%d ", sz(cnt[i]));
	puts("");
	fflush(stdout);
}

const int mod = 998244353, MAX = 200000  + 10;

int mul(int a, int b){
	return (a*(ll)b)%mod;
}

int fact[MAX];
int invInt[MAX], invFact[MAX];

int C(int n, int k){
	if(k > n) return 0;
	int ret = fact[n];
	ret = mul(ret, invFact[k]);
	ret = mul(ret, invFact[n-k]);
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	for(int n=1; n<=6;n++)
		bf(n);
	fact[0] = 1;
	for(int i = 1; i < MAX; i++) fact[i] = mul(i, fact[i-1]);
	invInt[1] = 1;
	for(int i = 2; i < MAX; i++) invInt[i] = mod-mul(mod/i, invInt[mod%i]);
	invFact[0] = 1;
	for(int i = 1; i < MAX; i++) {
		invFact[i] = mul(invFact[i-1], invInt[i]);
		assert(mul(fact[i], invFact[i]) == 1);
	}
	int n; ll K;
	cin >> n >> K;
	int ans = 0;
	if(K >= n) ans = 0;
	else if (K == 0) ans = fact[n];
	else {
		int q = n - K;
		int m = n - q;
		ans = C(m+q-1, q-1);
		ans = mul(ans, C(n, q));
		ans = mul(ans, 2);
	}
	cout << ans << endl;
	return 0;
}
