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

int CTR[500],n,m,mod;
char buffer[600];
int C[600][3];
int dp[600][600];

int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

int mul(int a,int b){
	return (a * 1LL * b)%mod;
}

int solve(int a,int b){
	if(!a && !b) return 1;
	if(dp[a][b] != -1) return dp[a][b];
	dp[a][b] = 0;
	if(a && b) dp[a][b] = add(dp[a][b],mul(mul(a,b),solve(a,b - 1)));
	if(a >= 2) dp[a][b] = add(dp[a][b],mul(C[a][2],solve(a - 2,b)));
	if(b >= 2) dp[a][b] = add(dp[a][b],mul(C[b][2],solve(a + 2,b - 2)));
	return dp[a][b];
}

void init(){
	loop(i,600){
		C[i][0] = add(0,1);
		if(i) {
			C[i][1] = add(C[i - 1][0],C[i - 1][1]);
			C[i][2] = add(C[i - 1][1],C[i - 1][2]);
		}
	}
}

int main(){
	scanf("%d %d %d",&n,&m,&mod);
	init();
	loop(i,m) {
		scanf("%s",buffer);	
		loop(j,n) {
			CTR[j] += buffer[j] == '1';
		}
	}
	m = n - m;
	int x = 0,y = 0;
	loop(i,n) {
		if(CTR[i] > 2) {
			puts("0");
			return 0;
		}
		else if(CTR[i] == 1) x++;
		else if(CTR[i] == 0) y++;
	}
	if(x & 1) {
		puts("0");
		return 0;
	}
	memset(dp,-1,sizeof dp);
	cout << solve(x,y) << endl;
	cerr << solve(x,y) << endl;
	return 0;
}
