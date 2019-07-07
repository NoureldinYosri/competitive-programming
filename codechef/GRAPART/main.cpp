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

const int MAX = 100*1000 + 10;
vi G[MAX],S[2];
int n;
vi U,V;
int depth[MAX];
vi children[MAX];

void dfs(int u,int p,int d) {
	S[d & 1].pb(u);
	depth[u] = d;
	children[u].clear();
	for(int v : G[u])
		if(v != p){
			dfs(v,u,d + 1);
			children[u].pb(v);
		}
	sort(all(children[u]),[](const int & a,const int & b) {
		return depth[a] < depth[b];
	});
}

void dfs(int u,int p,list<int> *path) {
	if(path != nullptr) {
		path->push_back(u);
		if(!children[u].empty()) {
			int v = children[u].back();
			children[u].pop_back();
			dfs(v,u,path);
		}
		for(int v : children[u])
			dfs(v,u,nullptr);
		return;
	}
	path = new list<int>();
	vi big;
	if(!children[u].empty()) {
		int v = children[u].back();
		children[u].pop_back();
		dfs(v,u,path);
	}
	reverse(path->begin(),path->end());
	path->push_back(u);
	if(!children[u].empty()) {
		int v = children[u].back();
		children[u].pop_back();
		dfs(v,u,path);
	}
	if(sz(U) > sz(V)) U.swap(V);
	int d = 0;
	for(int x : *path) {
		if(d%2 == 0) U.pb(x);
		else V.pb(x);
		d++;
	}
	list<int> aux = *path;
//	print(aux,int);
	for(int v : children[u])
		dfs(v,u,nullptr);
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		loop(i,n+1) G[i].clear();
		loop(i,2) S[i].clear();

		loop(e,n-1){
			int a,b; scanf("%d %d",&a,&b);
			G[a].pb(b);
			G[b].pb(a);
		}

		dfs(1,0,0);
		int k = 0;

		if(sz(S[0]) == sz(S[1])) {
			k = 1;
			U = S[0];
			V = S[1];
		}
		else {
			k = 2;
			U.clear();
			V.clear();
			dfs(1,0,nullptr);
		}
		assert(sz(U) == sz(V));
		assert(sz(U) + sz(V) == n);
		printf("%d\n",k);
		for(int i = 0;2*i < n;i++)
			printf("%d%c",U[i]," \n"[i==n/2-1]);
		for(int i = 0;2*i < n;i++)
			printf("%d%c",V[i]," \n"[i==n/2-1]);
	}
	return 0;
}
