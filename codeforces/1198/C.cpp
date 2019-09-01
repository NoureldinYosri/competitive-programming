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

const int MAXV = 300*1000 + 10;
const int MAXE = 500*1000 + 10;

int n,m;
int fr[MAXE],to[MAXE];
bool taken[MAXV];

void read(){
	scanf("%d %d",&n,&m);
	for(int e = 1;e <= m;e++)
		scanf("%d %d",fr + e,to + e);
}

void report(vi res,string name){
	puts(name.c_str());
	for(int i = 0;i < sz(res);i++) printf("%d%c",res[i]," \n"[i==sz(res)-1]);
}

void solve(){
	fill(taken,taken + 3*n + 1,0);
	vi E;
	for(int e = 1;e <= m;e++) {
		int u = fr[e],v = to[e];
		if(taken[u] || taken[v]) continue;
		E.push_back(e);
		taken[u] = taken[v] = 1;
		if(sz(E) == n) return report(E,"Matching");
	}
	vi V;
	for(int u = 1;u <= 3*n && sz(V) < n;u++)
		if(!taken[u])
			V.push_back(u);
	report(V,"IndSet");
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	tc(){
		read();
		solve();
	}
	return 0;
}
#endif
