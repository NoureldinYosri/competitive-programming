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

const int MAX = 10, mod = 1e9 + 7;
int n,m;
char G[MAX][MAX + 1];

queue<pi> q;
int merge(int r, int msk0, int msk1){
	int ret = msk1;
	loop(j, n) if(G[r][j] == '.') ret |= (msk0 & (1 << j));
	for(int j = 0;j < n;j++) if(G[r][j] == '.'){
		int k = j;
		bool y = 0;
		while(k < n && G[r][k] == '.'){
			y |= (ret >> k) & 1;
			k++;
		}
		for(;j < k;j++) ret |= y << j;
		j--;
	}
	return ret;
}

int dp[MAX+1][1 << MAX];
int vis[1 << MAX];

bool valid(int r, int msk){
	loop(j, n){
		if(G[r][j] == '.') continue;
		if(msk & (1 << j)) return 0;
	}
	return 1;
}

int solve(){
	int tot = 1 << n;
	loop(msk, tot) dp[m][msk] = 1;
	for(int r = m-1;r >= 0;r--){
		loop(msk0, tot){
			loop(msk, tot) vis[msk] = 0;
			loop(msk, tot) if(valid(r, msk)) vis[merge(r, msk0, msk)] = 1;
			loop(msk, tot) dp[r][msk0] += vis[msk] * dp[r+1][msk];
		}
		prArr(dp[r], tot, int);
	}
	return dp[1][0];
}

int main(){
	freopen("cave.in", "r", stdin);
	freopen("cave.out", "w", stdout);
	scanf("%d %d", &m, &n);
	if(m > MAX || n > MAX){
		puts("-1");
		return 0;
	}
	int res = solve();
	printf("%d\n", res);
	cerr << res << endl;
	return 0;
}
