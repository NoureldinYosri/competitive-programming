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

const int MAXN = 200*1000 + 10;
vector<ll> prices[MAXN];
int cnt[MAXN], n;
ll dp[MAXN];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 0;i <= n;i++) prices[i].clear(), cnt[i] = 0;
		
		loop(i, n){
			int m, p; scanf("%d %d", &m, &p);
			prices[m].pb(p);
			cnt[m]++;
		}
		
		for(int i = 1;i <= n;i++)
			cnt[i] += cnt[i-1];
		

		

		
		
		ll ans = 0;
		for(int c = 0; c < n;){
			while(c < cnt[c]) c = cnt[c];
			assert(c == cnt[c]);
			if(c == n) break;
			
			
			int nxt = c + 1;
			while(prices[nxt].empty()) nxt ++;
			
			int need = nxt - c;
			int to = need;
			while(to < cnt[to]) to = cnt[to];
			multiset<ll> MS;
			for(int i = c+1; i <= to; i++)
				for(ll x : prices[i])
					MS.insert(x);
			assert(sz(MS) <= need);
			cerr << "need " << need << " to go from " << c << " to " << nxt << " from: " << endl;
			print(MS, ll);
/*			while(need --){
				ans += *MS.begin();
				MS.erase(MS.begin());
			}
*/			c = nxt;
		}

		printf("%lld\n", ans);
		break;
	}
	return 0;
}
