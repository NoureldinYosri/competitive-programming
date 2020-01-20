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


int add(int a,int b,int m){
	a += b;
	if(a >= m) a -= m;
	if(a < 0) a += m;
	return a;
}

int mul(int a,int b,int m){
	return (a*(ll)b)%m;
}



int f(const vi & P,vi & freq){
	int ret = 0;
	for(int l = 0;l < sz(P);l++){
		int mx = INT_MIN, mn = INT_MAX;
		for(int r = l;r < sz(P);r++){
			mx = max(mx, P[r]);
			mn = min(mn, P[r]);
			if(r-l == mx-mn)
				ret++,freq[r-l]++;
		}
	}
	return ret;
}
int f(int n){
	vi P;
	loop(i,n) P.push_back(i);
	vi freq(n,0);
	int ret = 0;
	do{
		ret += f(P, freq);
	}while(next_permutation(all(P)));
	for(int i = 0;i < n;i++)
		cout << freq[i] << " ";
	cout << endl;
	return ret;
}

const int MAXN = 1 << 20;
int fact[MAXN], invInt[MAXN], invFact[MAXN];
int mod;

int C(int n,int k){
	if(k > n) return 0;
	return mul(fact[n], mul(invFact[k], invFact[n-k], mod), mod);
}

void init(){
	fact[0] = 1;
	for(int i = 1;i < MAXN;i++)
		fact[i] = mul(i, fact[i-1], mod);
	invInt[1] = 1;
	for(int i = 2;i < MAXN;i++){
		invInt[i] = add(mod, - mul(mod/i, invInt[mod%i], mod), mod);
		assert(mul(i, invInt[i], mod) == 1);
	}
	invFact[0] = 1;
	for(int i = 1;i < MAXN;i++)
		invFact[i] = mul(invFact[i-1], invInt[i], mod);
}


int g(int n){
	int ret = 0;
	for(int k = 0;k <= n;k++){
		int tmp = mul(fact[k+1], mul(n-k+1, fact[n-k+1], mod), mod);
		ret = add(ret, tmp, mod);
//		cout << tmp << " " ;
	}
//	cout << endl;
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n; scanf("%d %d",&n ,&mod);
	init();
	cout << g(n-1) << endl;
	return 0;
}
