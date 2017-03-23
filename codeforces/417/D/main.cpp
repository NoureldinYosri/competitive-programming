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


int n,m,b;
int can[100],req_mon[100],cost[100];
int ord[100];
ll dp[2][1 << 20];


int main(){
	scanf("%d %d %d",&n,&m,&b);
	loop(i,n){
		int q; scanf("%d %d %d",cost + i,req_mon + i,&q);
		while(q--){
			int x; scanf("%d",&x); x--;
			can[i] |= 1 << x;
		}
		ord[i] = i;
	}
	sort(ord,ord + n,[](const int  a,const int & b){
		return req_mon[a] < req_mon[b];
	});
	ll ans = 1LL << 60;
	fill(dp[0],dp[2],1LL << 60);
	dp[0][0] = 0;
	int one = 1,other = 0;
	loop(j,n){
		int i = ord[j];
		loop(msk,1 << m) dp[one][msk] = dp[other][msk];
		loop(msk,1 << m) dp[one][msk | can[i]] = min(dp[one][msk | can[i]],dp[other][msk] + cost[i]);
		ans = min(ans,dp[one][(1 << m) - 1] + req_mon[i] *1LL* b);
		swap(one,other);
	}
	if(ans >= (1LL << 60)) ans = -1;
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
