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

const int MAX = 1e6 + 1e2,MAXK = 21,MAXBLK = 100;
ll A[MAX]; int n;
ll dp[MAX];

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%lld",A + i);

	ll x = -(1LL << 61),y = x;
	loop(r,n){
		dp[r] = r ? dp[r - 1] : 0;
		dp[r] = max(dp[r],x + A[r]);
		dp[r] = max(dp[r],y - A[r]);
		x = max(x,(r ? dp[r - 1] : 0) - A[r]);
		y = max(y,(r ? dp[r - 1] : 0) + A[r]);
	}
	cerr << dp[n-1] << endl;
	cout << dp[n-1] << endl;
	return 0;
}
