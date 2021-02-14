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

int n;
int A[1 << 20];
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

unsigned long long f[1 << 20][2], g[1 << 20][2], pref[1 << 20][2];

int nxt[1 << 20];
int prv[1 << 20];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) loop(j, 2) {
		f[i][j] = rng();
		g[i][j] = g[i - 1][j] ^ f[i][j];
	}
	for(int i = 1; i <= n; i++) {
		scanf("%d", A + i);
		loop(j, 2)
			pref[i][j] = pref[i - 1][j] ^ f[A[i]][j];
	}
	

	vi ST;
	for(int i = n; i > 0; i--){
		while(!ST.empty() && A[ST.back()] <= A[i]) ST.pop_back();
		nxt[i] = ST.empty() ? -1 : ST.back();
		ST.push_back(i);
	}
	
	for(int i = 1; i <= n; i++) prv[i] = n + 1;
	
	ll ans = 0;
	int lim = n + 1;
	for(int i = n; i >= 1; i--){
		lim = min(lim, prv[A[i]]);
		prv[A[i]] = i;
		int j = i;
		for(; j != -1; j = nxt[j]){
			int m = A[j];
			int k = i + m - 1;
			if(k >= lim) break;
			ans += mp(pref[k][0] ^ pref[i - 1][0], pref[k][1] ^ pref[i - 1][1]) == mp(g[m][0], g[m][1]);
		}
	}
	cout << ans << endl;
	return 0;
}
