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

const int mod = 1e9 + 7;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}

const int MAX = 2 << 20;
int T[MAX][3];
int f[MAX];

void init(){
	T[1][0] = 1;
	for(int n = 2; n < MAX; n++){
		T[n][0] = add(T[n-1][0], mul(2, T[n-1][1]));
		T[n][1] = T[n-1][0];
		T[n][2] = add(T[n-1][2], T[n-1][1]);
	}
	for(int n = 2; n < MAX; n++){
		f[n] = mul(4, T[n-2][0]);
		if(n >= 3) f[n] = add(f[n], f[n-3]);
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	int T; scanf("%d", &T);
	while(T--){
		int n; scanf("%d", &n);
		assert(n < MAX);
		printf("%d\n", f[n]);
	}
	return 0;
}
