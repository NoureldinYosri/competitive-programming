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

const int MAXN = 5*100*1000 + 10;
int dfs_low[MAXN],dfs_num[MAXN],dfs_time;
vi E[MAXN];
int fr[MAXN],to[MAXN],isBridge[MAXN];
vp ans;
vp BE[MAXN];
vi V[MAXN];
int ID[MAXN];
set<int> SC[MAXN];

void dfsBi(int u,int p,int dfs_root) {
	dfs_low[u] = dfs_num[u] = dfs_time++;
	int t = 0;
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if (dfs_num[v] == -1) {
			if (u == dfs_root) t++;
			dfsBi(v,u,dfs_root);
			if (dfs_low[v] > dfs_num[u])
				isBridge[e] = 1;
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
		}
		else if (v != p)
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
	}
}

void init(){
	memset(dfs_num,-1,sizeof dfs_num);
	dfs_time = 0;
}

void floodFill(int u,int id) {
	ID[u] = id;
	V[id].push_back(u);
	for(int e : E[u]) if(!isBridge[e]){
		int v = fr[e] + to[e] - u;
		if(!ID[v])
			floodFill(v,id);
	}
}


int pointingUp[MAXN],Cycles[MAXN];

int getCycleCnt(int bu,int p){
	assert(!dfs_num[bu]);
	dfs_num[bu] = 1;
	int ret = sz(V[bu]) > 1;
	for(auto e : BE[bu]) {
		int v = e.yy,bv = ID[v];
		if(bv == p) continue;
		ret += getCycleCnt(bv,bu);
	}
	return ret;
}

void dfs(int bu,int p,int cycle_cnt) {
	Cycles[bu] = sz(V[bu]) > 1;
	for(auto e : BE[bu]) {
		int u = e.xx;
		int v = e.yy,bv = ID[v];
		if(bv == p) continue;
		dfs(bv,bu,cycle_cnt);
		int up = pointingUp[bv];
		int subCycles = Cycles[bv];

		if(!up && cycle_cnt==subCycles){
			pointingUp[bu]++;
			SC[bu].insert(bv);
			ans.push_back(mp(v,u));
		}

		Cycles[bu] += subCycles;
		pointingUp[bu] += pointingUp[bv];
	}
}

void dfs2(int bu,int p,int pointingDown) {
	pointingDown += pointingUp[bu];
	for(auto e : BE[bu]) {
		int u = e.xx;
		int v = e.yy,bv = ID[v];
		if(bv == p) continue;
		int subDown = pointingDown - pointingUp[bv] - SC[bu].count(bv);
		if(subDown==0 && Cycles[bv]==0){
			ans.push_back(mp(u,v));
			subDown++;
		}
		dfs2(bv,bu,subDown);
	}
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	init();
	int n,m;
	scanf("%d %d",&n,&m);
	loop(e,m) {
		scanf("%d %d",fr + e,to + e);
		E[fr[e]].push_back(e);
		E[to[e]].push_back(e);
	}
	for(int i = 1;i <= n;i++)
		if(dfs_num[i] == -1)
			dfsBi(i,0,i);

	int B = 0;
	for(int i = 1;i <= n;i++)
		if(!ID[i])
			floodFill(i,++B);

	for(int i = 1;i <= B;i++) {
		for(int u : V[i]) {
			for(int e : E[u]) {
				int v = fr[e] + to[e] - u;
				if(ID[v] != i)
					BE[i].push_back(mp(u,v));
			}
		}
	}
	memset(dfs_num,0,sizeof dfs_num);
	for(int i = 1;i <= B;i++)
		if(!dfs_num[i]) {
			int cycles = getCycleCnt(i,0);
			dfs(i,0,cycles);
			dfs2(i,0,0);
		}

	sort(all(ans));
	printf("%d\n",sz(ans));
	for(auto p : ans) printf("%d %d\n",p.xx,p.yy);

	return 0;
}
