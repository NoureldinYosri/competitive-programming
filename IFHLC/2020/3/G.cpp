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

int n, T;
int need[50];
double P[50];

vp factor(int N){
	static map<int, vp> mem;
	if(mem.count(N)) return mem[N];
	vp ret;
	int x = N;
	for(int i = 2; i*i <= x; i++){
		if(x%i) continue;
		int e = 0;
		while(x%i == 0) {
			x /= i;
			e++;
		}
		ret.emplace_back(i, e);
	}
	if(x > 1) ret.emplace_back(x, 1);
	mem[N] = ret;
	return ret;
}

long double M(const vi & H){
	map<int, int> E;
	int N = accumulate(all(H), 0);
	for(int i = 2; i <= N; i++){
		for(auto [p, e] : factor(i))
			E[p] += e;
	}
	for(int c : H) {
		for(auto [p, e] : factor(c))
			E[p] -= e;
	}
	long double ret = 1;
	for(auto [p, e] : E){
		assert(e >= 0);
		while(e) {
			ret *= p;
			e --;
		}
	}
	return ret;
}

void tc(){
	scanf("%d", &n);
	loop(i, n) scanf("%d %lf", need + i, P + i);
	scanf("%d", &T);
	if(accumulate(need, need + n, 0) > T){
		puts("0");
		return;
	}
	loop(i, n) if(P[i] <= 0){
		puts("0");
		return;
	}
	long double p0 = 1.0, sq = 0.0;
	vi H;
	loop(i, n){
		if(need[i] == 0) continue;
		if(P[i] >= 1) continue;
		p0 *= pow(P[i], need[i]);
		sq += 1 - P[i];
		H.pb(need[i]);
	}
	p0 *= M(H);
	long double ans = 0.0;
	int sc = accumulate(need, need + n, 0);
	for(int s = sc; s <= T; s++){
		cerr << s << ": " << p0 << endl;
		ans += p0;
		p0 *= (sq * s)/(s - sc + 1);
	}
	
	printf("%.3f\n", (double)ans);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
