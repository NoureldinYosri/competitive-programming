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

int n,k;
int C[500];

bool dp[502][502][502];

int main(){
	scanf("%d %d",&n,&k);
	loop(i,n) scanf("%d",C + i);
	vi ans ;
	loop(p,n + 1) loop(u,k + 1) loop(v,k + 1){
		dp[p][u][v] = 0;
		if(u == 0) {
			dp[p][u][v] = v == 0;
			continue;
		}
		if(!p) continue;
		dp[p][u][v] = dp[p - 1][u][v];
		if(u >= C[p - 1]) dp[p][u][v] |= dp[p - 1][u - C[p - 1]][v];
		if(u >= C[p - 1] && v >= C[p - 1]) dp[p][u][v] |= dp[p - 1][u - C[p - 1]][v - C[p - 1]];
	}	
	loop(i,k + 1) if(dp[n][k][i]) ans.pb(i);
	printf("%lu\n",sz(ans));
	for(int v  : ans) printf("%d ",v);
	return 0;
}
