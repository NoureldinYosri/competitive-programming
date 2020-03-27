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


int mul(int a, int b, int m){
	return (a*(ll)b)%m;
}
int powmod(int a, int p, int m){
	if(!p) return 1;
	int b = 1;
	for(;p > 1; p>>=1){
		if(p&1) b = mul(a, b, m);
		a = mul(a, a, m);
	}
	return mul(a, b, m);
}
int inv(int x, int m){
	return powmod(x, m - 2, m);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	ll n;
	int p, r; cin >> n >> p >> r;
	if(n >= 2*p){
		if(r == 0) printf("%d %d\n", 2*p, 2*p-1);
		else puts("-1 -1");
	}
	else if(n >= p){
		if(r == 0){
			for(int i = 2;i <= n;i ++)
				if(i != p){
					printf("%d %d\n", i, i-1);
					return 0;
				}
			puts("-1 -1");
		}
		else {
			int k = 1;
			for(int i = 1;i <= n;i ++)
				if(i != p)
					k = mul(k, i, p);
			printf("%d %d\n", p, mul(r, inv(k, p), p));
		}
	}
	else if(r == 0) puts("-1 -1");
	else {
		int f = 1;
		for(int i = 1;i <= n;i++)
			f = mul(f, i, p);
		int invf = inv(f, p);
		for(int i = 2;i <= n;i++){
			int j = mul(r, mul(i, invf, p), p);
			if(j < i){
				printf("%d %d\n", i, j);
				return 0;
			}
		}
		puts("-1 -1");
	}
	return 0;
}
