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

const int MAX = 500*1000 + 10,MAXB = 710;
int A[MAX];
ll f[MAXB][MAXB];







int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int Q; scanf("%d",&Q);
	while(Q--) {
		int t,x,y; scanf("%d %d %d",&t,&x,&y);
		if(t == 1) {
			for(int m = 1;m < MAXB;m++) {
				int r = x%m;
				f[m][r] += y;
			}
			A[x] += y;
		}
		else {
			if(x < MAXB) printf("%lld\n",f[x][y]);
			else {
				ll ans = 0;
				for(int i = y;i < MAX;i += x)
					ans += A[i];
				printf("%lld\n",ans);
			}
		}
	}
	return 0;
}
#endif
