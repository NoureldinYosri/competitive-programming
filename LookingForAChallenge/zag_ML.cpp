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
vi to, nxt, head, rev_head;
vi ID, SCC;
vector<bool> vis;
list<int> ord;
vi town, pref, suff;


int Not(int x){
	return x^1;
}

void add_implication(int a, int b){
	int e = sz(to);
	to.pb(b);
	nxt.pb(head[a]);
	head[a] = e;
	
	e = sz(to);
	to.pb(a);
	nxt.pb(rev_head[b]);
	rev_head[b] = e;
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


void dfs(int u){
	vis[u] = 1;
	for(int e = head[u]; ~e; e = nxt[e]) {
		int v = to[e];
		if(!vis[v]) dfs(v);
	}
	ord.pb(u);
}


void dfs(int u, int q){
	cerr << u << " ";
	SCC[u] = q;
	vis[u] = 1;
	for(int e = rev_head[u]; ~e; e = nxt[e]) {
		int v = to[e];
		if(!vis[v]) dfs(v, q);
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &m, &k);
	head.resize(2*n, -1);
	rev_head.resize(2*n, -1);
	ID.resize(2*n, -1);
	SCC.resize(2*n, -1);
	vis.resize(2*n, false);
	
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
				rev_head.pb(-1);
				SCC.pb(-1);
				ID.pb(-1);
				vis.pb(false);				
			}
		}
		for(int i = 0;i < sz(pref); i++){
			add_or(Not(2*town[i]), pref[i]);
			if(i) add_or(Not(pref[i-1]), pref[i]);
		}
		for(int i = sz(suff)-1; i >= 0;i--){
			add_or(Not(2*town[i]), suff[i]);
			if(i+1 < sz(suff)) add_or(Not(suff[i+1]), suff[i]);
		}
		for(int i = 0; i + 1 < sz(pref); i++)
			add_xor(pref[i], suff[i+1]);

	}
	
	
	
	for(int i = 0; i < offset; i++)
		if(!vis[i])
			dfs(i);
	reverse(all(ord));
	fill(all(vis), false);
	int q = 0;
	for(int u : ord) if(!vis[u]) {
		cerr << q << ": ";
		dfs(u, q++);
		cerr << endl;
	}
	for(int i = 0; i < offset; i ++)
		if(SCC[i] == SCC[Not(i)]){
			puts("NIE");
			return 0;
		}
	puts("TAK");
	vp res;
	loop(i, n) {
		vis[i] = SCC[2*i] > SCC[2*i+1];
		cerr << i+1 << ": " << SCC[2*i] << " " << SCC[2*i+1] << " " << vis[i] << endl;
	}
	loop(i, n) if(vis[i]) {
		SCC[ID[i]] = i+1;
		cerr << "use " << i+1 << " for " << ID[i] << endl;
	}
	loop(i, k) printf("%d ", SCC[i]);
	puts("");
	return 0;
}
