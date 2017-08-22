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
#define popcnt(x) __builtin_popcount(x)
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

int n;
int X[2500],Y[2500];
double dp[2500][2500*2][2];
double dist[2500][2500];

double solve(int s,int e,int t){
	if(s >= e) return 0;
	if(s >= n)  s -= n,e -= n;
	double & ret = dp[s][e][t];
	if(ret == ret) return ret;
	ret = 0;
	int lead = (t == 0) ? s : e;
	int l = (t == 0) ? (s + 1) : s,r = (t == 0) ? e : (e - 1);

	double a = dist[lead%n][l%n] + solve(l,r,0);
	double b = dist[lead%n][r%n] + solve(l,r,1);
	ret = max(a,b);
	return ret;
}

void build(){
	for(int l = 1;l < n;l++){
		for(int s = n-1;s >= 0;s--){
			int e = s + l;
			if(e > n-1) continue;
			for(int t = 0;t < 2;t++){
				int lead = (t == 0) ? s : e;
				int l = (t == 0) ? (s + 1) : s,r = (t == 0) ? e : (e - 1);
				double a = dist[lead][l] + dp[l][r][0];
				double b = dist[lead][r] + dp[l][r][1];
				dp[s][e][t] = max(a,b);
			}
		}
	}

	for(int l = 1;l < n;l++){
		for(int s = n-1;s >= 0;s--){
			int e = s + l;
			for(int t = 0;t < 2;t++){
				int lead = (t == 0) ? s : e;
				int l = (t == 0) ? (s + 1) : s,r = (t == 0) ? e : (e - 1);
				double a = dist[lead%n][l%n] + (l >= n ? dp[l - n][r - n][0] : dp[l][r][0]);
				double b = dist[lead%n][r%n] + (l >= n ? dp[l - n][r - n][1] : dp[l][r][1]);
				dp[s][e][t] = max(a,b);
			}
		}
	}
}


int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",X + i,Y + i);
	loop(i,n) loop(j,n) dist[i][j] = hypot(X[i] + 0.0 - X[j],Y[i] + 0.0 - Y[j]);
	build();
	//memset(dp,-1,sizeof dp);
	double ans = 0;
	loop(pivot,n) ans = max(ans,solve(pivot,pivot + n-1,0));
	//double ans = solve();
	printf("%.18f\n",ans);
	//recon(0,n-1,0);
	return 0;
}
