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


const int MAX = 1 << 20, TOT = MAX - 1;

int have[MAX];
int cnt[MAX];

ll dfs(int x){
	if(cnt[x] == 0) return 0;
	ll ret = have[x];
	cnt[x] = 0;
	loop(i, 20) if((x >> i) & 1) {
		ret += dfs(x ^ (1 << i));
	}
	return ret;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n; scanf("%d", &n);
	loop(i, n){
		int x; scanf("%d", &x);
		cnt[x] = have[x] = 1;
	}
	loop(k, 20){
		loop(x, MAX) if((x >> k) & 1) cnt[x] += cnt[x ^ (1 << k)];
	}
	
	ll ans = 0;
	for(int x = TOT; x; x--) if(have[x]){
		have[x] = 0;
		ans += x * dfs(x ^ TOT);
	}
	printf("%lld\n", ans);
	return 0;
}
