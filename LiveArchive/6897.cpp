#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;


vi G[1 << 11];
int degree[1 << 11],N,K;
int vis[1 << 11];

int f(queue<int> & q){
	for(int i = 0,L = sz(q);i < L;i++){
		if(degree[q.front()] < K) return 1;
		q.push(q.front());
		q.pop();
	}
	return 0;
}

int dfs(int u){
	int ans = 1;
	vis[u] = 1;
	for(int v : G[u])
		if(degree[v] >= K && !vis[v])
			ans += dfs(v);
	return ans;
}

int f(){
	queue<int> q;
	loop(i,N) q.push(i);
	while(f(q)){
		for(int i = 0,L = sz(q);i < L;i++){
			int u = q.front(); q.pop();
			if(degree[u] >= K) q.push(u);
			else{
				for(int v : G[u]) --degree[v];
			}
		}
	}
	fill(vis,vis + N,0);
	int ans = 0;
	for(;!q.empty();q.pop()){
		if(!vis[q.front()]){
			ans += dfs(q.front());
		}
	}
	return ans;
}

int main(){
	int T,M;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d",&N,&K,&M);
		loop(i,N) G[i].clear();
		fill(degree,degree + N,0);
		while(M--){
			int a,b;
			scanf("%d %d",&a,&b);
			--a,--b;
			G[a].pb(b);
			G[b].pb(a);
			degree[a]++;
			degree[b]++;
		}
		printf("%d\n",f());
	}
	return 0;
}
