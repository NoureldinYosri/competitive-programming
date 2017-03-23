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

int T[1 << 20],n;
int dp[1 << 20];

int get(int t){
	return int(upper_bound(T,T + n,t) - T) - 1;
}

int solve(int p){
	if(p < 0) return 0;
	if(dp[p] != -1) return dp[p];
	int & ret = dp[p];
	ret = 20 + solve(p - 1);
	ret = min(ret,50 + solve(get(T[p] - 90)));
	ret = min(ret,120 + solve(get(T[p] - 1440)));
	return ret;
}


int main(){
	scanf("%d",&n);
	int cover = 0,lst = 0,type = 0;	
	loop(i,n) scanf("%d",T + i);
	memset(dp,-1,sizeof dp);
	loop(i,n){
		printf("%d\n",max(0,solve(i) - lst));
		lst = solve(i);
	}
	
	return 0;
}
