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

const int MAX = 200;
int n;
pi P[MAX];

pi operator - (const pi & a,const pi & b) {
	return pi(b.first - a.first,b.second - a.second);
}

int cross(pi o,pi a,pi b) {
	a = a - o;
	b = b - o;
	return a.first*b.second - a.second*b.first;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",&P[i].first,&P[i].second);
	int ans = 0;
	loop(i,n) loop(j,i) {
		int ctr = 0;
		loop(k,n) ctr += cross(P[i],P[j],P[k]) == 0;
		ans = max(ans,ctr);
	}
	printf("%d\n",ans);
	return 0;
}
