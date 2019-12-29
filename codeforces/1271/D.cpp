#pragma GCC optimize ("O3")
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
using namespace std;


const int MAXN = 5000 + 10,MAXM = 300*1000 + 10;
vi ord[MAXN];
int A[MAXN],B[MAXN],C[MAXN];
int n,m,k;
bool vis[MAXN][MAXN];
ll dp[MAXN][MAXN];
int P[MAXN];
const ll oo = 1LL << 60;

ll solve(int u,int army){
	if(army < 0) return -oo;
	if(u == n) return 0;
	ll & ret = dp[u][army];
	if(vis[u][army]) return ret;
	vis[u][army] = 1;
	ret = -oo;
	if(army >= A[u]){
		ll val = 0;
		int narmy = army + B[u];
		ret = solve(u+1,narmy);
		for(int v : ord[u]){
			val += C[v];
			narmy--;
			ret = max(ret,solve(u+1,narmy) + val); 
		}
	}
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d",&n,&m,&k);
	loop(i,n) {
		scanf("%d %d %d",A + i,B + i,C + i);
		P[i] = i;
	}
	loop(e,m){
		int u,v; scanf("%d %d",&u,&v);
		u--,v--;
		P[v] = max(P[v],u);
	}
	loop(i,n) ord[P[i]].push_back(i);
	loop(i,n){
		sort(all(ord[i]),[](const int & a,const int & b){
			return C[a] > C[b];
		});
	}
	
	ll ans = solve(0,k);
	if(ans < 0) ans = -1;
	cout << ans << endl;
	return 0;
}
