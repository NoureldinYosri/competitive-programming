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

const int mod = 1e9 + 7;
const int dim = 16;

int add(int a,int b){
	a += b;
	if (a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a,int b){
	return (a*1LL*b)%mod;
}

void mult(int A[dim][dim],int B[dim][dim],int R[dim][dim]){
	int C[dim][dim] = {0};
	loop(i,dim) loop(j,dim) loop(k,dim) C[i][j] = add(C[i][j],mul(A[i][k],B[k][j]));
	loop(i,dim) loop(j,dim) R[i][j] = C[i][j];
}

void make_eye(int A[dim][dim]){
	loop(i,dim) loop(j,dim) A[i][j] = i==j;
}

void EXP(int A[dim][dim],ll p){
	if(!p) return make_eye(A);
	int B[dim][dim]; make_eye(B);
	for(;p > 1;p >>= 1){
		if(p & 1) mult(A,B,B);
		mult(A,A,A);
	}
	mult(A,B,A);
}

void build(int A[dim][dim],int c){
	loop(i,dim) loop(j,dim) A[i][j] = 0;
	loop(i,dim) {
		if(i <= c) A[i][i] = 1;
	}
	loop(i,dim) {
		if(i+1 <= c && i+1 < dim) A[i][i+1] = 1;
	}
	loop(i,dim) {
		if(i <= c && i) A[i][i - 1] = 1;
	}
}

void prMatrix(int A[dim][dim]){
	loop(i,dim) {prArr(A[i],dim,int);}
	cerr << "====================" << endl;
}

void vecMul(int A[dim][dim],int V[dim]){
	int R[dim] = {0};
	loop(i,dim) loop(j,dim) R[i] = add(R[i],mul(A[i][j],V[j]));
	loop(i,dim) V[i] = R[i];
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int n; ll k;
	scanf("%d %lld",&n,&k);
	int res[dim] = {0}; res[0] = 1;
	loop(i,n){
		ll a,b; int c;
		scanf("%lld %lld %d",&a,&b,&c);
		if(a > k) break;
		int A[dim][dim];
		build(A,c);
		EXP(A,min(b,k) - a);
		vecMul(A,res);
	}
	printf("%d\n",res[0]);
	return 0;
}
