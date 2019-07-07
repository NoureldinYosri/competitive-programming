#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
using namespace std;

const int MAX = 200*1000 + 10;
vi G[MAX];
int P[MAX],n;
bool dead[MAX];
int depth[MAX],RP[MAX];

void dfs(int u,int p) {
	depth[u] = depth[p] + 1;
	RP[u] = p;
	for(int v : G[u])
		if(v != p)
			dfs(v,u);
}

void answer(int u) {
	cout << "! " << u << endl;
	fflush(stdout);
	exit(0);
}

int ask(char c,int u) {
	cout << c << " " << u << endl;
	fflush(stdout);
	int res; cin >> res;
	if(res == -1) exit(0);
	return res;
}

int ask_d(int u) {
	static map<int,int> mem;
	if(mem.count(u)) return mem[u];
	int x = ask('d',u);
	if(x == 0) answer(u);
	return mem[u] = x;
}
int ask_s(int u) {
	static map<int,int> mem;
	if(mem.count(u)) return mem[u];
	return mem[u] = ask('s',u);
}


int siz[MAX],mx[MAX];

int floodfill(int u,int p) {
	siz[u] = 1;
	mx[u] = 0;
	P[u] = p;
	for(int v : G[u]) {
		if(v == p || dead[v]) continue;
		floodfill(v,u);
		siz[u] += siz[v];
		mx[u] = max(mx[u],siz[v]);
	}
	return siz[u];
}
int getCenteroid(int u,int p,int s) {
	mx[u] = max(mx[u],s - siz[u]);
	int c = u;
	for(int v : G[u]) {
		if(v == p || dead[v]) continue;
		int g = getCenteroid(v,u,s);
		if(mx[g] < mx[c])
			c = g;
	}
	return c;
}


int pick(){
	int root = -1;
//	cerr << "candidates" ;
	for(int u = 1;u <= n;u++){
		if(dead[u]) continue;
		root = u;
//		cerr << " " << u ;
	}
	assert(root != -1);
//	cerr << endl;
	int s = floodfill(root,0);
	return getCenteroid(root,0,s);
}

void trim(int u,int p) {
	dead[u] = 1;
//	cerr << "kill " << u << endl;
	for(int v : G[u]){
		if(v == p || dead[v]) continue;
		trim(v,u);
	}
}

void trimAns(int u,int p) {
	if(p) trim(p,u);
}

void trimChild(int p,int u) {
//	cerr << "trim child" << endl;
	trim(u,p);
}

bool trimMore(int u,int p,int d,int D) {
	bool ret = 0;
	if(d > D) {
		dead[u] = 1;
//		cerr << "kill " << u << " " << d << " vs " << D << endl;
	}
	if(d == D) ret = 1;
	for(int v : G[u]) {
		if(v == p) continue;
		ret |= trimMore(v,u,d+1,D);
	}
	if(!dead[u] && !ret) {
		dead[u] = 1;
//		cerr << "kill b " << u << endl;
	}
	return ret;
}
int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
	srand((unsigned ll)(new char()));
	scanf("%d",&n);
	loop(e,n-1) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	depth[0] = -1;
	dfs(1,0);
	int L = ask_d(1);
	trimMore(1,0,0,L);
	while(1) {
		int ctr = 0;
		int cand = 0;
//		prArr(dead+1,n,bool);
		for(int u = 1;u <= n;u++){
			if(!dead[u]) {
				cand = u;
				ctr++;
			}
		}
//		cerr << ctr << endl;
		if(ctr == 1) answer(cand);
		int u = pick();
		int d = ask_d(u);
		if(d + depth[u] == L) {
			int s = ask_s(u);
			trim(u,s);
		}
		else {
			trim(u,RP[u]);
		}
	}
	return 0;
}
