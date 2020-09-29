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

int n, m, k;
vi to, nxt, head;
vi ID;
vi town, pref, suff;
vi dfs_in, dfs_low, ST, SCC;
int dfs_time, SCC_cnt;
vector<bool> inStack;

void tarjanSCC(int u) {
	dfs_in[u] = dfs_low[u] = dfs_time++;
	ST.pb(u);
	inStack[u] = true;
	for(int e = head[u]; ~e; e = nxt[e]) {
		int v = to[e];
		if (dfs_in[v] == -1) {
			tarjanSCC(v);
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
		else if (inStack[v]) {
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
	}
	if (dfs_low[u] == dfs_in[u]) {
		bool done = 0;
//		vi aux;
		while(!done){
			int v = ST.back();
			SCC[v] = SCC_cnt;
			ST.pop_back();
			done = v == u;
			inStack[v] = 0;
//			aux.pb(v);
		}
		SCC_cnt++;
//		print(aux, int);
	}
}


int Not(int x){
	return x^1;
}

void add_implication(int a, int b){
	int e = sz(to);
	to.pb(b);
	nxt.pb(head[a]);
	head[a] = e;
}

void add_or(int a, int b){
	add_implication(Not(a), b);
	add_implication(Not(b), a);
}

void add_xor(int a, int b){
	add_or(a, b);
	add_or(Not(a), Not(b));
}

void add_nand(int a, int b){
	add_or(Not(a), Not(b));
}




int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &m, &k);
	head.resize(2*n, -1);
	ID.resize(n, -1);
	
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		a--, b--;
		add_or(2*a, 2*b);
	}
	int offset = 2*n;
	loop(i, k){
		int g; scanf("%d", &g);
		town.clear();
		while(g--){
			int x; scanf("%d", &x);
			x--;
			ID[x] = i;
			town.pb(x);
		}
		pref.resize(sz(town));
		suff.resize(sz(town));
		for(int & x: pref) { 
			x = offset;
			offset += 2;
		}
		for(int & x: suff) {
			x = offset;
			offset += 2;
		}
		int tmp = sz(pref) + sz(suff);
		while(tmp--){
			loop(c, 2){
				head.pb(-1);
			}
		}
		for(int i = 0;i < sz(pref); i++){
//			add_or(Not(2*town[i]), pref[i]);
//			if(i) add_or(Not(pref[i-1]), pref[i]);
			
			add_implication(2*town[i], pref[i]);
			if(i) add_implication(pref[i-1], pref[i]);
		}
		for(int i = sz(suff)-1; i >= 0;i--){
			add_or(Not(2*town[i]), suff[i]);
			if(i+1 < sz(suff)) add_or(Not(suff[i+1]), suff[i]);
		}
		for(int i = 0; i + 1 < sz(pref); i++)
			add_xor(pref[i], suff[i+1]);

	}
	
	
	
	dfs_in.resize(offset, -1);
	dfs_low.resize(offset, -1);
	inStack.resize(offset, false);
	SCC.resize(offset, -1);
	
	vi ans(k);
	for(int i = 0; i < offset; i++)
		if(dfs_in[i] == -1){
			tarjanSCC(i);
			assert(ST.empty());
		}
	
	for(int i = 0; i < offset; i+= 2){
		if(SCC[i] == SCC[i+1]){
			puts("NIE");
			return 0;
		}
	}
	loop(i, n) if(SCC[i << 1] < SCC[(i << 1) | 1]){
		ans[ID[i]] = i+1;
	}
	puts("TAK");
	for(int x : ans) printf("%d ", x);
	puts("");
	return 0;
}
