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

const int mod = 1000'000'007,MAX = 100'010;
int dp[MAX][3];
int LIM[3],n;
int sum[3];

int main(){
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		memset(sum,0,sizeof sum);
		loop(i,3) scanf("%d",LIM + i);
		range(i,1,n){
			loop(j,3) {
				dp[i][j] = sum[j] + (i <= LIM[j]);				
				if(dp[i][j] >= mod) dp[i][j] -= mod;
			}
			loop(j,3){
				int o = (j == 2) ? 0 : (j + 1);
				sum[j] += dp[i][o]; sum[j] -= (sum[j] >= mod) ? mod : 0;
				sum[j] += dp[i][3-j-o]; sum[j] -= (sum[j] >= mod) ? mod : 0;
			}
		//	prArr(dp[i],3,int);
		//	prArr(sum,3,int);
			loop(j,3){
				int o = (j == 2) ? 0 : (j + 1);
				if(i>LIM[j]){
					sum[j] -= dp[i-LIM[j]][o]; sum[j] += (sum[j] < 0) ? mod : 0;
					sum[j] -= dp[i-LIM[j]][3-j-o]; sum[j] += (sum[j] < 0) ? mod : 0;
				}
			}
		//	prArr(sum,3,int);
		}
		int ans = 0;
		loop(i,3) {
			ans += dp[n][i];
			if(ans >= mod) ans -= mod;
		}
		printf("%d\n",ans);
	//	cerr << ans << endl;
	}	
	
	
	return 0;
}
