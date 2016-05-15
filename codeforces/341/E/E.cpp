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

ll dp[100][100];
int CNT[10],n,k,x,b;
const ll mod = 1e9 + 7;

void mult(ll A[100][100],ll B[100][100],ll C[100][100]){
	ll Z[100][100];
	loop(i,x) loop(j,x){
		Z[i][j] = 0;
		loop(k,x) Z[i][j] = (Z[i][j] + A[i][k] * B[k][j])%mod;
	}
	loop(i,x) loop(j,x) C[i][j] = Z[i][j];
}

void EXP(ll A[100][100],int p){
	if(p == 0){
		loop(i,x) loop(j,x) A[i][j] = i == j;
		return;
	}
	ll B[100][100];
	mult(A,A,B);
	EXP(B,p >> 1);
	if(p & 1) mult(A,B,B);
	loop(i,x) loop(j,x) A[i][j] = B[i][j];
}

int main(){
	scanf("%d %d %d %d",&n,&b,&k,&x);
	loop(i,n){
		int a;
		scanf("%d",&a);
		CNT[a%x]++;
	}
	loop(i,x){
		loop(d,10){
			dp[(i * 10 + d)%x][i] += CNT[d];
		}
	}
	EXP(dp,b - 1);
	ll ans = 0;
	loop(i,10) ans = (ans + dp[k][i] * CNT[i])%mod;
	cout << ans << endl;
	return 0;
}
