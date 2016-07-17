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
#define prS(A,n,t)	cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int dp[1 << 10],D[1 << 10],S[1 << 10],m,k;


int main(){
	scanf("%d %d",&m,&k);
	loop(i,m) scanf("%d",D + i);
	loop(i,m) scanf("%d",S + i);
	int a = 0,mx = -1;
	ll ans = 0;
	loop(i,m){
		a += S[i];
		mx = max(mx, S[i]);
		ans += D[i];
		if(a < D[i]){
			int tmp = D[i] - a;
			tmp = (tmp + mx - 1)/mx;
			ans += tmp *1LL* k;
			a += tmp * 1LL * mx;
		}
		a -= D[i];
	}
	printf("%lld", ans);
	return 0;
}
