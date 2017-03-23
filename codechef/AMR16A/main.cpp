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

const int mod = 1e9 + 7,MAX = 1024;
int C[MAX][MAX];
int L[MAX],R[MAX],siz[MAX];
int dp[MAX][MAX];
int is_left[MAX];

int add(int x,int y){
	x += y;
	if(x >= mod) x -= mod;
	return x;
}
int mul(int x,int y){
	return (x*1LL*y)%mod;
}

int f(int n,int s,int e,int k){
	int ret = 0;
	for(int i = s + 1;i <= n - e;i++){
		int tmp = (i == 1) ? 1 : C[i - 2][s - 1];
		tmp = mul(tmp,C[n - i][e]);
		tmp = mul(tmp,C[n - s - e - 1][k]);
		ret = add(ret,tmp);
		if(n == 5) cerr << i << " " << tmp << endl;
	}
//	if(n == 4) cerr << n << " " << s << " " << e << " " << k << " " << ret << endl;
	return ret;
}

int dfs(int u){
	if(!u) return 0;
	return siz[u] = dfs(L[u]) + dfs(R[u]) + 1;
}

int dfs(int u,int x){
	if(!u) return x == 0;
	if(siz[u] < x) return 0;
	int & ret = dp[u][x];
	if(ret != -1) return ret;
	ret = 0;
	int debug = u == 1;
	int m = siz[u] - x;
	if(is_left[u]){
		for(int i = 1;i <= m;i++){
			int more = x + m - i,less = i - 1;
			for(int j = 0;j <= more && j <= siz[L[u]];j++){
				ret += C[more][j] * C[less][siz[L[u]] - j] * dfs(L[u],j) * dfs(R[u],more - j);
			}
		}
	}
	else{
		for(int i = 1;i <= x;i++){
			int more = x - i,less = m + i - 1;
			for(int j = 0;j <= more && j <= siz[L[u]];j++){
				ret += C[more][j] * C[less][siz[L[u]] - j] * dfs(L[u],j) * dfs(R[u],more - j);
			}
		}
	}
//	if(debug) cerr << u << " " << x << " "  << ret << endl;
	return ret;
}

int main(){
	loop(i,1024){
		C[i][0] = C[i][i] = 1;
		range(j,1,i-1) C[i][j] = add(C[i - 1][j],C[i - 1][j - 1]);
	}
	int T; scanf("%d",&T);
	while(T--){
		int n; scanf("%d",&n);
		memset(is_left,0,sizeof is_left);
		range(i,1,n) scanf("%d %d",L + i,R + i),is_left[L[i]] = 1;
		memset(dp,-1,sizeof dp);
		dfs(1);
//		cerr << dfs(1) << endl;
		cerr << dfs(1,n) << endl;
//		break;
	}
	
	return 0;
}
