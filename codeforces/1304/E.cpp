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

const int MAX = 1 << 20, MAXLG = 20;
vi G[MAX];
int dfs_in[MAX], dfs_out[MAX], dfs_time, depth[MAX], euler[MAX];
int ST[MAX][MAXLG], lg[MAX], n;

void dfs(int u, int p){
	depth[u] = depth[p] + 1;
	dfs_in[u] = dfs_time;
	euler[dfs_time++] = u;
	for(int v : G[u]) if (v != p){
		dfs(v, u);
		euler[dfs_time++] = u;
	}
	dfs_out[u] = dfs_time;
}

int argmin(int a, int b){
	return (depth[a] < depth[b]) ? a : b;
}
void buildST(){
	loop(i, dfs_time) ST[i][0] = euler[i];
	loop(k , MAXLG-1){
		loop(i, dfs_time){
			int j = i + (1 << k);
			if(j >= dfs_time) j = i;
			ST[i][k+1] = argmin(ST[i][k], ST[j][k]);
		}
	}
	lg[0] = -1; 
	for(int i = 1;i <= dfs_time;i++)
		lg[i] = lg[i-1] + (i == LSOne(i));
}

int lca(int a, int b){
	a = dfs_in[a], b = dfs_in[b];
	if(a > b) swap(a, b);
	int l = lg[b-a+1];
	return argmin(ST[a][l], ST[b-(1 << l)+1][l]);
}

int dist(int a, int b){
	return depth[a] + depth[b] - 2*depth[lca(a, b)];
}

bool cond(int d, int k){
	return d <= k && (k-d)%2 == 0;
}

bool in_subtree(int u, int p){
	return dfs_in[p] <= dfs_in[u] && dfs_in[u] < dfs_out[p];
}

int get_entery(int u, int x, int y){
	int p = lca(x, y);
	
	if(!in_subtree(u, p)) return p;
		
	int a = lca(u, x);
	int b = lca(u, y);
	
	if(depth[a] < depth[b]) return b;
	else return a;
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
	dfs(1, 0);
	buildST();
	
	int m; scanf("%d", &m);
	loop(q, m){
		int x, y, a, b, k;
		scanf("%d %d", &x, &y);
		scanf("%d %d", &a, &b);
		scanf("%d", &k);
		if(cond(dist(a, b), k)) puts("YES");
		else {
			int e_a = get_entery(a, x, y);
			int e_b = get_entery(b, x, y);
			int d1 = dist(a, e_a);
			int d2 = dist(b, e_b);
			int L = dist(x, y) + 1;
			int l1 = dist(e_a, e_b);
			int l2 = L - l1;
			bool y = 0;
			loop(q, 10){
				if(cond(d1+d2+q*L+l1, k)) y = 1;
				if(cond(d1+d2+q*L+l2, k)) y = 1;	
				if(y) break;
			}
			puts(y ? "YES" : "NO");
		}
	}
	return 0;
}
