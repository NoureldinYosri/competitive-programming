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

const int MAXN = 555;
int A[MAXN], n;
pair<int, pi> dp[MAXN][MAXN];
bool vis[MAXN][MAXN];

pair<int, pi> solve(int s, int e){
	if(s > e) return mp(0, pi(INT_MAX, INT_MAX));
	if(s == e) return mp(1, pi(A[s], A[s]));
	auto & ret = dp[s][e];
	if(vis[s][e]) return ret;
	vis[s][e] = 1;
	ret = mp(e-s+1, pi(A[s], A[e]));
	for(int k = s;k+1 <= e; k++){
		auto L = solve(s, k), R = solve(k+1, e);
		pair<int, pi> tmp;
		tmp.first = L.first + R.first;
		if(L.second.second == R.second.first){
			tmp.first--;
			if(L.first == 1) L.second.first++;
			if(R.first == 1) R.second.second++;
		}
		tmp.second.first = L.second.first;
		tmp.second.second = R.second.second;
		ret = min(ret, tmp);
	}
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	printf("%d\n", solve(0, n-1).first);
	return 0;
}
