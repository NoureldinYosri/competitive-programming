#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

const int MAXN = 300 + 10;
int D[MAXN];

void build(int l,int r,int d,int *A){
	if(l > r) return;
	int x = min_element(A + l,A + r + 1) - A;
	D[x] = d;
	build(l,x-1,d+1,A);
	build(x+1,r,d+1,A);
}


void bf(int n,int K){
	int A[10];
	loop(i,n) A[i] = i;
	vector<vi> ans(n*(n-1)/2 + 1,vi(n,0));
	do{
		build(0,n-1,1,A);
		int k = 0;
		for(int i = 0;i < n;i++)
			for(int j = 0;j < i;j++)
				k += A[j] > A[i];
		loop(i,n) ans[k][i] += D[i];
	}while(next_permutation(A,A + n));
	for(int k = 0;k < sz(ans);k++){
		if(k != K && K >= 0) continue;
		cout << fixed << setw(2) << k << ":";
		loop(i,n) printf(" %6d",ans[k][i]);
		cout << endl;
	}
/*	int i = 0;
	if(i < n){
		for(int k = 0;k < sz(ans);k++)
			printf("%6d ",ans[k][i]);
		puts("");
	}
	*/
}

int dp[MAXN][MAXN];
int Fact[MAXN];
int C[MAXN][MAXN];
int mod;

int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a,int b){
	return (a*(ll)b)%mod;
}

void init(){
	Fact[0] = 1;
	for(int i = 1;i < MAXN;i++)
		Fact[i] = mul(Fact[i-1],i);
		
	for(int n = 0;n < MAXN;n++){
		C[n][0] = C[n][n] = 1;
		for(int k = 1;k < n;k++)
			C[n][k] = add(C[n-1][k],C[n-1][k-1]);
	}
}


int getCount(int n,int k){
	if(k == 0) return 1;
	if(k < 0) return 0;
	int ret = 0;
	for(int i = 0;i < n;i++)
		ret += getCount(n-1,k - i);
	return ret;
}

int solve(int i,int n,int K,int d){
	if(K < 0) return 0;

	for(int j = 0;j < n;j++){
		if(j < i) res += solve(i-1,n-1,K - j,d+1);
		else if(i == j) res += d*getCount(n-1,K - j);
		else res += solve(i,n-1,K - j,d);
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	
	for(int k = 0;k <= 10;k++){
		for(int i = 1;i <= 10;i++)
			bf(i,k);
		cout << string(50,'-') << endl;
	}
	return 0;
}
