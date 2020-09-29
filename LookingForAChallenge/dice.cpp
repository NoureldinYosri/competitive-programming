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

const int MAX = 1 << 20;
using point = complex<double>;
using poly = point[MAX];
poly P, Q;
int n, m;

void fft(poly & f, int n, bool inv){
    static poly W[2][20];
    static bool ready = 0;
    if(!ready){
        for(int sgn = 0;sgn < 2;sgn++){
            loop(k,10) {
                int m = 1 << k;
                double theta = PI/m * (2*sgn - 1);
                for(int i = 0;i < m;i++)
                    W[sgn][k][i] = polar(1.0,i*theta);
            }
        }
        ready = 1;
    }
	for(int i = 1,j = 0;i+1 < n;i++) {
        for(int k = n >> 1; !(k & (j ^= k));k >>= 1);
        if(i < j) swap(f[i],f[j]);
    }
    for(int m = 1,k = 0;2*m <= n;m <<= 1,k++) {
        const poly & w = W[inv][k];
        for(int s = 0;s < n;s += 2*m) {
            for(int i = 0;i < m;i++) {
                point a = f[s + i],b = f[s + i + m];
                f[s + i] = a + w[i]*b;
                f[s + i + m] = a - w[i]*b;
            }
        }
    }

	
	
	if(inv) {
		loop(i, n) f[i] /= n;
	}
}


void mul(poly & P, int n, poly & Q, int m, poly & R, int & N, int k){
	static point aux[MAX];
	int t = max(n, m);
	while(t != LSOne(t)) t++;
	t <<= 1;
	for(int i = n; i < t;i ++) P[i] = 0;
	for(int i = m; i < t; i++) Q[i] = 0;
	
	fft(P, t, 0);
	fft(Q, t, 0);
	loop(i, t) aux[i] = P[i]*Q[i];
	fft(P, t, 1);
	fft(Q, t, 1);
	fft(aux, t, 1);
	
	loop(i, k) R[i] = aux[i];	
}

void get(int k, int p){
	loop(i, 6) P[i] = 1/6.;
	n = 6;
	Q[0] = 1;
	m = 1;
	while(p > 1){
		if(p & 1) mul(P, n, Q, m, Q, m, k + 1);
		mul(P, n, P, n, P, n, k + 1);
	}
	mul(P, n, Q, m, P, n, k + 1);
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		int n, k; scanf("%d %d", &n, &k);
		if(k < n){
			puts("0");
			continue;
		}
		k -= n;
		get(k, n);
		printf("%.0f\n", floor(P[k].real()*100 + 1e-12));
	}
	return 0;
}
