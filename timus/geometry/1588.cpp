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

const int MAX = 311;
const ll oo = 1LL << 60;
pi P[MAX];
int n;
ll dist[MAX][MAX];
bool done[MAX][MAX];

ll cross(pi o,pi a,pi b) {
	a.first -= o.first,a.second -= o.second;
	b.first -= o.first,b.second -= o.second;
	return a.first*(ll)b.second - a.second*(ll)b.first;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",&P[i].first,&P[i].second);
	sort(P,P + n);
	loop(i,n) loop(j,n){
		ll dx = P[i].first - P[j].first;
		ll dy = P[i].second - P[j].second;
		dist[i][j] = dx*dx + dy*dy;
	}
	double ans = 0;
	loop(i,n) loop(j,i) {
		pair<pi,int> S (P[j],j);
		pair<pi,int> E (P[i],i);
		loop(k,n) if(cross(P[i],P[j],P[k]) == 0) {
			S = min(S,mp(P[k],k));
			E = max(E,mp(P[k],k));
		}
		int s = S.second,e = E.second;
		if(done[s][e]) continue;
		done[s][e] = 1;
//		cout << P[s] <<" " << P[e] << " " << sqrt(dist[s][e]) << endl;
		ans += sqrt(dist[s][e]);
	}
	printf("%.0f\n",ans);

	return 0;
}
#endif
