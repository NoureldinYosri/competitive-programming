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


bool check(const vi & V, int x){
	vi P;
	loop(i, sz(V)) P.pb(i);
	int val = -1;
	do{
		int r = x;
		for(int i : P) r %= V[i];
		if(val != -1 && r != val) return 0;
		val = r;
	}while(next_permutation(all(P)));
	return 1;
}

bool check_each(const vi & V, int n){
	for(int x = 0; x <= 3*n; x++)
		if(!check(V, x))
			return 0;
	print(V, int);
	return 1;
}

int solve(int k, int n){
	static vi V;
	if(k == 0) return check_each(V, n);
	int low = V.empty() ? 0 : V.back();
	int ret = 0;
	for(int a = low+1; a <= n; a++){
		V.pb(a);
		ret += solve(k-1, n);
		V.pop_back();
	}
	return ret;
}



const int mod = 998244353;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}
const int MAX = 1 << 20;
int invInt[MAX], fact[MAX], invFact[MAX];

void init(){
	invInt[1] = 1;
	for(int i = 2; i < MAX; i++)
		invInt[i] = add(mod, -mul(mod/i, invInt[mod%i]));
	fact[0] = 1;
	invFact[0] = 1;
	for(int i = 1; i < MAX; i++){
		fact[i] = mul(fact[i-1], i);
		invFact[i] = mul(invFact[i-1], invInt[i]);
	}

}

int C(int n, int k){
	if(n < 0 || k < 0) return 0;
	if(k > n) return 0;
	int ret = fact[n];
	ret = mul(ret, invFact[k]);
	ret = mul(ret, invFact[n-k]);
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	int n, k; cin >> n >> k;
	ll ret = 0;
	for(int x = 1; x <= n; x++){
		int m = n/x;
		int tmp = C(m - 1, k-1);
//		cout << x << " " << tmp << endl;
		ret = add(ret, tmp);
	}
	cout << ret << endl;
	return 0;
}
