#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
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
const double PI = acos(-1);
using namespace std;

const int MAX = 2000 + 10,MAXN = MAX*MAX;
char G[MAX][MAX];
int D[MAX][MAX],nxt[MAXN],m,n;
int dx[] = {-1,0,1,0},dy[] = {0,1,0,-1};
string dir = "^>v<#";
vi adj[MAXN];
short vis[MAXN];

bool dfs(int u) {
	if (vis[u] == 1) return true;
	if (vis[u] == 2) return false;
	vis[u] = 1;
	if (nxt[u] != -1 && dfs(nxt[u])) return true;
	vis[u] = 2;
	return false;
}


int X,Y;

int getDepth(int u) {
	int mx1 = 0,mx2 = 0;
	for (int v : adj[u]) {
		int r = 1 + getDepth(v);
		if (r > mx2) mx2 = r;
		if (mx2 > mx1) {
			int t = mx1;
			mx1 = mx2;
			mx2 = t;
		}
	}
	X = mx1;
	Y = mx2;
	return mx1;;
}

int solve() {
	int N = n*m;
	for (int i = 0;i < N;i++)
		if (vis[i] == 0)
			if (dfs(i))
				return -1;

	for (int i = 0;i < N;i++) {
		if (nxt[i] != -1)
			adj[nxt[i]].push_back(i);

	}

	int mx = 0,ans = 0;
	for (int i = 0;i < N;i++)
		if (nxt[i] == -1) {
			getDepth(i);
			int D1 = X,D2 = Y;
			ans = max(ans,D1 + D2);
			ans = max(ans,2*D1 - 1);
			ans = max(ans,D1 + mx);
			if (D1 > mx) mx = D1;
		}

	return ans;
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&m,&n);
	for (int i = 0;i < m;i++) {
		scanf("%s",G[i]);
		for (int j = 0;j < n;j++) {
			D[i][j] = dir.find(G[i][j]);
		}
	}

	for (int i = 0;i < m;i++)
		for (int j = 0;j < n;j++){
			int d = D[i][j];
			nxt[i*n + j] = -1;
			if (d < 4) {
				int x = i + dx[d],y = j + dy[d];
				nxt[i*n + j] = x*n + y;
			}
		}

	printf("%d\n",solve());
	return 0;
}
