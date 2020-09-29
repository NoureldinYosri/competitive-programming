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

const int mod = 490019, phi = mod - 1, MAXLG = 20, MAXN = 1 << MAXLG;
using point = complex<long double>;
using poly = point[MAXN];

int add(int a, int b, int m){
	a += b;
	if(a >= m) a -= m;
	if(a < 0) a += m;
	if(a < 0 || a >= m) a = (a%m + m)%m;
	return a;
}
int mul(int a, int b, int m){
	return (a*(ll)b)%m;
}

int powmod(int x, int p, int m){
	if(!p) return 1;
	int y = 1;
	for(; p > 1; p >>= 1){
		if(p & 1) y = mul(x, y, m);
		x = mul(x, x, m);
	}
	return mul(x, y, m);
}

int inv(int x){
	return powmod(x, phi-1, mod);
}

void fft(poly & f, int n, bool inv) {
    for(int i = 1,j = 0;i+1 < n;i++) {
        for(int k = n >> 1; !(k & (j ^= k));k >>= 1);
        if(i < j) swap(f[i],f[j]);
    }
    static vector<point> W;
    for(int m = 1,k = 0;2*m <= n;m <<= 1,k++) {
		double theta = PI/m * (2*inv - 1);
		W.clear();
		for(int i = 0; i < m; i++) W.pb(polar(1.0, i*theta));
        for(int s = 0;s < n;s += 2*m) {
            for(int i = 0;i < m;i++) {
                point a = f[s + i],b = f[s + i + m];
                point w = W[i];
                f[s + i] = a + w*b;
                f[s + i + m] = a - w*b;
            }
        }
    }
    if(inv){
        loop(i,n) f[i] /= n;
    }
}

int A[MAXN], B[MAXN], n, m, c;
poly fA, fB, fC;
poly LA, RA;
poly LB, RB;

void apply(int *A, int n, function<int(const int &)> f){
	static int aux[MAXN];
	loop(i, phi) aux[i] = 0;
	loop(i, n) aux[f(i)] = add(aux[f(i)], A[i], mod);
	copy(aux, aux + phi, A);
}

const int base = sqrt(mod);
point split(int v){
	return point(v/base, v%base);	
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &m, &c);
	loop(i, n) {
		scanf("%d", A + i);
		A[i] %= mod;
	}
	loop(j, m) {
		scanf("%d", B + j);
		B[j] %= mod;
	}
	apply(A, n, [](const int & i){
		return mul(i, i, phi);
	});
	apply(B, m, [](const int & i){
		return mul(mul(i, i, phi), i, phi);
	});
	int N = phi;
	while(N != LSOne(N)) N++;
	N <<= 1;
	vi C(phi), iC(phi);
	int ic = inv(c);
	C[0] = iC[0] = 1;
	for(int i = 1; i < phi; i++){
		C[i] = mul(C[i-1], c, mod);
		iC[i] = mul(iC[i-1], ic, mod);
	}
	loop(i, N){
		int a_i = (i < phi) ? A[i] : 0;
		int b_i = (i < phi) ? B[i] : 0;
		ll k = ((i*(i + 1LL)) >> 1)%phi;

		fA[i] = split(mul(a_i, iC[k], mod));
		fB[i] = split(mul(b_i, iC[k], mod));
	}
//	cerr << "fft A" << endl;
	fft(fA, N, false);
//	cerr << "fft B" << endl;
	fft(fB, N, false);
//	cerr << "rev" << endl;
	loop(i, N) {
		int j = -i & (N - 1);
		LA[i] = (fA[i] + conj(fA[j]))/point(2, 0.0);
		RA[i] = (fA[i] - conj(fA[j]))/point(0, 2.0);
		
		LB[i] = (fB[i] + conj(fB[j]))/point(2, 0.0);
		RB[i] = (fB[i] - conj(fB[j]))/point(0, 2.0);
	}
//	cerr << "pre" << endl;
	loop(i, N){
		fA[i] = LA[i] * LB[i];
		fB[i] = LA[i] * RB[i] + LB[i] * RA[i];
		fC[i] = RA[i] * RB[i];
	}
//	cerr << "re" << endl;
	fft(fA, N, true);
	fft(fB, N, true);
	fft(fC, N, true);
	int ans = 0;
	for(int s = 0; s < N; s++){
		int e = ((s*(s + 1LL)) >> 1)%phi;
		ll f = round(fA[s].real())*base*base; f %= mod;
		f += round(fB[s].real())*base; f %= mod;
		f += round(fC[s].real());
//		if(f) cerr << s << ": " << f << " * c^" << e << endl;
		ans = add(ans, mul(f%mod, C[e], mod), mod);
	}
	cout << ans << endl;
	return 0;
}
