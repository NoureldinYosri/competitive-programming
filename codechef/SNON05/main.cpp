#pragma GCC optimize ("O3")
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
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
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

const int MAXn = 12;
const int MAXN = 12*12*4;
const int mod = 1000007;
int dx[8]={-2,-2,2,2,-1,-1,1,1};
int dy[8]={1,-1,1,-1,2,-2,2,-2};
int N;
void mul(int A[MAXN][MAXN],int B[MAXN][MAXN]){
	int C[MAXN][MAXN] = {0};
	loop(i,N) loop(j,N) loop(k,N) {
		C[i][j] += (A[i][k] * 1LL * B[k][j])%mod;
		if(C[i][j] >= mod) C[i][j] -= mod;
	}
	loop(i,N) loop(j,N) A[i][j] = C[i][j];
}

void make_eye(int A[MAXN][MAXN]){
	loop(i,N) loop(j,N) A[i][j] = i == j;
}

void EXP(int A[MAXN][MAXN],ll K){
	if(!K) return make_eye(A);
	int B[MAXN][MAXN]; make_eye(B);
	for(;K;K >>= 1){
		if(K & 1) mul(B,A);
		mul(A,A);
	}
	mul(A,B);
}


void build(int A[MAXN][MAXN],int n){
	N = 4*n*n;
	int m = 2*n;
	loop(i,N) loop(j,N) A[i][j] = 0;
	loop(i,N){
		int x = i/m,y = i%m;
		loop(k,8){
			int nx = x + dx[k],ny = y + dy[k];
			if(nx < 0 || nx >= m || ny < 0 || ny >= m) continue;
			A[i][nx*m + ny] = 1;
		}
	}
}

void add(int A[MAXN][MAXN],int B[MAXN][MAXN]){
	loop(i,N) loop(j,N) {
		A[i][j] += B[i][j];
		if(A[i][j] >= mod) A[i][j] -= mod;
	}
}

void compute(int A[MAXN][MAXN],ll K){
	if(K == 0) return make_eye(A);
	// I + A + ... + A^K
	int B[MAXN][MAXN],C[MAXN][MAXN];
	loop(i,N) loop(j,N) B[i][j] = A[i][j];
	if(K & 1){
		// I + A
		// I + A + A^2 + A^3
		compute(A,K >> 1);
		EXP(B,(K + 1) >> 1);
		make_eye(C);
		add(B,C);
		mul(A,B);
	}
	else{
		compute(A,K - 1);
		EXP(B,K);
		add(A,B);
	}
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	range(n,1,12){
		int B[MAXN][MAXN],A[MAXN][MAXN];
		build(A,n);
		int m = 2*n;
		for(int k = 0;k <= 5;k++){
			make_eye(B);
			mul(B,A);
			compute(B,k);
			int ans = B[0][0];
			ans += B[0][m-1];
			ans += B[0][(m - 1)*m];
			ans += B[0][m*m - 1];
			cerr << ans << " " ;
		}
		cerr << endl;
	}

	return 0;
}
