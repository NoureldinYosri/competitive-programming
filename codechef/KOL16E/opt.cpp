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

int powmod(int a, int x, int m){
	if(!x) return 1;
	int b = 1;
	for(; x > 1; x >>= 1){
		if(x & 1) b = (a*(ll)b)%m;
		a = (a*(ll)a)%m;
	}
	return (a*(ll)b)%m;
}

int solve(int m){
	int phi = m-1;
	int ret = INT_MAX;
	for(int i = 1; i*i <= phi; i++) if(phi%i == 0) {
		int a = powmod(10, i, m);
		if(a == 1) return i;
		if(i != phi/i && powmod(10, phi/i, m) == 1) ret = phi/i;
	}
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	char str[2][10] = {"alter", ""};
	for(int t = 1; t <= T; t++){
		int p; scanf("%d", &p);
		int k = solve(p);
		pi res(k, 1);
		if(k%2 == 0 && powmod(10, k >> 1, p) == p-1){
			res = pi(k >> 1, 0);
		}
//		cerr << p << " " << res << endl;
		printf("Case %d: %d-%ssum\n", t, res.first, str[res.second]);
	}
	return 0;
}
