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

const int MAX = 310;
ll dp[MAX][MAX];
int n,m;
const ll oo = 1LL << 60;
ll C[MAX][MAX];

ll solve(int day,int cnt){
	if(day == n) return 0;
	if(dp[day][cnt] != -1) return dp[day][cnt];
	dp[day][cnt] = oo;	
	loop(i,m+1) if(cnt + i) dp[day][cnt] = min(dp[day][cnt],solve(day+1,cnt + i - 1) + C[day][i-1] + (i*1LL*i));
	return dp[day][cnt];
}

int main(){
	int T; scanf("%d",&T);
	range(t,1,T){
		memset(dp,-1,sizeof dp);
		scanf("%d %d",&n,&m);
		loop(i,n) {
			loop(j,m) scanf("%lld",&C[i][j]);
			sort(C[i],C[i] + m);
			loop(j,m) C[i][j] += j ? C[i][j - 1] : 0;
		}
		printf("Case #%d: %lld\n",t,solve(0,0));
	}	
	
	
	return 0;
}
