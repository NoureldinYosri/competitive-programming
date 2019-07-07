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
#define prArr(A,n,t)  cerr << fixed << setprecision(3) << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
using namespace std;

typedef complex<long double> num;
const int MAXN = 1 << 20,mod = 1000*1000 + 7;
const double PI = acos(-1);
int N,M,K;
typedef num* poly;

poly getPoly(int & n) {
	n = K + 1;
	while(n != LSOne(n)) n++;
	poly P = new num[2*n];
	loop(i,n) P[i] = num(0.0,0.0);
	for(int i = 0;i <= M && i < n;i++)
		P[i] = num(1.0,0.0);
	return P;
}


void fft(poly P,int n,bool inv) {
	static num aux[1 << 20];
	for(int i = 1,j = 0;i+1 < n;i++) {
		for(int k = n >> 1;!(k & (j ^= k));k >>= 1);
		if(i < j) swap(P[i],P[j]);
	}
	for(int m = 1;m < n;m <<= 1) {
		double w = (1 - 2*inv)*PI/m;
		loop(i,m) aux[i] = polar(1.0,w*i);
		for(int i = 0;i < n;i += (m << 1)) {
			for(int j = 0;j < m;j++) {
				num a = P[i + j],b = P[i + j + m];
				P[i + j] = a + aux[j]*b;
				P[i + j + m] = a - aux[j]*b;
			}
		}
	}
	if(inv) {
		loop(i,n) P[i] /= n;
	}
}

num mul(num a,num b) {
	return a*b;
}

num raise(num x,int p){
	if(p == 0) return num(1.0,0.0);
	num y (1.0,0.0);
	for(;p > 1;p >>= 1) {
		if(p & 1) y = mul(y,x);
		x = mul(x,x);
	}
	return mul(x,y);
}


void make_eye(poly P,int n) {
	loop(i,n) P[i] = num(1.0*(i == 0),0.0);
}

void mul(poly A,poly B,int n) {
	static num aux[1 << 20];
	static num C[1 << 20];
	for(int i = 0;i < n;i++)
		A[i + n] = B[i + n] = 0;
//	prArr(A,2*n,num);
//	prArr(B,2*n,num);
	loop(i,2*n) aux[i] = B[i];
	fft(A,2*n,0);
	fft(aux,2*n,0);

	loop(i,2*n) C[i] = A[i]*aux[i];
	fft(C,2*n,1);
	loop(i,n) {
		A[i] = C[i];
		long double v = round(A[i].real());
		long double im = abs(A[i].imag());
		ll k = floor(v/mod);
		cerr << A[i] << " : " <<  v  << " " << im << " " << (im < 1e-9) << " -> " << v-k*mod << endl;
		assert(im < 1e-9);
		A[i] = v - k * mod;
	}
//	prArr(C,2*n,num);
}

void EXP(poly P,int n,int p) {
	if(p == 0) return make_eye(P,n);
	static num aux[1 << 20];
	make_eye(aux,n);
	for(;p > 1;p >>= 1) {
		cerr << "p is " << p << endl;
		if(p & 1) {
			mul(aux,P,n);
		}
		mul(P,P,n);
	}
	mul(P,aux,n);
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	cin >> N >> M >> K;
//	N = 2;
	int n;
	poly P = getPoly(n);
	EXP(P,n,N);
	num res = mul(P[K],num(1.0,0.0));
//	prArr(P,n,num);
	cout << round(res.real()) << endl;
	return 0;
}
