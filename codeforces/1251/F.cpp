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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;


const int mod = 998244353 ;

int mul(int a,int b) {
	return (a*(ll)b)%mod;
}
int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

int powmod(int a,int p) {
	if(p == 0) return 1;
	int b = 1;
	for(;p > 1;p >>= 1) {
		if(p&1) b = mul(a,b);
		a = mul(a,a);
	}
	return mul(a,b);
}

vi getPrimeDivs(int n) {
	vi P;
	for(int x = 2;x*x <= n;x++)
		if(n%x == 0) {
			P.push_back(x);
			while(n%x == 0) n /= x;
		}
	if(n > 1) P.push_back(n);
	return P;
}

bool isGen(int g,vi & P) {
	for(int p : P)
		if(powmod(g,(mod-1)/p) == 1)
			return 0;
	return 1;
}

int getGen() {
	vi P = getPrimeDivs(mod-1);
	while(1) {
		int g = rand()%(mod - 1) + 1;
		if(isGen(g,P)) return g;
	}
}
const int MAXB = 23;
const int G = 846930887;
int memR[1 << MAXB];
int memRinv[1 << MAXB];

int getRoot(int n,bool inv) {
	assert((mod-1)%n == 0);
	if(memR[n] == -1){
		memR[n] = powmod(G,(mod-1)/n);
		memRinv[n] = powmod(memR[n],mod-2);
	}
	return inv ? memRinv[n] : memR[n];
}

int f[5][1 << MAXB];
int A[1 << 20],B[5];
int n,m;

int g1[1 << MAXB],g2[1 << MAXB];
int fact[1 << MAXB],invFact[1 << MAXB],invInt[1 << MAXB];
int p2[1 << MAXB];

void init(){
	memset(memR,-1,sizeof memR);
	p2[0] = fact[0] = invFact[0] = 1;
	for(int i = 1;i < (1 << MAXB);i++){
		fact[i] = mul(fact[i-1],i);
		p2[i] = mul(p2[i-1],2);
	}
	invInt[1] = invFact[1] = 1;
	for(int i = 2;i < (1 << MAXB);i++){
		invInt[i] = add(mod,-mul(mod/i,invInt[mod%i]));
		assert(mul(i,invInt[i]) == 1);
		invFact[i] = mul(invFact[i - 1],invInt[i]);
	}
}


int C(int n,int k) {
	if(k > n) return 0;
	int res = fact[n];
	res = mul(res,invFact[k]);
	res = mul(res,invFact[n-k]);
	return res;
}

void DFT(int *f,int n,bool inv) {
    for(int i = 1,j = 0;i+1 < n;i++) {
        for(int k = n >> 1; !(k & (j ^= k));k >>= 1);
        if(i < j) swap(f[i],f[j]);
    }
    for(int m = 1,k = 0;2*m <= n;m <<= 1,k++) {
    	int g = getRoot(2*m,inv);
        for(int s = 0;s < n;s += 2*m) {
        	for(int i = 0,w = 1;i < m;i++) {
                int a = f[s + i],b = f[s + i + m];
                f[s + i] = add(a ,mul(w,b));
                f[s + i + m] = add(a,- mul(w,b));
                w = mul(w,g);
            }
        }
    }
    if(inv){
    	int in = powmod(n,mod - 2);
    	for(int i = 0;i < n;i++)
    		f[i] = mul(f[i],in);
    }
}

void work(int a,int b,int *f) {
	int n = a + 2*b + 1;
	while(n != LSOne(n)) n++;
	fill(g1,g1 + n,0);
	fill(g2,g2 + n,0);
	for(int i = 0;i <= a;i++)
		g1[i] = mul(C(a,i),p2[i]);
	for(int i = 0;i <= 2*b;i++)
		g2[i] = C(2*b,i);
//	cerr << a << " " << b << endl;
//	prArr(g1,n,int);
//	prArr(g2,n,int);
	DFT(g1,n,0);
	DFT(g2,n,0);
	for(int i = 0;i < n;i++)
		f[i] = mul(g1[i],g2[i]);
	DFT(f,n,1);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i);
	loop(i,m) scanf("%d",B + i);
	sort(A,A + n);
	sort(B,B + m);
	set<int> type1,type2;
	for(int i = 0,j = 0;j < m;j++) {
		while(i < n && A[i] < B[j]) {
			int x = A[i++];
			if(type2.count(x)) continue;
			if(type1.count(x)) {
				type1.erase(x);
				type2.insert(x);
				continue;
			}

			type1.insert(x);
		}
//		cerr << "@" << B[j] << endl;
//		print(type1,int);
//		print(type2,int);
		work(type1.size(),type2.size(),f[j]);
//		prArr(f[j],10,int);
	}

	fflush(stderr);
	int Q; scanf("%d",&Q);
	while(Q--) {
		int A; scanf("%d",&A);
		A >>= 1;
		int ans = 0;
		loop(i,m) {
			int w = A - B[i] - 1;
			if(w < 0) continue;
			ans = add(ans,f[i][w]);
		}
//		cerr << ans << endl;
		printf("%d\n",ans);
	}
	return 0;
}
