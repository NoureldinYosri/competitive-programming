#ifdef ACTIVE
#include <cstdio>

const int MAX = 2*100*1000 + 10;
int n;
int Y[MAX];
int deg[MAX];
int head[MAX],nxt[MAX],to[MAX],m;

void addedge(int a,int b) {
	int e = m++;
	nxt[e] = head[a];
	to[e] = b;
	head[a] = e;
	deg[a]++;
}

inline void addBiEdge(int a,int b) {
	addedge(a,b);
	addedge(b,a);
}

const int oo = 1 << 28;
int dp[MAX][2];

void dfs(int u,int p) {
	for(int i = 0;i < 2;i++) dp[u][i] = 0;
	if(Y[u] != -1) dp[u][Y[u]^1] = oo;

	for(int e = head[u];~e;e = nxt[e]) {
		int v = to[e];
		if(v == p) continue;
		dfs(v,u);
	}
	for(int c = 0;c < 2;c++) {
		for(int e = head[u];~e;e = nxt[e]) {
			int v = to[e];
			if(v == p) continue;
			int tmp = dp[v][c];
			if(dp[v][c^1] + 1 < tmp) tmp = dp[v][c^1] + 1;
			dp[u][c] += tmp;
			if(dp[u][c] > oo) dp[u][c] = oo;
		}
	}
}



int main(){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		m = 0;
		for(int i = 1;i <= n;i++) {
			scanf("%d",Y + i);
			head[i] = -1;
			deg[i] = 0;
		}
		for(int e = 0;e < n-1;e++) {
			int a,b; scanf("%d %d",&a,&b);
			addBiEdge(a,b);
		}
		dfs(1,0);
		int ans = (dp[1][0] < dp[1][1]) ? dp[1][0] : dp[1][1];
		printf("%d\n",ans);
	}
	return 0;
}
#endif
