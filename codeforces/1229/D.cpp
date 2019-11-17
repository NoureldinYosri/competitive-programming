#ifdef DEBUG
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

const ll mod = 1000000007;
const int MAX = 100*1000 + 10,MAXLG = 20;
ll val[MAX];
vi G[MAX];
int n;
int dfs_in[MAX],dfs_out[MAX],depth[MAX],dfs_time;
int P[MAX][MAXLG];
ll W[MAX][MAXLG];

ll gcd(ll a,ll b) {
	if(a==0 && b==0) return 0;
	while(b) {
		a = a%b;
		swap(a,b);
	}
	return a;
}

void dfs(int u,int p) {
	P[u][0] = p;
	W[u][0] = gcd(val[u],val[p]);
	loop(k,MAXLG-1) {
		int p = P[u][k];
		P[u][k+1] = P[p][k];
		W[u][k+1] = gcd(W[u][k],W[p][k]);
	}
//	cerr << u << ": ";
//	prArr(W[u],5,ll);
	dfs_in[u] = dfs_time++;
	depth[u] = depth[p] + 1;

	for(int v : G[u]) {
		if(v == p) continue;
		dfs(v,u);
	}
	dfs_out[u] = dfs_time-1;
}
int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b){
	return (a*(ll)b)%mod;
}

int getP(int u,int d) {
	int k = 0;
	while(d) {
		int t = LSOne(d);
		while(t != (1 << k)) k++;
		d ^= t;
		u = P[u][k];
	}
	return u;
}

ll getW(int u,int d) {
	if(!d) return val[u];
	int k = 0;
	ll w = val[u];
	while(d) {
		int t = LSOne(d);
		while(t != (1 << k)) k++;
		d ^= t;
		w = gcd(w,W[u][k]);
		u = P[u][k];
	}
	return w;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%lld",val + i + 1);
//	prArr(val+1,n,ll);
	loop(e,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfs(1,0);
	dfs_out[0] = n;

	int ans = 0;
	for(int u = 1;u <= n;u++) {
		int tmp = val[u]%mod;
		int d = depth[u]-1,v = u;
		ll g = val[u];
		while(d && v) {
			ll x = W[v][0];
			int k = 0;
			while((2 << k) <= d && W[v][k+1] == x) k++;
			int s = 1 << k;
			g = gcd(x,g);
			tmp = add(tmp,mul(g%mod,s));
			d -= s;
			v = P[v][k];
		}
		ans = add(ans,tmp);
//		cout << u << " " << tmp << endl;
	}
	printf("%d\n",ans);
	return 0;
}
#endif
