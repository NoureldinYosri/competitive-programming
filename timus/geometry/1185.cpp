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

const int MAX = 1 << 10;
pi P[MAX];
int n;

ll cross(pi o,pi a,pi b) {
	a.first -= o.first,a.second -= o.second;
	b.first -= o.first,b.second -= o.second;
	return a.first*(ll)b.second - a.second*(ll)b.first;
}
int sgn(ll x) {
	return (x > 0) - (x < 0);
}

double dist(pi a,pi b) {
	return hypot(a.first - b.first,a.second - b.second);
}


vector<pi> getHull(){
	vector<pi> H;
	loop(i,n) {
		pi p = P[i];
		while(sz(H) > 1 && cross(H[sz(H)-2],H[sz(H)-1],p) >= 0) H.pop_back();
		H.push_back(p);
	}
	return H;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int L;
	scanf("%d %d",&n,&L);
	loop(i,n) scanf("%d %d",&P[i].first,&P[i].second);
	sort(P,P + n);
	vector<pi> U = getHull();
	reverse(P,P + n);
	vector<pi> D = getHull();

	double ans = 0;
	for(int i = 0;i+1 < sz(U);i++) ans += dist(U[i],U[i+1]);
	for(int i = 0;i+1 < sz(D);i++) ans += dist(D[i],D[i+1]);
	ans += 2*PI*L;
	printf("%.0f\n",ans);
	return 0;
}
#endif
