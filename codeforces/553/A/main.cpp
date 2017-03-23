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

const int mod = 1e9 + 7;
int k,n,ans = 1;
int A[1000],F[1001],inv[1001],pref[1001];
int dp[1000][1001];

void mul(int & x,int y){
	x = (x * 1LL * y) % mod;
}

void add(int & x,int y){
	x += y;
	if(x >= mod) x -= mod;
}

int POW(int x,int y){
	if(!y) return 1;
	int z = 1;
	for(;y > 1;y >>= 1){
		if(y & 1) mul(z,x);
		mul(x,x);
	}
	mul(x,z);
	return x;
}

int C(int n,int k){
	if(n < k) return 0;
	int ret = F[n];
	mul(ret,inv[k]);
	mul(ret,inv[n - k]);
	return ret;
}

void init(){
	F[0] = inv[0] = 1;
	loop(i,1000) {
		F[i + 1] = F[i];
		mul(F[i + 1],i + 1);
		inv[i + 1] = POW(F[i + 1],mod - 2);
	}
	memset(dp,-1,sizeof dp);
}

int solve(int i,int r){
	if(i == k-1) return r < A[i];
	if(pref[i] + r > n) return 0;
	if(dp[i][r] != -1) return dp[i][r];
	int & ret = dp[i][r]; ret = 0;
	if(r >= A[i]-1) {
		ret = C(r,A[i] - 1);
		mul(ret,solve(i + 1,r - A[i] + 1));
	}
	add(ret,solve(i,r + 1));
	return ret;
}

int main(){
	cin >> k;
	loop(i,k) cin >> A[i],n += A[i],pref[i + 1] = pref[i] + A[i];
	init();	
	cout << solve(0,0) << endl;	
	return 0;
}
