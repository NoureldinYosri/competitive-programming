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

const int MAXB = 30, MAXN = 100*1000 + 10, MAX = MAXB * MAXN + MAXN;
int trie[MAX][2],tsize = 1;
int depth[MAX];

void insert(int x){
	int cur = 0;
	for(int i = 0;i < MAXB;i++){
		int b = (x >> (MAXB - 1 - i)) & 1;
		if(trie[cur][b] == -1) {
			depth[tsize] = depth[cur] + 1;
			trie[cur][b] = tsize++;
		}
		cur = trie[cur][b];
	}
}

ll dp[MAX];

ll solve(int cur){
	if(cur == -1) return 0;
	ll & ret = dp[cur];
	if(ret != -1) return ret;
	ret = 1LL << 60;
	int i = MAXB - 1 - depth[cur];
	ll bit = 1LL << i;
	
	for(int c = 0;c < 2;c++){
		ll tmp = 0;
		loop(j, 2){
			if(trie[cur][j] == -1) continue;
			ll aux = solve(trie[cur][j]);
			if((c^j)) aux |= bit;
			tmp = max(tmp, aux);
		}
		ret = min(ret, tmp);
	}
//	cout << cur << " " << ret << " " << trie[cur][0] << " " << trie[cur][1] << endl;

	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	memset(trie, -1, sizeof trie);
	int n; scanf("%d",&n);
	loop(i,n){
		int x; scanf("%d",&x);
		insert(x);
	}
	memset(dp, -1, sizeof dp);
	cout << solve(0) << endl;
	return 0;
}
