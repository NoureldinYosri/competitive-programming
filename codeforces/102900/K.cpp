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

int n, m;
vi fr, to;
vector<vi> E[2], G;
char color[1 << 20];
vi dfs_low, dfs_num;
vector<bool> articulation_vertex;
vi ID, ST;
vector<array<vi, 2>> blocks;
vi dfs_in, dfs_out, euler, depth;
int dfs_time;

void clear(){
	fr.clear();
	to.clear();
	loop(c, 2) E[c].clear();
	G.clear();
	dfs_low.clear();
	dfs_num.clear();
	euler.clear();
	dfs_time = 0;
	articulation_vertex.clear();
	ID.clear();
	ST.clear();
	blocks.clear();
	dfs_in.clear();
	dfs_out.clear();
	depth.clear();
}

void extract(int u){
	bool change = false;
	blocks.emplace_back();
//	cerr << "calling from " << u << ": ";
	while(!ST.empty() && ST.back() != u){
		int v = ST.back(); ST.pop_back();
//		cerr << v << " ";
		blocks.back()[0].push_back(v);
		change = true;
	}
	if(u != -1 && change){
		blocks.back()[0].push_back(u);
	} 
	if(change){
//		cerr << endl;
		assert(blocks.back()[0].size() > 0);
	} else {
		blocks.pop_back();
	}
}

void dfsBi(int u, int p, int dfs_root) {
	dfs_low[u] = dfs_num[u] = dfs_time++;
	int t = 0;
	ST.push_back(u);
	for(int e : E[1][u]){
		int v = fr[e] + to[e] - u;
		if (dfs_num[v] == -1) {
			if (u == dfs_root) t++;
			dfsBi(v,u,dfs_root);
			if ((u != dfs_root && dfs_low[v] >= dfs_num[u]) || (u == dfs_root && t > 1)) {
				articulation_vertex[u] = true;
				extract(u);
			}
/*			if (dfs_low[v] > dfs_num[u]){
			//	printf(" Edge (%d, %d) is a bridge\n", u, v);
				extract(u);
			}
*/			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
			ST.push_back(u);
		}
		else if (v != p)
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
	}
	if(u == dfs_root && t > 1) articulation_vertex[u] = true;
}





void BlockCut(){
	dfs_num.resize(n);
	dfs_low.resize(n);
	fill(all(dfs_num), -1);
	dfs_time = 0;
	
	articulation_vertex.resize(n);
	fill(all(articulation_vertex), false);

	ST.clear();
	blocks.clear();
	dfsBi(0, -1, 0);
	extract(-1);
	
	ID.resize(n);
	fill(all(ID), -1);
	int z = sz(blocks);
	loop(i, z){
		sort(all(blocks[i][0]));
//		cerr << "B[" << i << "] = ";
		for(int u : blocks[i][0]) {
			ID[u] = i;
//			cerr << u << " ";
		}
//		cerr << endl;
			
	}
	loop(i, n) if(articulation_vertex[i]) {
//		cerr << "C[" << z << "] = " << i << endl;
		ID[i] = z++;
	}
	G.clear();
	G.resize(z);
	
	loop(i, sz(blocks)){
		for(int u : blocks[i][0]) if(articulation_vertex[u]){
			G[i].push_back(ID[u]);
			G[ID[u]].push_back(i);
		}
	}
	for(auto & V : G){
		sort(all(V));
		V.resize(unique(all(V)) - V.begin());
	}
/*	loop(i, sz(G)) {
		for(int j : G[i])
			if(i < j) cerr << i << " " << j << endl;
	}
*/
}



void dfs(int u, int p, int d){
	dfs_in[u] = sz(euler);
	depth[u] = d;
	euler.push_back(u);
	for(int v : G[u]) if(v != p) {
		dfs(v, u, d + 1);
		euler.push_back(u);
	}
	dfs_out[u] = sz(euler) - 1;
}

vector<vi> sparse_table;
vi lg;

auto cmp = [](const int & a, const int & b){
	return depth[a] < depth[b];
};

void buildTable(){
	lg.resize(sz(euler) + 5);
	lg[0] = -1;
	for(int i = 1; i < sz(lg); i++)
		lg[i] = lg[i - 1] + (i == LSOne(i));
	sparse_table.clear();
	int B = lg[sz(euler)] + 1;
	sparse_table.resize(sz(euler), vi(B));
	loop(i, sz(euler)) sparse_table[i][0] = euler[i];
	loop(k, B - 1) loop(i, sz(euler)){
		int j = i + (1 << k);
		if(j >= sz(euler)) j = i;
		sparse_table[i][k + 1] = min(sparse_table[i][k], sparse_table[j][k], cmp);
	}
}

int lca(int a, int b){
	a = dfs_in[a];
	b = dfs_in[b];
	if(a > b) swap(a, b);
	int l = lg[b - a + 1];
	return min(sparse_table[a][l], sparse_table[b - (1 << l) + 1][l], cmp);
}

bool check(int a, int b, int u){
	if(a == b) return true;
	if(dfs_in[a] <= dfs_in[b] && dfs_in[b] <= dfs_out[a]) return true;
	if(!articulation_vertex[u]) return false;
	int p = lca(a, b);
//	cerr << "for " << a << " " << b << " lca is " << p << " looking for " << u<< endl;
	if(p < sz(blocks)) {
//		print(blocks[p][0], int);
		return binary_search(all(blocks[p][0]), u);
	}
	return false;
}

bool solve(){
	BlockCut();
	int z = sz(G);
	dfs_in.resize(z);
	dfs_out.resize(z);
//	print(ID, int);
	depth.resize(z);
	dfs(ID[0], -1, 0);
//	print(euler, int);
	buildTable();
	for(int u = 0; u < n; u++) if(ID[u] != -1) {
		for(int e : E[0][u]){
			int v = fr[e] + to[e] - u;
			if(ID[v] == -1) continue;
			int a = ID[u], b = ID[v];
//				cerr << "checking " << pi(u, v) << " which are " << pi(a, b) << endl;
			if(check(a, b, u)) {
				return true;
			}
		}
	}
	return false;
}

void tc(){
	scanf("%d %d %s", &n, &m, color);
	loop(c, 2){
		E[c].clear();
		E[c].resize(n);
	}
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
	
		fr.push_back(a);
		to.push_back(b);
		
		int t = color[a] != color[b];
		E[t][a].push_back(e);
		E[t][b].push_back(e);			
	}
	
	
	if(solve()){
		puts("yes");
	} else {
		puts("no");
	}
	clear();
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
