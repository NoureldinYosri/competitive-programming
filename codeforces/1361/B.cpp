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

const int mod = 1000000007;

int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}


int n, p;
int A[1 << 20];
int f[1 << 20], g[1 << 20];


unordered_map<int, int> mem;

int powmod(int k){
	if(!k) return 1;
	if(mem.find(k) != mem.end()) return mem[k];
	int x = powmod(k/2);
	x = mul(x, x);
	if(k & 1) x = mul(x, p);
	return mem[k] = x;
}


int solve(){
	if(p == 1) return n & 1;
	sort(A, A + n);
	int m = 0;
	for(int i = 0; i < n; ){
		int v = A[i];
		int j = i;
		while(j < n && A[i] == A[j]) j++;
		f[m] = j-i;
		A[m] = v;
		m++;
		i = j;
	}
	n = m;
	
	
	int e = 0, q = -1;
	for(int i = 0; i < n; i++){
		while(q < A[i] && e >= p){
			e /= p;
			q ++;
		}
		if(q != A[i]) q = A[i], e = 0;
		g[i] = e;
		e = e + f[i];
		q = A[i];
	}
	int need = 0, purge = 1;
	
	for(int i = n-1; i >= 0; i--){
		for(int k = A[i]; i+1 < n && k < A[i+1] && need; k++)
			need *= p;
//		cerr << A[i] << " " << f[i] << " " << g[i] << " " << need << endl;
		int d = min(need, f[i]);
		f[i] -= d;
		need -= d;
//		cerr << "need " << need << endl;
		if(need == 0 && purge){
			f[i] &= 1;
			if(f[i] <= g[i]){
				d = min(g[i], f[i]);
				f[i] -= d;
				need += d;							
			}
			else purge = 0;
		}
//		cerr << "after " << f[i] << endl;
	}
	int ans = 0, is_first = 1;
	mem.clear();
	for(int i = n-1; i >= 0; i--) if(f[i]) {
	//	cerr << A[i] << " " << f[i] << endl;
		int v = mul(f[i], powmod(A[i]));
		if(!is_first) {
			v = add(0, -v);
		}
		is_first = 0;
		ans = add(ans, v); 
	}
	return ans;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d", &n, &p);
		loop(i, n) scanf("%d", A + i);
		printf("%d\n", solve());
	}
	return 0;
}
