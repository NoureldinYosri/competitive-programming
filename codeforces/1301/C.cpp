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

ll C(ll n){
	return (n*(n+1LL))/2;
}

ll solve(int n, int m){
	if(m == 0) return 0;
	if(n == m) return C(n);
	int d = (n - m)/(m + 1);
	ll ret = C(n);
	int r = (n - m)%(m + 1);
	ret -= C(d)*(m+1-r) + C(d+1) * r;
	return ret;
}


int bf(int n, int m){
	vi V(n, 0), ord;
	loop(i, m) V[i] = 1;
	loop(i, n) ord.pb(i);
	int ret = 0;
	do{
		int tmp = 0;
		int prv = -1;
		loop(j, n){
			int i = ord[j];
			if(V[i]) prv = j;
			tmp += prv + 1;
		}
		ret = max(ret, tmp);
	}while(next_permutation(all(ord)));
	return ret;
}

void test(){
	int n = rand()%10 + 1;
	int m = rand()%(n+1);
	int correct = bf(n, m);
	int ans = solve(n, m);
	if(ans != correct){
		cerr << "failed on " << n << " " << m << endl;
		cerr << "expected " << correct << " found " << ans << endl;
		exit(0);
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
/*	for(int t = 1;;t++){
		test();
		cerr << "passed " << t << endl;
	}
*/
	int T; scanf("%d", &T);
	while(T--){
		int n, m; scanf("%d %d", &n, &m);
		printf("%lld\n", solve(n, m));
	}
	return 0;
}
