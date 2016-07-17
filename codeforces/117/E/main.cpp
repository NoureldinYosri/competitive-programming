#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

const int mod = 1e9 + 7;
int n,l;
int A[100][2];
int dp[3000][100][2];

vector<pi> G[100][2];
void pre(){
	loop(i,n) {
		loop(j,n) if(i != j) {
			if(A[i][1] == A[j][0]) G[i][0].pb(mp(j,0));
			if(A[i][1] == A[j][1] && A[j][0] != A[j][1]) G[i][0].pb(mp(j,1));
			if(A[i][0] == A[j][0]) G[i][1].pb(mp(j,0));
			if(A[i][0] == A[j][1] && A[j][0] != A[j][1]) G[i][1].pb(mp(j,1));
		} 
	}
}

ll solve(int p,int q,int c){
	//cerr << p << " " << q << " " << c << endl;
	if(dp[p][q][c] != -1) return dp[p][q][c];
	int h = A[q][c];	
	if(p + h >= l) return p + h == l;
	dp[p][q][c] = 0;
	for(auto e : G[q][c]) dp[p][q][c] = (dp[p][q][c] + solve(p + h,e.xx,e.yy))%mod;
//	cerr << p << " " << q << " " << c << " " << dp[p][q][c] << endl;
	return dp[p][q][c];
}

int main(){
	scanf("%d %d",&n,&l);
	fill(&dp[0][0][0],&dp[l][0][0],-1);
	loop(i,n) scanf("%d %d",&A[i][0],&A[i][1]);
	pre();
	ll ans = 0;
	loop(i,n) {
		ans = (ans + solve(0,i,0))%mod;
		if(A[i][0] != A[i][1]) ans = (ans + solve(0,i,1)) % mod;
	//	cerr << solve(0,i,0) << " " << solve(0,i,1) << endl;
	}
	cout << ans << endl;
	cerr << ans << endl;	
	return 0;
}
