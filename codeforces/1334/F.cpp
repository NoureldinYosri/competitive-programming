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


const ll oo = 1LL << 60;
const int MAX = 1 << 20;
int A[MAX], B[MAX], P[MAX], n, m;
int lst[MAX];
int nxt[MAX];
int R[MAX];
vi IDX[MAX];

ll dp[MAX];


ll neg_sum[MAX];
ll sum[MAX];
ll T[2][MAX];
int M;


void add(int p, ll v, ll *BIT){
	for(++p; p <= M; p += LSOne(p))
		BIT[p] += v;
}

ll get(int p, ll *BIT){
	ll ret = 0;
	for(++p; p; p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}




ll solve(){
	M = 2*n;
	for(int i = 0; i < n;i++){
		add(A[i], P[i], T[0]);
		add(A[i], min(P[i], 0), T[1]);
		sum[i] = get(M, T[0]) - get(A[i], T[0]);
		neg_sum[i] = get(A[i], T[1]);
//		cerr << "set " << i << " " << A[i] << " " << sum[i] << " " << neg_sum[i] << endl;
		
		ll & ret = dp[i];
		ret = oo;
		int x = A[i], r = R[x];
		if(r == 0) {
			ret = 0;
			continue;
		}
		if(nxt[i] != -1) {
			int j = nxt[i];
			if(dp[j] < oo){
				ll tmp = dp[j] + neg_sum[i] - neg_sum[j] + sum[i] - sum[j];
				ret = min(ret, tmp);				
			}
		}
		
		int y = B[r-1];
		auto ptr = upper_bound(all(IDX[y]), i);
		if(ptr != IDX[y].begin()){
			ptr--;
			
			int j = *ptr;
			if(dp[j] < oo){
				ll s = get(M, T[0]) - get(y, T[0]) - sum[j] - P[i];
				ll neg = get(y, T[1]) - neg_sum[j];
//				cerr << i << " " << y << " " << x << "\t" << s << " " << neg << endl;
				ll tmp = dp[j] + neg + s;	
				ret =  min(ret, tmp);				
			}
		}
		else ret = oo;		
	}
/*	prArr(dp, n, ll);
	prArr(neg_sum, n, ll);
	prArr(sum, n, ll);
*/	return dp[n-1];
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", A + i);
	for(int i = 1; i <= n; i++) scanf("%d", P + i);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) scanf("%d", B + i);
	A[0] = B[0] = 0;
	A[n+1] = B[m+1] = n+1;
	n += 2;
	m += 2;

	loop(i, m-1) if(B[i] >= B[i+1]){
		puts("NO");
		return 0;
	}
	loop(i, m) R[B[i]] = i;
	
	memset(lst, -1, sizeof lst);
	loop(i, n){
		IDX[A[i]].pb(i);
		nxt[i] = lst[A[i]];
		lst[A[i]] = i;
	}
	
/*	prArr(A, n, int);
	prArr(P, n, int);
	prArr(B, m, int);
*/

	ll ans = solve();

	if(ans >= oo){
		puts("NO");
		return 0;
	}
	puts("YES");
	cout << ans << endl;
	return 0;
}
