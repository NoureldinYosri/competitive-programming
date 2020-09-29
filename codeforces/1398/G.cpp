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


const int LG = 19;
using point = complex<double>;
using poly = point[1 << LG];


void fft(poly & f,int n,bool inv) {
    static poly W[2][LG];
    static bool ready = 0;
    if(!ready){
        for(int sgn = 0;sgn < 2;sgn++){
            loop(k, LG) {
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
    if(inv){
        loop(i,n) f[i] /= n;
    }
}

const int MAX = 400*1000 + 10;
poly f, g;
bool canMake[MAX];
int best[1 << 20];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n, X, Y;
	scanf("%d %d %d", &n, &X, &Y);
	loop(i, n + 1){
		int a; scanf("%d", &a);
		f[a] = 1;
		g[X-a] = 1;
	}
	int N = X + 1;
	while(N != LSOne(N)) N++;
	N <<= 1;
	assert(N <= (1 << LG));
	fft(f, N, false);
	fft(g, N, false);
	loop(i, N) f[i] *= g[i];
	fft(f, N, true);
	
	for(int diff = 1; diff <= X; diff++)
		if(round(f[diff + X].real()) > 0){
			canMake[diff + Y] = true;
		}
		
	memset(best, -1, sizeof best);

		
	for(int i = 1; i <= X + Y; i++) if(canMake[i])  {
		for(int j = i; j < (1 << 20); j += i)
			best[j] = i;
	}
	
	
	int m; scanf("%d", &m);
	while(m--){
		int L; scanf("%d", &L);
		assert(L%2 == 0);
		L >>= 1;
		int ans = best[L];
		if(ans != -1) ans <<= 1;
		printf("%d%c", ans, " \n"[m==0]);
	}
	return 0;
}
