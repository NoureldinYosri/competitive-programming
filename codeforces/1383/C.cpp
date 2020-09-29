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


const int MAX = 1 << 20; 
char A[MAX], B[MAX];
int n;

vi G[20], R[20], who[20], CG[20];
vi ord;
bool vis[20];
int id[20];

void dfs(int u, vi *adj){
	if(vis[u]) return;
	vis[u] = 1;
	for(int v : adj[u]) dfs(v, adj);
	ord.pb(u);
}
int dfs(int u, int i){
	if(vis[u]) return 0;
	id[u] = i;
	vis[u] = 1;
	who[i].pb(u);
	int ret = 1;
	for(int v : R[u]) ret += dfs(v, i);
	return ret;
}


int solve(){
	loop(i, 20) G[i].clear(), R[i].clear();
	vi aux(20, 0);
	loop(i, n) {
		int a = A[i] - 'a', b = B[i] - 'a';
		if(a == b) continue;
		aux[a] |= 1 << b;
	}
	loop(i, 20){
		loop(j, 20) if((aux[i] >> j) & 1){
			G[i].pb(j);
			R[j].pb(i);
			cerr << (char)(i + 'a') << " " << (char)(j + 'a') << endl;
		}
	}

	ord.clear();
	memset(vis, 0, sizeof vis);
	loop(i, 20) id[i] = i;
	loop(i, 20) dfs(i, G);
	reverse(all(ord));
	int m = 0, ans = 0;
	memset(vis, 0, sizeof vis);
	for(int i : ord) {
		who[m].clear();
		CG[m].clear();
		int s = dfs(i, m);
		if(s > 1) ans += s;
		m++;
	}
	loop(i, m){
		int msk = 0;
		for(int x : who[i]){
			for(int y : G[x]){
				int j = id[y];
				if(i == j) continue;
				msk |= 1 << j;
			}
		}
		loop(j, m) if((msk >> j) & 1) {
			CG[i].pb(j);
			cerr << i << " " << j << endl;
		}
	}
	
	memset(vis, 0, sizeof vis);
	ord.clear();
	loop(i, m) dfs(i, CG);
	
	vi msks(m, 0);
	
	for(int i : ord){
		for(int j : CG[i]){
			if(!((msks[i] >> j) & 1))
				ans++;
			msks[i] |= 1 << j;
			msks[i] |= msks[j];
		}
	}

	return ans;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %s %s", &n, A, B);
		printf("%d\n", solve());
	}
	return 0;
}
