#pragma GCC optimize ("O3")
#include <cstdio>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)


const int MAX = 5 << 10,MAXLG = 13;
int A[MAX],n,K;
ll dp[MAX][MAX];
int ST[MAXLG][MAX],lg[MAX];

void build_sparse_table(){
	lg[0] = -1;
	for(int i = 1;i <= n;i++)
		lg[i] = lg[i-1] + (i == LSOne(i));
	
	loop(i,n) ST[0][i] = A[i];
	loop(k,MAXLG-1) loop(i,n){
		int j = i + (1 << k);
		if(j >= n) j = i;
		ST[k+1][i] = ST[k][i] | ST[k][j];
	}
}

int query(int s,int e){
	int l = lg[e-s+1];
	return ST[l][s] | ST[l][e-(1 << l)+1];
}

void solve(int q,int s,int e,int l,int r){
	if(s > e) return ;
	int m = (s + e) >> 1;
	int best_k = l;
	ll best = -(1LL << 60);
	for(int k = l;k <= r && k <= m;k++){
		ll tmp = query(k,m);
		tmp += k ? dp[q-1][k-1] : 0;
		if(tmp > best){
			best = tmp;
			best_k = k;
		}
	}
	dp[q][m] = best;
	solve(q,s,m-1,l,best_k);
	solve(q,m+1,e,best_k,r);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&K);
		loop(i,n) scanf("%d",A + i);
		build_sparse_table();
		loop(i,n) dp[0][i] = -(1LL << 60);
		for(int k = 1;k <= K;k++){
			solve(k,0,n-1,0,n-1);
		//	prArr(dp[k],n,ll);
		}
		printf("%lld\n",dp[K][n-1]);
		
	}
	return 0;
}
