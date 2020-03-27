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

const int mods[] = {10337, 3};
int invs[2][10337];

int add(int a, int b, int m){
	a += b;
	if(a >= m) a -= m;
	if(a < 0) a += m;
	return a;
}
int mul(int a, int b, int m){
	return (a*(ll)b)%m;
}
int inv(int a, int m){
	int c = m == mods[1];
	return invs[c][a%m];
}
void init(){
	loop(c, 2){
		invs[c][1] = 1;
		for(int i = 2; i < mods[c]; i++){
			invs[c][i] = add(mods[c], -mul(mods[c]/i, invs[c][mods[c]%i], mods[c]), mods[c]);
			assert(mul(i, invs[c][i], mods[c]) == 1);
		}
	}
}

const int MAXN = 111;
int n, m;
vector<pair<int, pi>> E;
vi G[MAXN];
int id[MAXN], W[MAXN];

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}
void join(int a, int b){
	a = find(a), b = find(b);
	if(a == b) return ;
	if(W[a] < W[b]) swap(a, b);
	W[a] += W[b];
	id[b] = a;
}

int visID[MAXN], name[MAXN], visNum;
vi V;

int get_name(int u){
	if(visID[u] == visNum) return name[u];
	name[u] = sz(V);
	V.pb(u);
	visID[u] = visNum;
	return name[u];
}

void dfs(int u){
	if(visID[u] == visNum) return;
	get_name(u);
	for(int v : G[u]){
		dfs(v);
	}
}

int get_det(vector<vi> & L, int c){
	if(sz(L) <= 1) return 1;
	L.pop_back();
	for(auto & row : L)  row.pop_back();
/*	for(auto row : L){
		print(row, int);
	}
	cerr << endl;
*/	for(auto & row : L){
		for(auto & x : row)
			x = (x%mods[c] + mods[c])%mods[c];
	}
	int det = 1;
	for(int pivot = 0; pivot < sz(L); pivot++){
		int row = pivot, t = row;
		while(t < sz(L) && L[t][pivot] == 0) t++;
		if(t == sz(L)) return 0;
		if(t != row) {
			swap(L[t], L[row]);
			det = mul(det, mods[c]-1, mods[c]);
		}
		int w = inv(L[row][pivot], mods[c]);
		det = mul(det, L[row][pivot], mods[c]);
		for(int k = pivot;k < sz(L); k++)
			L[row][k] = mul(L[row][k], w, mods[c]);
		
		for(int r = row+1; r < sz(L); r++){
			w = L[r][pivot];
			for(int k = pivot; k < sz(L);k++){
				L[r][k] = add(L[r][k], -mul(L[row][k], w, mods[c]), mods[c]);
			}
		}
/*		for(auto R : L){
			print(R, int);
		}
		cerr << endl;
*/	}
/*	for(auto row : L){
		print(row, int);
	}
*/	
//	cout << "det is " << det << endl;
	return det;
}

int solve(vector<pi> & E, int c){
	static vi subgraph;
//	static map<pi, int> cnt;
	subgraph.clear();
//	cnt.clear();
	for(auto p : E){
		int a = p.first, b = p.second;
		subgraph.pb(a);
		subgraph.pb(b);
//		pi q(min(a, b), max(a, b));
//		cnt[q]++;
	}
	sort(all(subgraph));
	subgraph.resize(unique(all(subgraph)) - subgraph.begin());
	for(int v : subgraph) G[v].clear();

	for(auto p : E){
		int a = p.first, b = p.second;
		G[a].pb(b);
		G[b].pb(a);
	}
	
	int ret = 1;
	visNum++;
	for(int u : subgraph) if(visID[u] != visNum){
		V.clear();
		dfs(u);
//		print(V, int);
		vector<vi> L(sz(V), vi(sz(V), 0));
		for(int v : V){
			int i = get_name(v);
//			print(G[v], int);
			L[i][i] = sz(G[v]);
			for(int k : G[v])
				L[i][get_name(k)] --;
			
		}
		
		ret = mul(ret, get_det(L, c), mods[c]);
	}
	
	
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	scanf("%d %d", &n, &m);
	loop(e, m){
		int a, b, c; scanf("%d %d %d", &a, &b, &c);
		E.emplace_back(c, pi(a, b));
	}
	for(int i = 1; i <= n;i++) id[i] = i, W[i] = 1;
	sort(all(E));
	int ans[] = {1, 1};
	vector<pi> subE;
	for(int i = 0; i < m; ){
		int j = i;
		subE.clear();
		while(j < m && E[i].first == E[j].first){
			int a = E[j].second.first, b = E[j].second.second;
			if(find(a) != find(b))
				subE.emplace_back(find(a), find(b));
			j++;
		}
		loop(k, 2) ans[k] = mul(ans[k], solve(subE, k), mods[k]);
	
		for(; i < j; i++){
			int a = E[i].second.first, b = E[i].second.second;
			join(a, b);
		}
	}
	int M = 31011;
	int res = 0;
	loop(i, 2){
		int tmp = mul(mods[i^1], inv(mods[i^1], mods[i]), M);
		tmp = mul(ans[i], tmp, M);
		res = add(res, tmp, M);
	}
	cout << res << endl;
	return 0;
}
