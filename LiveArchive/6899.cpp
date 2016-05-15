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

#define white 0
#define grey 1
#define black 2

int vis[1 << 10],nxt[1 << 10],in[1 << 10];

int dfs(int u){
	if(vis[u]) return vis[u] == grey;
	vis[u] = grey;
	int ans = dfs(nxt[u]);
	vis[u] = black;
	return ans;
}

int main(){
	int T,N;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		fill(vis,vis + N,0);
		fill(in,in + N,0);
		loop(i,N) scanf("%d",nxt + i),nxt[i]--,in[nxt[i]]++;
		queue<int> q;
		loop(i,N) if(in[i] == 0) q.push(i);
		int ans = 0; 
		for(;!q.empty();q.pop()) ans += dfs(q.front());
		loop(i,N) if(vis[i] == white) ans += dfs(i);
		printf("%d\n",ans);
	}	
}
