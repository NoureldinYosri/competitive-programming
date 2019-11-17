#ifdef ACTIVE
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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int MAX = 1 << 20;
int S[MAX];
ll A[MAX];
int n;

int sgn(ll x) {
	return (x > 0) - (x < 0);
}

int f(int x) {
	int res = 0;
	for(int i = max(x-4,0),r = min(x+4,n);i <= r && i+1 < n;i++) {
		res += S[i] != S[i+1];
	}
	return res;
}

int main(){
	freopen("pinball.in", "r", stdin);
	freopen("pinball.out", "w", stdout);
	scanf("%d",&n);
	loop(i,n) scanf("%lld",A + i);
	for(int i = 1;i < n;i++)
		S[i] = sgn(A[i] - A[i - 1]);
	int ans = 1;
	for(int i = 1;i < n;i++)
		ans += S[i] != S[i - 1];
	printf("%d\n",ans);
	int m; scanf("%d",&m);
	while(m--) {
		int x,y; scanf("%d %d",&x,&y);
		x--;
		ans -= f(x);
//		cerr << ans << endl;
		A[x] = y;
		if(x) S[x] = sgn(A[x] - A[x - 1]);
		if(x+1 < n) S[x+1] = sgn(A[x+1] - A[x]);
//		prArr(S,n,int);
		ans += f(x);
		printf("%d\n",ans);
	}
	return 0;
}
#endif
