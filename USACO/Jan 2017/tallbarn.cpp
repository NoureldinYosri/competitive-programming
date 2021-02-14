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

int n;
ll A[1 << 20];
double C[1 << 20];
vi ord;

double solve(ll K){
	double scaler = 0;
	loop(i, n) {
		C[i] = sqrt(A[i]);
		scaler += C[i];
	}
	ll used = 0;
	double ans = 0;
	set<pair<double, int>> gain;
	loop(i, n) {
		C[i] *= K / scaler;
		C[i] = floor(C[i]);
		C[i] = max(C[i], 1.0);
		used += C[i];
		ans += A[i]/C[i];
		gain.emplace(A[i]/C[i] - A[i]/(C[i] + 1), i);
	}
	assert(used <= K);
	while(used < K){
		used++;
		auto p = *gain.rbegin();
		int i = p.second;
		gain.erase(p);
		ans -= A[i]/C[i];
		C[i]++;
		ans += A[i]/C[i];
		gain.emplace(A[i]/C[i] - A[i]/(C[i] + 1), i);		
	}
	return ans;
}

double solve2(ll K){
	double scaler = 0;
	loop(i, n) {
		C[i] = sqrt(A[i]);
		scaler += C[i];
	}
	ll used = 0;
	double ans = 0;
	set<pair<double, int>> gain;
	loop(i, n) {
		C[i] *= (K - n) / scaler;
		C[i] = floor(C[i]) + 1;
		used += C[i];
		ans += A[i]/C[i];
		gain.emplace(A[i]/C[i] - A[i]/(C[i] + 1), i);
	}
	assert(used <= K);
	while(used < K){
		used++;
		auto p = *gain.rbegin();
		int i = p.second;
		gain.erase(p);
		ans -= A[i]/C[i];
		C[i]++;
		ans += A[i]/C[i];
		gain.emplace(A[i]/C[i] - A[i]/(C[i] + 1), i);		
	}
	return ans;
}


int main(){
	freopen("tallbarn.in", "r", stdin);
	freopen("tallbarn.out", "w", stdout);
	ll K; scanf("%d %lld", &n, &K);
	loop(i, n) scanf("%lld", A + i);
	double ans = solve(K);
	ans = min(ans, solve2(K));
	printf("%.0f\n", ans);
	return 0;
}
