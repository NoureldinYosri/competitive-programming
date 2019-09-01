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

int n,m,K;
pi P[3];

int cross(pi o,pi a,pi b) {
	a.first -= o.first, a.second -= o.second;
	b.first -= o.first, b.second -= o.second;
	return a.first*b.second - a.second*b.first;
}

bool solve(){
	if(n > m) {
		swap(n,m);
		loop(i,K+1) swap(P[i].first,P[i].second);
	}
	if(n == 1) return K > 0;
	if(n == 2) return K > 1;
	if(K <= 1) return 0;
	return cross(P[0],P[1],P[2]) != 0;
}

int main(){
	freopen("in.in", "r", stdin);
//	freopen("out.out","w",stdout);
	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++) {
		scanf("%d %d %d",&n,&m,&K);
		for(int k = 0;k <= K;k++)
			scanf("%d %d",&P[k].first,&P[k].second);
		printf("Case #%d: %c\n",t,"NY"[solve()]);
	}
	return 0;
}
#endif
