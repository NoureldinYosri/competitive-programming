#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

int m,n;
int G[40][40];
vp dir;

void init(){
	set<pi> S;
	for(int dx = 0;dx <= 3*m;dx++)
		for(int dy = dx==0;dy <= 3*n;dy++){
			int a = dx,b = dy;
			int g = __gcd(a,b);
			a /= g;
			b /= g;
			S.insert(mp(a,b));
		}
	dir.reserve(sz(S));
	for(auto p : S) dir.pb(p);
}

int ccw(pi o,pi a,pi b){
	a.xx -= o.xx,a.yy -= o.yy;
	b.xx -= o.xx,b.yy -= o.yy;
	return a.xx*b.yy - a.yy*b.xx;
}

int sgn(int v){
	return (v > 0) - (v < 0);
}

bool intersect(pi a,pi b,pi c,pi d){
	int s1 = sgn(ccw(a,b,c)) ,s2 = sgn(ccw(a,b,d));
	if(s1 == 0 || s2 == 0) return 1;
	if(s1 == s2) return 0;
	s1 = sgn(ccw(c,d,a)),s2 = sgn(ccw(c,d,b));
	if(s1 == 0 || s2 == 0) return 1;
	return s1 != s2;
}

ll solve(pi s,pi e){
	ll ret = 0;
	loop(i,m) loop(j,n) {
		vector<pair<pi,pi> > sides {{{i,j},{i,j+1}},{{i,j},{i+1,j}},{{i+1,j},{i+1,j+1}},{{i,j+1},{i+1,j+1}}};
		bool cond = 0;
		for(auto side : sides) {
			if(intersect(s,e,side.xx,side.yy))
				cond = 1;
		}
		if(cond) ret += G[i][j];
	}
	return ret;
}

int main(){
	freopen("division.in", "r", stdin);
	freopen("division.out", "w", stdout);
	scanf("%d %d",&m,&n);
	loop(i,m) loop(j,n) scanf("%d",&G[i][j]);
	init();
	ll ans = 0;
	for(auto dl : dir){
		pi dr = dl;
		for(int offset = -m;offset <= 2*m;offset++) {
			pi s = mp(offset,0);
			pi e = mp(offset + 100*dr.xx,100*dr.yy);
			ans = max(ans,solve(s,e));
		}
		dr.yy *= -1;
		for(int offset = -m;offset <= 2*m;offset++) {
			pi s = mp(offset,0);
			pi e = mp(offset + 100*dr.xx,100*dr.yy);
			ans = max(ans,solve(s,e));
		}
	}
	cerr << ans << endl;
	printf("%lld\n",ans);
	return 0;
}
