#include <bits/stdc++.h>
#define loop(i,n) for(ll i = 0;i < (n);i++)
#define range(i,a,b) for(ll i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((ll)A.size())
#define vi vector<ll>
#define vl vector<long>
#define vd vector<double>
#define vp vector<pair<ll,ll> >
#define ll long long
#define pi pair<ll,ll>
#define poll pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define prll(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const ll mod = 1e9 + 7;

ll O[200][200],n;
ll A[200];

void multiply(ll A[200][200],ll B[200][200],ll C[200][200]){
	ll Z[200][200];
	loop(i,n) loop(j,n){
		Z[i][j] = 0;
		loop(k,n) Z[i][j] = (Z[i][j] + A[i][k]*1LL*B[k][j])%mod;
	}
	loop(i,n) loop(j,n) C[i][j] = Z[i][j];
}

void EXP(ll M[200][200],ll p){
	while(p > 1){
		if(p & 1) multiply(M,O,O);
		multiply(M,M,M);
		p >>= 1;
	}
	multiply(M,O,M);
}

int main(){
	ll M[200][200]; ll k;
	scanf("%I64d %I64d",&n,&k);
	if(k == 1){
		printf("%I64d\n",n);
		return 0;
	}
	loop(i,n) scanf("%I64d",A + i),O[i][i] = 1;
	loop(i,n) loop(j,n) M[i][j] = popcnt(A[i]^A[j])%3 == 0;
	EXP(M,k - 1);
	ll ans = 0;
	loop(i,n) loop(j,n){
		ans += M[i][j];
		ans %= mod;
	}
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
