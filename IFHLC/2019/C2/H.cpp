#ifdef ACTIVE
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


const int MAX = 100*1000 + 10,mod = 1e9 + 7;
int n,m;

int fact[MAX],invFact[MAX],invInt[MAX];
int invP2[MAX],invP4[MAX];

int mul(int a,int b){
	return (a*(ll)b)%mod;
}
int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

void init(){
	fact[0] = invFact[0] = 1;
	invInt[1] = 1;
	for(int i = 2;i < MAX;i++){
		invInt[i] = mod - mul(mod/i,invInt[mod%i]);
		assert(mul(i,invInt[i]) == 1);
	}
	for(int i = 1;i < MAX;i++) {
		fact[i] = mul(fact[i-1],i);
		invFact[i] = mul(invFact[i-1],invInt[i]);
		assert(mul(fact[i],invFact[i]) == 1);
	}
	int i2 = invInt[2],i4 = invInt[4];
	invP2[0] = invP4[0] = 1;
	for(int i = 1;i < MAX;i++) {
		invP2[i] = mul(invP2[i - 1],i2);
		invP4[i] = mul(invP4[i - 1],i4);
	}
}

int C(int n,int k) {
	if(n < k) return 0;
	int ret = fact[n];
	ret = mul(ret,invFact[k]);
	ret = mul(ret,invFact[n-k]);
	return ret;
}

int solve(){
	scanf("%d %d",&n,&m);
	if(n < abs(m)) return 0;
	int ret = 0;
	for(int x = 0;x <= n;x++) {
		int y = x - m;
		if(y < 0 || y > n) continue;
		int stay = n - x - y;
		if(stay < 0 || stay > n) continue;
//		cerr << x << " " << y << " " << stay << endl;
		int coef = mul(C(n,x),C(n-x,y));
		coef = mul(coef,invP4[x]);
		coef = mul(coef,invP4[y]);
		coef = mul(coef,invP2[stay]);
		ret = add(ret,coef);
	}
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	int T; scanf("%d",&T);
	while(T--) printf("%d\n",solve());
	return 0;
}
#endif
