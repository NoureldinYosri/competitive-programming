#pragma GCC optimize("O3")
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

const int mod = 1e9 + 7,MAX = 101;

int cnt[MAX],dp[MAX];

void make_eye(int A[MAX][MAX]){
	loop(i,MAX) loop(j,MAX) A[i][j] = i == j;
}

void make_aux(int A[MAX][MAX]){
	loop(i,MAX) {
		A[0][i] = i ? cnt[i] : 1;
		A[1][i] = i ? cnt[i] : 0;
	}
	loop(i,MAX){
		if(i <= 1) continue;
		loop(j,MAX) A[i][j] = 0;
		A[i][i-1] = 1;
	}
}

void mul(int A[MAX][MAX],int B[MAX][MAX]){
	int C[MAX][MAX] = {0};
	loop(i,MAX) loop(j,MAX) loop(k,MAX) {
		int tmp = (A[i][k] *1LL* B[k][j])%mod;
		C[i][j] += tmp;
		if(C[i][j] >= mod) C[i][j] -= mod;
	}
	loop(i,MAX) loop(j,MAX) A[i][j] = C[i][j];
}

void EXP(int A[MAX][MAX],int p){
	if(!p) return make_eye(A);
	int B[MAX][MAX]; make_eye(B);
	while(p > 1){
		if(p & 1) mul(B,A);
		mul(A,A);
		p >>= 1;
	}
	mul(A,B);
}

int solve(int x){
	if(!x) return 1;
	if(dp[x] != -1) return dp[x];
	dp[x] = 0;
	loop(i,MAX) if(i && i <= x) {
		dp[x] += (cnt[i] *1LL* solve(x - i))%mod;
		if(dp[x] >= mod) dp[x] -= mod;
	}
	return dp[x];
}

int main(){
	int n,x; scanf("%d %d",&n,&x);
	loop(i,n){
		int v; scanf("%d",&v);
		cnt[v]++;
	}
	memset(dp,-1,sizeof dp);
	loop(i,MAX) solve(i);
	int ans = 0;
	loop(i,min(x+1,MAX)) if(i) {
		ans += dp[i];
		if(ans >= mod) ans -= mod;
	}
	if(x > 100){
		int A[MAX][MAX]; 
		make_aux(A);
		EXP(A,x - 100);
		loop(i,100) dp[i] = dp[i + 1];
		dp[100] = ans;
		ans = 0;
		loop(i,101)  {
			int tmp = (A[0][i] * 1LL * dp[100 - i])%mod;
			ans += tmp;
			if(ans >= mod) ans -= mod;
		}
	}
	ans ++; if(ans >= mod) ans -= mod;
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
