#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int A[1 << 20];
int dp[1 << 20][4];

bool can(int i,int j,int k){
	if(j + k == 4) return 1;
	if(A[i + 1] <= A[i]) return 0;
	int dis = A[i + 1] - A[i];
	return (k + 1)*10 >= dis;
}

int main(){
	int T,n;
	scanf("%d",&T); //T = 1;
	loop(t,T){
		scanf("%d",&n);
		loop(i,n) scanf("%d",A + i);
		loop(i,n + 1) loop(j,4) dp[i][j] = 1 << 29;
		A[n] = INT_MAX; dp[n][1] = 0;
		for(int i = n - 1;i >= 0;i--){
			for(int j = 0;j < 4;j++){
				if(j == 0) dp[i][j] = dp[i + 1][1];
				else{
					for(int k = 0;k <= 4 - j;k++){
						if(can(i,j,k)) dp[i][j] = min(dp[i][j],k + dp[i + 1][(j + k + 1)%4]);
					}
				}
			}
		}
		printf("Case #%d: %d\n",t + 1,dp[0][1]);
	}	
	return 0;
}
