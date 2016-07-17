#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
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

int L,C,T,NC;
int P[26][1000];
int E[26][1000];
ll dp[26][1000];

ll solve(int c,int t){
	if(c == C) return abs(L - P[c][t]) + E[c][t];
	if(dp[c][t] != -1) return dp[c][t];
	dp[c][t] = 1LL << 60;	
	loop(i,T) dp[c][t] = min(dp[c][t],solve(c + 1,i) + abs(P[c][t] - P[c + 1][i]));
	return dp[c][t] += E[c][t];
}

int main(){
	scanf("%d",&NC);
	while(NC--){
		scanf("%d %d %d",&C,&T,&L);
		loop(i,C) loop(j,T) scanf("%d %d",&P[i + 1][j],&E[i + 1][j]);
		loop(i,C + 1) loop(j,T) dp[i][j] = -1;
		P[0][0] = E[0][0] = 0;
		cout << solve(0,0) << endl;
//		cerr << solve(0,0) << endl;
	}	
	return 0;
}
