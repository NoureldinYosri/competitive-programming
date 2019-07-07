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
int deg[MAX],n;
vi G[MAX];
vi *leafs[MAX];
vp ans;

void dfs(int u,int p) {
	if(deg[u] == 1) {
		leafs[u] = new vi({u});
		return;
	}

	leafs[u] = 0;
	for(int v : G[u])
		if(v != p) {
			dfs(v,u);
			if(leafs[u] == 0 || leafs[v]->size() > leafs[u]->size())
				leafs[u] = leafs[v];
		}
	for(int v : G[u]) if(v != p && leafs[u] != leafs[v]) {
		while(!leafs[u]->empty() && !leafs[v]->empty() && leafs[u]->size() + leafs[v]->size() > 2) {
			int a = leafs[u]->back(); leafs[u]->pop_back();
			int b = leafs[v]->back(); leafs[v]->pop_back();
			ans.push_back(mp(a,b));
		}
		for(int t : *leafs[v])
			leafs[u]->push_back(t);
	}
	if(p == 0) {
		while(leafs[u]->size() > 1) {
			int a = leafs[u]->back(); leafs[u]->pop_back();
			int b = leafs[u]->back(); leafs[u]->pop_back();
			ans.push_back(mp(a,b));
		}
		if(!leafs[u]->empty()) {
			int a = leafs[u]->back(); leafs[u]->pop_back();
			int b = ans.back().xx;
			ans.push_back(mp(a,b));
		}
	}
}

int main(int argc,char **argv){
	freopen("kingdom.in","r",stdin);
#ifndef HOME
	freopen("kingdom.out","w",stdout);
#endif
	scanf("%d",&n);
	loop(i,n-1) {
		int a,b; scanf("%d %d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
		deg[a]++;
		deg[b]++;
	}
	if(n == 2) puts("1\n1 2");
	else {
		int root = 1;
		for(root = 1;root <= n && deg[root] == 1;root++);
		assert(root <= n);
		dfs(root,0);
		printf("%d\n",sz(ans));
		for(auto p : ans)
			printf("%d %d\n",p.xx,p.yy);
	}
	return 0;
}
