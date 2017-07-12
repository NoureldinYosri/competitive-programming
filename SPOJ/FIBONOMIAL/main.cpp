#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int dim = 3,mod = 1000000007;

void mul(int A[dim][dim],int B[dim][dim]){
	int C[dim][dim] = {0};
	loop(i,dim) loop(j,dim) loop(k,dim){
		C[i][j] += (A[i][k] * 1LL * B[k][j])%mod;
		if(C[i][j] >= mod) C[i][j] -= mod;
	}
	loop(i,dim) loop(j,dim) A[i][j] = C[i][j];
}

void make_eye(int A[dim][dim]){
	loop(i,dim) loop(j,dim) A[i][j] = i==j;
}

void EXP(int A[dim][dim],ll power){
	if(!power) return make_eye(A);
	int B[dim][dim] = {0};make_eye(B);
	for(;power > 1;power >>= 1){
		if(power & 1) mul(B,A);
		mul(A,A);
	}
	mul(A,B);
}


int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	int T; scanf("%d",&T);
	while(T--){
		ll n,y; scanf("%lld %lld",&n,&y);
		int x = y % mod,x2 = (x*1LL*x)%mod;
		int A[dim][dim] = {{1,x,x2},{0,x,x2},{0,1,0}};
		int B [dim]= {(x + x2)%mod,x2,x};
		int ans = 0;
		if(n == 0) ans = 0;
		else if(n == 1) ans = x;
		else {
			EXP(A,n-2);
			loop(i,dim) {
				ans += (A[0][i] * 1LL * B[i])%mod;
				if(ans >= mod) ans -= mod;
			}
		}
//		cerr << ans << endl;
		printf("%d\n",ans);
	}
	return 0;
}
