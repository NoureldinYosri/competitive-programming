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

const int mod = 998244353, MAX = 3e5 + 10 ;
int fact[MAX];
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}
 
void init(){
	fact[0] = 1;
	for(int i = 1; i < MAX; i++){
		fact[i] = mul(fact[i - 1], i);
	}
}

int n;
vp A;

int f(vi & B){
	map<int, int> M;
	for(int x : B) M[x]++;
	int ret = 1;
	for(auto [_, s] : M) ret = mul(ret, fact[s]);
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	scanf("%d", &n);
	A.resize(n);
	for(auto & [l, r] : A) scanf("%d %d", &l, &r);
	int ans = fact[n];
	vi B, C;
	loop(i, n){ 
		B.push_back(A[i].first);
		C.push_back(A[i].second);
	}
	ans = add(ans, -f(B));
	ans = add(ans, -f(C));
	sort(all(A));
	bool found = false;
	loop(i, n - 1) if(A[i].second > A[i + 1].second) found = true;
	if(!found){
		map<pi, int> M;
		loop(i, n) M[A[i]]++;
		int tmp = 1;
		for(auto [_, s] : M) tmp = mul(tmp, fact[s]);
		ans = add(ans, tmp);
	}
	printf("%d\n", ans);
	return 0;
}
