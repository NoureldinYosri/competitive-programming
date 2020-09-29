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


const int mod = 998244353;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}

const int MAX = 300*1000 + 10;
int n;
list<int> G[MAX];
int dp_no_root[MAX];
int dp_root_is[MAX];
int dp_root_nis[MAX];
int tot[MAX];

int dp[MAX][2][2];

int dfs(int u, int p, int used_parent_edge, int in_is){
	int & ret = dp[u][used_parent_edge][in_is];
	if(ret != -1) return ret;
	
	ret = 1;
	int aux = 1;
	for(int v : G[u]) if(v != p){
		int tmp = 0, tmp2 = 0;
		loop(use_edge, 2) loop(use_node, 2) {
			if(use_edge && in_is && use_node) continue;
			int val = dfs(v, u, use_edge, use_node);
			tmp = add(tmp, val);
			if(!use_edge) tmp2 = add(tmp2, val);
		}
		ret = mul(ret, tmp);
		aux = mul(aux, tmp2);
	}
	
	if(!used_parent_edge && in_is) ret = add(ret, -aux);

	return ret;
}




int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(e, n-1){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	memset(dp, -1, sizeof dp);
	int ans = 0;
	loop(in_is, 2) ans = add(ans, dfs(1, 0, 0, in_is));
	ans = add(ans, -1);
	cout << ans << endl;
	return 0;
}
