#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
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

const int mod = 1e9 + 7;

ll EXP(int a,int b){
	if(b == 0) return 1;
	int t = 1;
	while(b > 1){
		if(b & 1) t = (t*1LL*a)%mod;
		a = (a*1LL*a)%mod;
		b >>= 1;
	}
	return (a*1LL*t)%mod;
}

void multiply(ll A[2][2],ll B[2][2]){
	ll Z[2][2];
	loop(i,2) loop(j,2){
		Z[i][j] = 0;
		loop(k,2) Z[i][j] = (Z[i][j] + A[i][k]*B[k][j])%mod;
	}
	loop(i,2) loop(j,2) B[i][j] = Z[i][j];
}

void EXP(ll A[2][2],int b){
	ll O[2][2] = {{1,0},{0,1}};
	if(b == 0){
		A[0][0] = 0;
		return;
	}
	while(b > 1){
		if(b & 1) multiply(A,O);
		multiply(A,A);
		b >>= 1;
	}
	multiply(O,A);
}


int main(){
	int k,n = 1; ll a;
	scanf("%d",&k);
	loop(i,k){
		scanf("%lld",&a);
		a %= mod - 1;
		n = (n*a)%(mod - 1);
	}
	if(n == 0) n = mod-1;
	ll b = EXP(2,n - 1),aa;
	if(n == 1) aa = 0;
	else if(n <= 3) aa = 1;
	else{
		ll B[2][2] = {{1,2},{1,0}};		
		EXP(B,n - 2);
		aa = B[0][0];
	}
	cerr << aa << " " << b << endl;
	printf("%lld/%lld\n",aa,b);
	return 0;
}
