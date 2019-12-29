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


const int MAX = 100000 + 10;

vi G[MAX];
int P[MAX];
int n; 
int color[MAX];
vi E[MAX];

void transform(int u,int p,vi *adj){
	if(color[u] == 0) adj = &E[u];
	for(int v : G[u]) if(v != p){
		if(color[v] == 0){
			adj->push_back(v);
			transform(v,u,&E[v]);
		}
		else transform(v,u,adj);
	}
}


const int MAXB = 9;
int f[MAX], g[MAX];
int dfs_in[MAX],dfs_out[MAX],euler[MAX],dfs_time;
int prefChild[MAX], subtreeSiz[MAX];

int trie[MAX*MAXB][2],trie_siz = 1;
int siz[MAX*MAXB],flag;
int val[MAX];
list<int> who[MAX*MAXB];

int insert(int x,int u,int cur = 0,int i = 0){
	if(i == MAXB){
		val[cur] = x;
		siz[cur] += who[cur].empty();
		who[cur].push_back(u);
		return sz(who[cur]) == 1;
	}
	int j = MAXB-i-1;
	int b = (x >> j) & 1;
	if(trie[cur][b] == -1) trie[cur][b] = trie_siz++;
	int ret = insert(x,u,trie[cur][b],i + 1);
	siz[cur] += ret;
	return ret;
}


int getMix(int cur = 0, int i = 0){
	if(cur == -1 || i == MAXB) return 0;
	int j = MAXB - i - 1;
	int zero = (flag >> j)&1, one = 1^zero;
	int E = 1 << j;
	
	int a = trie[cur][zero],b = trie[cur][one];
	//cout << a << " " << b << " " << siz[a] << " " << siz[b] << endl;

	if(a == -1 || siz[a] < E) return getMix(a, i+1);
	return (1 << j) | getMix(b, i + 1);
}



void dsu(int u,bool keep){
	f[u] = 0;
	for(int v : E[u]) if(v != prefChild[u]) {
		dsu(v,0);
		f[u] ^= g[v];
	}

	if(prefChild[u] != -1) {
		int v = prefChild[u];
		dsu(v,1);
		f[u] ^= g[v];
		int x = f[u] ^ g[v];
		flag ^= x;
	}
	insert(f[u]^flag,u);

	for(int v : E[u]) if(v != prefChild[u]){
		int x = f[u] ^ g[v];
		for(int i = dfs_in[v];i < dfs_out[v];i++){
			int t = euler[i];
			f[t] ^= x;
			insert(f[t]^flag,t);
		}
	}

	g[u] = getMix();

	
	if(!keep){
		for(int i = 0;i < trie_siz;i++){
			for(int t : who[i])
				f[t] = val[i]^flag;
			who[i].clear();
			siz[i] = 0;
			val[i] = 0;
			loop(j,2) trie[i][j] = -1;
		}
		flag = 0;
		trie_siz = 1;
/*		cout << "out of light " << u << endl;
		for(int i = dfs_in[u];i < dfs_out[u];i++){
			int t = euler[i];
			cout << make_pair(t,pi(f[t],g[t]));
		}
		cout << endl;
*/	}
/*	else {
		cout << "in heavy "  << u << endl;
		for(int i = 0;i < trie_siz;i++)
			for(int t : who[i])
				cout << make_pair(t,pi(val[t]^flag,g[t]));
		cout << endl;
	}
*/
}


void floodFill(int u){
	euler[dfs_time] = u;
	dfs_in[u] = dfs_time++;
	subtreeSiz[u] = 1;
	prefChild[u] = -1;
	
	for(int v : E[u]){
		floodFill(v);
		subtreeSiz[u] += subtreeSiz[v];
		if(prefChild[u] == -1 || subtreeSiz[prefChild[u]] < subtreeSiz[v])
			prefChild[u] = v;
	}
	dfs_out[u] = dfs_time;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	for(int u = 1;u <= n;u++) scanf("%d",color + u);
	loop(e,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	if(accumulate(color+1,color + n+1,0) == n){
		puts("-1");
		return 0;
	}
	
	transform(1,0,color[1] ? &E[0] : &E[1]);
	if(color[1] == 0) E[0].push_back(1);
	floodFill(0);
	
	memset(trie,-1,sizeof trie);
	
	dsu(0,0);
	if(f[0] == 0) puts("-1");
	else {
//		prArr(f,n+1,int);
//		int *C = color;
//		prArr(C,n+1,int);
		for(int u = 1;u <= n;u++)
			if(color[u] == 0 && f[u] == 0)
				printf("%d\n",u);
	}	
	return 0;
}
