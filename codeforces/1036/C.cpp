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

vi D;
vector<ll> dp[4][2];

ll solve(int i, int ctr, bool areEqual){
	if(ctr > 3) return 0;
	if(i == sz(D)) return 1;
	ll & ret = dp[ctr][areEqual][i];
	if(ret != -1) return ret;
	ret = 0;
	loop(d, 10){
		if(areEqual && (d > D[i])) break;
		ret += solve(i + 1, ctr + (d != 0), areEqual && (d == D[i]));		
	}
	return ret;
}

ll solve(ll x){
	D.clear();
	while(x) {
		D.push_back(x%10);
		x /= 10;
	}
	if(D.empty()) D.push_back(0);
	reverse(all(D));
	loop(i, 4) loop(j, 2){
		dp[i][j].clear();
		dp[i][j].resize(sz(D), -1);
	}
	return solve(0, 0, 1);
}

void tc(){
	ll l, r; scanf("%lld %lld", &l, &r);
	printf("%lld\n", solve(r) - solve(l - 1));
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
