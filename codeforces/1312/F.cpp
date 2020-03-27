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

const int MAX = 1 << 20;
ll A[MAX];
int n;
int C[3];

map<pi, int> dp;
int ring;

int solve(int x, int prv){
	if(x <= 0) return 0;
	pi t(x, prv);
	if(dp.count(t)) return dp[t];
	set<int> S;
	loop(i, 3) if(i == 0 ||  (i != prv))
		S.insert(solve(x - C[i], i));
	int ret = 0;
	while(S.count(ret))ret++;
	dp[t] = ret;
	return ret;
}

vi path[3];
int stem[3], cycle[3];
const int W = 10;

void work(int condition){
	path[condition].clear();
	loop(i, 1000) path[condition].pb(solve(i, condition));
//	cerr << "in" << endl;
	for(stem[condition] = 1; ; stem[condition]++)
		for(cycle[condition] = 1; cycle[condition] <= 60; cycle[condition]++){
			bool y = 1;
			for(int i = stem[condition]; i < sz(path[condition]) && y; i++){
				y = path[condition][i] == path[condition][stem[condition] + (i - stem[condition])%cycle[condition]];
			}
			if(y) {
//				cerr << "out " << " " << stem[condition] << " " << cycle[condition] << endl;
				return;
			}
		}
	assert(0);
}

void get_stem_cycle(){
	dp.clear();
	loop(i, 3) work(i);
}


int get_val(ll x, int condition){
	if(x <= 0) return 0;
	if(x < stem[condition]) return path[condition][x];
	return path[condition][stem[condition] + (x - stem[condition])%cycle[condition]];
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		loop(i, 3) scanf("%d", C + i);
		get_stem_cycle();
		
		int v = 0;
		loop(i, n) {
			scanf("%lld", A + i);
			v ^= get_val(A[i], 0);
#ifdef HOME
			assert(get_val(A[i], 0) == solve(A[i], 0));
#endif
		}
		int ans = 0;
		loop(i, n) {
			int x = v ^ get_val(A[i], 0);
			loop(j, 3) {
				ans += x == get_val(A[i]-C[j], j);
#ifdef HOME
				assert(get_val(A[i]-C[j], j) == solve(A[i] - C[j], j));
#endif
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
