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

const int mod = 1000000007,MAXK = 128,MAXLG = 32;
int A[MAXK],B[MAXK],C[MAXK];
int R[MAXLG][MAXK][MAXK],n;


int ax;

#define add(a,b) (ax=(a)+(b),ax -= (ax >= mod)?mod:0,ax += (ax < 0)?mod:0)
#define mul(a,b) ((a)*(ll)(b))%mod

void bf(int A[MAXK][MAXK],int B[MAXK][MAXK],int C[MAXK][MAXK],int n) {
	static int D[MAXK][MAXK];
	ll v ;
	loop(i,n) loop(j,n) {
		D[i][j] = 0;
		loop(k,n) {
			v = A[i][k] * (ll)B[k][j];
			D[i][j] += v % mod;
			if(D[i][j] >= mod) D[i][j] -= mod;
		}
	}
	loop(i,n) loop(j,n) C[i][j] = D[i][j];
}

void MatAdd(int A[MAXK][MAXK],int B[MAXK][MAXK],int C[MAXK][MAXK],int n) {
	static int D[MAXK][MAXK];
	loop(i,n) loop(j,n) D[i][j] = add(A[i][j],B[i][j]);
	loop(i,n) loop(j,n) C[i][j] = D[i][j];
}
void MatSub(int A[MAXK][MAXK],int B[MAXK][MAXK],int C[MAXK][MAXK],int n) {
	static int D[MAXK][MAXK];
	loop(i,n) loop(j,n) D[i][j] = add(A[i][j],-B[i][j]);
	loop(i,n) loop(j,n) C[i][j] = D[i][j];
}

void MatMul(int A[MAXK][MAXK],int B[MAXK][MAXK],int C[MAXK][MAXK],int n) {
	if(n <= 2) return bf(A,B,C,n);
	assert(n == LSOne(n));
	static int aux1[MAXK][MAXK];
	static int aux2[MAXK][MAXK];
	int m = n/2;
	int AA[2][2][MAXK][MAXK],BB[2][2][MAXK][MAXK];
	loop(a,2) loop(b,2) loop(i,m) loop(j,m) {
		AA[a][b][i][j] = A[i + a*m][j + b*m];
		BB[a][b][i][j] = B[i + a*m][j + b*m];
	}
	int M[7][MAXK][MAXK];
	MatAdd(AA[0][0],AA[1][1],aux1,m);
	MatAdd(BB[0][0],BB[1][1],aux2,m);
	MatMul(aux1,aux2,M[0],m);

	MatAdd(AA[1][0],AA[1][1],aux1,m);
	MatMul(aux1,BB[0][0],M[1],m);

	MatSub(BB[0][1],BB[1][1],aux1,m);
	MatMul(A[1][1],)
}

inline void makeEye(int A[MAXK][MAXK]) {
	loop(i,n) loop(j,n) A[i][j] = i == j;
}

void vecMul(int A[MAXK][MAXK],int V[MAXK]) {
	static int aux[MAXK];
	loop(i,n) {
		aux[i] = 0;
		loop(j,n) aux[i] = add(aux[i],mul(A[i][j],V[j]));
	}
	loop(i,n) V[i] = aux[i];
}

map<int,int> lg;

int F(int e,int V[MAXK]) {
	if(e <= n) return 1;
	loop(i,n) V[i] = 1;
	e -= n;
	for(;e > 0;e ^= LSOne(e))
			vecMul(R[lg[LSOne(e)]+1],V);
	int ret = V[0];
	return ret;
}
class testException: public exception{
	  virtual const char* what() const throw()
	  {
	    return "singular matrix";
	  }
};

int powmod(int a,int p) {
	if(p <= 0) return 1;
	int b = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) b = mul(a,b);
		a = mul(a,a);
	}
	return mul(a,b);
}
int inv(int a) {
	return powmod(a,mod - 2);
}

void Gauss(int A[MAXK][MAXK],int B[MAXK],int X[MAXK]) {
	int P[MAXK];
	loop(i,n) P[i] = i;
	for(int pivot = 0;pivot < n;pivot++) {
		int tr = -1;
		for(int r = pivot;r < n;r++)
			if(A[r][pivot]) {
				tr = r;
				break;
			}
		if(tr == -1) throw testException();
		if(pivot != tr){
			for(int c = 0;c < n;c++)
				swap(A[pivot][c],A[tr][c]);
			swap(B[pivot],B[tr]);
			swap(P[pivot],P[tr]);
		}

		int m = inv(A[pivot][pivot]);
		for(int c = pivot;c < n;c++)
			A[pivot][c] = mul(A[pivot][c],m);
		B[pivot] = mul(B[pivot],m);

		for(int r = pivot+1;r < n;r++){
			m = A[r][pivot];
			for(int c = pivot;c < n;c++)
				A[r][c] = add(A[r][c],-mul(A[pivot][c],m));
			B[r] = add(B[r],-mul(m,B[pivot]));
		}
	}
	int Y[MAXK];
	for(int row = n-1;row >= 0;row--) {
		Y[row] = B[row];
		for(int i = row+1;i < n;i++)
			Y[row] = add(Y[row],-mul(A[row][i],Y[i]));
	}
	loop(i,n) X[i] = Y[P[i]];
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	loop(i,MAXLG) lg[1 << i] = i;
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	loop(i,n) scanf("%d",B + i);
	makeEye(R[0]);
	loop(i,n) R[1][0][i] = A[i];
	for(int r = 1;r < n;r++)
		R[1][r][r-1] = 1;
	for(int i = 1;i+1 < MAXLG;i++)
		MatMul(R[i],R[i],R[i + 1]);


	int bk = 2*max(B[n-1],n) + 1;
	int BB[MAXK];
	int AA[MAXK][MAXK];
	int aux[MAXK];
	BB[0] = F(bk + 1,aux);
	int VV[MAXK][MAXK];
	for(int j = 0;j < n;j++){
		int V[MAXK];
		AA[0][j] = F(bk+1-B[j],V);
		loop(k,n) VV[k][j] = V[k];
	}

	for(int r = 1;r < n;r++) {
		MatMul(R[1],VV,VV);
		loop(j,n) AA[r][j] = VV[0][j];
		vecMul(R[1],aux);
		BB[r] = aux[0];
	}

	int X[MAXK];
	Gauss(AA,BB,X);
	loop(i,n) printf("%d%c",X[i]," \n"[i==n-1]);

	return 0;
}
