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




int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	map<int,vi> M;
	int n; scanf("%d",&n);
	loop(i,n) {
		int x; scanf("%d",&x);
		M[x].push_back(i+1);
	}
	if(M.count(1) && sz(M[1]) > 1) {
		printf("%d %d\n",M[1][0],M[1][1]);
		return 0;
	}
	int u = 1,v = 2;
	while(v <= M.rbegin()->first) {
		if(M.count(u) && M.count(v)) {
			int a = M[u][0],b = M[v][0];
			printf("%d %d\n",a,b);
			return 0;
		}
		u += v;
		swap(u,v);
	}
	puts("impossible");
	return 0;
}
#endif
