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

const int MAX = 400*1000 + 10;
vi E[MAX];
int n, m;
int fr[MAX], to[MAX];
int id[MAX], dfs_num[MAX], dfs_low[MAX], dfs_time;
vi ST;
vector<vi> blocks;

void cut(int u){
	int k = sz(blocks);
	blocks.emplace_back();
	vi & V = blocks.back();
	while(!ST.empty() && ST.back() != u){
		int v = ST.back(); ST.pop_back();
		id[v] = k;
		V.pb(v);
	}
	sort(all(V));
	V.resize(unique(all(V)) - V.begin());
	if(V.empty()) blocks.pop_back();
//	else{
//		print(V, int);
//	}
}

void dfs(int u, int p){
	dfs_low[u] = dfs_num[u] = ++dfs_time;
	ST.pb(u);
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(dfs_num[v] == 0){
			fr[e] = u, to[e] = v;
			dfs(v, u);
			if(dfs_low[v] > dfs_num[u]){
//				cerr << u << " " << v << endl;
				cut(u);
			}
			else ST.pb(u);
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
		else if(v != p){
			if(dfs_num[v] < dfs_num[u]) {
				fr[e] = u, to[e] = v;
				dfs_low[u] = min(dfs_low[u], dfs_num[v]);				
			}
		}
	}
} 


void floodfill(int c, int prv){
	for(int u : blocks[c])
		for(int e : E[u]){
			int v = fr[e] + to[e] - u;
			int iv = id[v];
			if(iv == prv || iv == c) continue;
			fr[e] = v;
			to[e] = u;
			
			floodfill(iv, c); 
		}
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(e, m) {
		scanf("%d %d", fr + e, to + e);
		E[fr[e]].pb(e);
		E[to[e]].pb(e);
	}
	dfs(1, 0);
	cut(-1);
	
	int c = 0;
	loop(i, sz(blocks)) if(sz(blocks[i]) > sz(blocks[c])) c = i;
	floodfill(c, -1);
	
	printf("%d\n", sz(blocks[c]));
	loop(e, m) printf("%d %d\n", fr[e], to[e]);
	
	return 0;
}
