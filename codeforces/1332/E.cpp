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
 
const int mod = 998244353;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}
 
const int M = 2;
 
void mul(int A[M][M], int B[M][M], int C[M][M]){
	static int Z[M][M];
	loop(i, M) loop(j, M) {
		Z[i][j] = 0;
		loop(k, M) Z[i][j] = add(Z[i][j], mul(A[i][k], B[k][j]));
	}
	loop(i, M) loop(j, M) C[i][j] = Z[i][j];
}
 
void make_eye(int A[M][M]){
	loop(i, M) loop(j, M) A[i][j] = i==j;
}
 
void EXP(int A[M][M], ll p){
	if(!p) return make_eye(A);
	int B[M][M]; make_eye(B);
	for(; p > 1; p >>= 1){
		if(p&1) mul(A, B, B);
		mul(A, A, A);
	}
	mul(A, B, A);
}
 
void get_cnt(int n, int *f){
	f[0] = n/2;
	f[1] = n - f[0];
}
 
int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	ll n, m, L, R; cin >> n >> m >> L  >> R;
	int fR[2], fL[2], cnt[2];
	get_cnt(R, fR);
	get_cnt(L-1, fL);
	loop(i, 2) cnt[i] = fR[i] - fL[i];
	int A[2][2] = {{cnt[0], cnt[1]}, {cnt[1], cnt[0]}};
/*	loop(i, 2){
		prArr(A[i], 2, int);
	}
	prArr(cnt, 2, int);
*/	EXP(A, n*m);
/*	loop(i, 2){
		prArr(A[i], 2, int);
	}
*/
	int ans = A[0][0];
	if((n&1)&&(m&1)) ans = add(ans, A[0][1]);
	cout << ans << endl;
	return 0;
}
