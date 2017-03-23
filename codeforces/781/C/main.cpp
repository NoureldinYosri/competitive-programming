#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 200'010;
vi G[MAX];
int vis[MAX],n,m,k;
int ord[MAX << 2],dfs_time;
deque<int> path[MAX];
int cnt[MAX];
int deg[MAX];

void dfs(int u){
	vis[u] = 1;
	ord[dfs_time++] = u;
	for(int v : G[u]) if(!vis[v]) {
		dfs(v);
		ord[dfs_time++] = u;
	}	
}

int main(){
	scanf("%d %d %d",&n,&m,&k);
	loop(i,m){
		int a,b ; scanf("%d %d",&a,&b);
		if(a == b) continue;
		G[a].pb(b);
		G[b].pb(a);
	}
	range(i,1,n) {
		sort(all(G[i]));
		G[i].resize(unique(all(G[i])) - G[i].begin());
	}
	dfs(1);
	assert(dfs_time <= 2*n);

	int len = (2*n + k - 1)/k;
	for(int i = 0,k = 0;i < dfs_time;k++){
		int l = -1;
		for(;sz(path[k]) < len && i < dfs_time;){
			path[k].pb(ord[i]);
			l = ord[i++];
			cnt[l]++;
			while(cnt[path[k].front()] > 1) {
				cnt[path[k].front()]--;
				path[k].pop_front();
			}
		}
		for(int u : path[k]) cnt[u] = 0;
	}
	for(int i = 0;i < k;i++) {
		if(path[i].empty()) path[i].pb(1);
		printf("%d",sz(path[i]));
		for(int u : path[i]) printf(" %d",u);
		puts("");
	}
	return 0;
}
