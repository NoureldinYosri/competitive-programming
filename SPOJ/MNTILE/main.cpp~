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

ll dp[25][1 << 22];
int n,m;
int M,N,T;
vi A,B;

ll solve(){
	loop(S,1 << n) dp[0][S] = 0;
	loop(k,m + 1) dp[k][0] = 1;
	range(k,1,m) range(msk,1,((1 << n) - 1)){
		dp[k][msk] = dp[k - 1][msk];
		loop(i,n) {
			int x1 = A[i]/N,y1 = A[i]%N;
			int x2 = B[k]/N,y2 = B[k]%N;
			bool c = msk & (1 << i);
			c &= abs(x1 - x2) + abs(y1 - y2) == 1;
			if(c) dp[k][msk] += dp[k - 1][msk ^ (1 << i)];
		}
	}
	return dp[m][(1 << n) - 1];
}

int main(){
	scanf("%d",&T);
	while(T--){
		A.clear(),B.clear();
		scanf("%d %d",&M,&N);
		m = n = 0;
		int c = 0;
		loop(i,M) {
			loop(j,N){
				if(c) m++,A.pb(i*N + j);
				else n++,B.pb(i*N + j);
				c ^= 1; 
			}
		} 
		printf("%lld\n",solve());
	}		
	return 0;
}
