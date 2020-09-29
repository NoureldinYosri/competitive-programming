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


vector<map<ll, int>> dp;

int bt(int i, ll msk, const vp & pairs){
	if(i == sz(pairs)) return 0;
	if(dp[i].count(msk)) return dp[i][msk];
	auto [x, y] = pairs[i];
	bool can_take = 1;
	if((msk >> x) & 1) can_take = 0;
	if((msk >> y) & 1) can_take = 0;
	int ret = bt(i + 1, msk, pairs);
	if(can_take) ret = max(ret, 1 + bt(i + 1, msk | (1LL << x) | (1LL << y), pairs));
	return dp[i][msk] = ret;
} 

int solve(int m, int n){
	vp pairs;
	vp cells;
	loop(i, m) loop(j, n) cells.emplace_back(i, j);
	loop(i, sz(cells)) loop(j, i){
		auto [a, b] = cells[i];
		auto [c, d] = cells[j];
		if(abs(a-c) + abs(b-d) == 3){
			pairs.emplace_back(a*n + b, c*n + d);
		}
	}
	if(sz(pairs) > 30) return -1;
	dp.clear();
	dp.resize(sz(pairs));
	return bt(0, 0, pairs);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	for(int m = 1; m <= 20;m ++, cerr << endl)
		for(int n = 1; n <= 10; n++)
			cerr << solve(m, n) << " ";
	return 0;
}
