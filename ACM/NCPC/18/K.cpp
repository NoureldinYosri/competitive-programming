#ifdef ACTIVE
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

const int mod = 1e9 + 7,MAX = 2500 + 10;

vi G[MAX];
int C[MAX][MAX];

int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a,int b) {
	return (a*(ll)b)%mod;
}
void init(){
	for(int n = 0;n < MAX;n++) {
		C[n][0] = C[n][n] = 1;
		for(int k = 1;k < n;k++)
			C[n][k] = add(C[n-1][k],C[n-1][k-1]);
	}
}

int dp[MAX][MAX];
int f[MAX];
int solve(int u,int k) {
	int & ret = dp[u][k];
	if(ret != -1) return ret;
	ret = k - (u != 0);
	for(int v : G[u])
		ret = mul(ret,solve(v,k));
	return ret;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	init();
	int n,K; cin >> n >> K;
	for(int u = 1;u < n;u++) {
		int p; cin >> p;
		G[p].push_back(u);
	}
	memset(dp,-1,sizeof dp);
	for(int k = 1;k <= K;k++){
		f[k] = solve(0,k);
		for(int i = 1;i < k;i++)
			f[k] = add(f[k],-mul(f[i],C[k][i]));
	}
//	prArr(f,K+1,int);
	cout << f[K] << endl;
	return 0;
}
#endif
