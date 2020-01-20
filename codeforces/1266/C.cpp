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

const int MAX = 500 + 10;
ll A[MAX][MAX];

vi primes;

void init(){
	for(int i = 2;sz(primes) < MAX;i++){
		bool is_prime = 1;
		for(int j = 2;j*j <= i && is_prime;j ++)
			if(i%j == 0)
				is_prime = 0;
		if(is_prime) primes.push_back(i);
	}
}

vector<vi> solve(int m, int n){
	vector<vi> ret;
	if(n == 1){
		loop(i,m) {
			ret.push_back(vi{i+2});
		}
		return ret;
	}
	ret.emplace_back();
	loop(i, n) ret.back().push_back(2*i+2);
	for(int i = 2;i <= m;i++){
		ret.emplace_back();
		ret.back().push_back(2*i-1);
		for(int j = 1;j < n;j++){
			int a = ret.back()[0];
			int b = ret[0][j];
			ret.back().push_back(a*(b/__gcd(a,b)));
		}
	}
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int R,C; cin >> R >> C;
	if(R*C == 1) {
		puts("0");
		return 0;
	}
	init();
	vector<vi> res = solve(max(R,C), min(R,C));
	if(R < C){
		loop(r, R) loop(c, C) printf("%d%c", res[c][r], " \n"[c==C-1]);
	}
	else {
		loop(r, R) loop(c, C) printf("%d%c", res[r][c], " \n"[c==C-1]);
	}
	return 0;
}
