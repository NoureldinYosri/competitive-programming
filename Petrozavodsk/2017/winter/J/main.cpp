#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
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
using namespace std;

const int MAXN = 200*1000,mod = 1e9 + 7;
int n,base;
int A[MAXN];
int freq[MAXN+1][20];


int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b){
	return (a*(ll)b)%mod;
}

const int DIM = 21;
int N;

void mul(int A[DIM][DIM],int B[DIM][DIM],int C[DIM][DIM]) {
	static int D[DIM][DIM];
	loop(i,N) loop(j,N) {
		D[i][j] = 0;
		loop(k,N) D[i][j] = add(D[i][j],mul(A[i][k],B[k][j]));
	}
	loop(i,N) loop(j,N) C[i][j] = D[i][j];
}

void makeI(int A[DIM][DIM]) {
	loop(i,N) loop(j,N) A[i][j] = i==j;
}

void EXP(int A[DIM][DIM],int p) {
	if(p <= 0) return makeI(A);
	static int B[DIM][DIM];
	makeI(B);
	for(;p > 1;p >>= 1) {
		if(p & 1) mul(A,B,B);
		mul(A,A,A);
	}
	mul(A,B,A);
}

void makeMatrix(int A[DIM][DIM],int x) {
	loop(i,N) loop(j,N) A[i][j] = 0;
	loop(i,base+1) A[i][i] ++;
	for(int i = 0;i < base;i++)
		A[(i+x)%base][i] ++;
	A[x][base] ++;
}

void mul(int A[DIM][DIM],int R[DIM]) {
	static int C[DIM];
	memset(C,0,sizeof C);
	loop(i,N) {
		C[i] = 0;
		loop(j,N) C[i] = add(C[i],mul(A[i][j],R[j]));
	}
	copy(C,C + N,R);
}

const int MAXP = 21;
int powers[20][MAXP][DIM][DIM];

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d",&n,&base);
	loop(i,n) {
		scanf("%d",A + i);
		A[i] %= base;
		copy(freq[i],freq[i+1],freq[i+1]);
		freq[i+1][A[i]]++;
	}
	N = base+1;

	for(int v = 0;v < base;v++) {
		makeI(powers[v][0]);
		makeMatrix(powers[v][1],v);
		for(int p = 1;p+1 < MAXP;p++)
			mul(powers[v][p],powers[v][p],powers[v][p+1]);
	}

	map<int,int> lg;
	loop(i,20) lg[1 << i] = i;

	int Q; scanf("%d",&Q);
	int R[DIM];

	while(Q--) {
		int l,r; scanf("%d %d",&l,&r);
		memset(R,0,sizeof R);
		R[base] = 1;
		loop(i,base) {
			int cnt = freq[r][i] - freq[l-1][i];
			while(cnt) {
				int x = LSOne(cnt);
				cnt ^= x;
				x = lg[x] + 1;
				mul(powers[i][x],R);
			}
		}

		int ans = add(R[0],1);

		printf("%d\n",ans);
	}
	return 0;
}
