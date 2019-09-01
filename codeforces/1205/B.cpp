#ifdef ACTIVE
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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int MAX = 1 << 20,B = 64;
int n;
ll A[MAX];
vi who[B];
vi bits[MAX];
int vis[MAX];

void conv(int id,vi & b){
	ll x = A[id];
	for(int i = 0;x;i++){
		if(x & 1) {
			b.push_back(i);
			who[i].push_back(id);
		}
		x >>= 1;
	}
}


bool dfs(int u,int len,int root) {
	if(len == 0) return u == root;
	if(vis[u]) return 0;
	vis[u] = 1;
	for(int b : bits[u])
		for(int v : who[b]) {
			if(v == u) continue;
			if(dfs(v,len-1,root)) return 1;
		}
	return 0;
}

bool can(int len){
	loop(i,n) {
		fill(vis,vis + n,0);
		if(dfs(i,len,i)) return 1;
	}
	return 0;
}

int solve(){
	loop(i,n) conv(i,bits[i]);
	loop(b,B) if(sz(who[b]) >= 3) return 3;
//	loop(i,n) {
//		for(int b : bits[i])
//			for(int j : who[b]) {
//				if(i < j) cout << i << " " << j << endl;
//			}
//	}
	for(int len = 3;len <= n;len++)
		if(can(len))
			return len;
	return -1;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%lld",A + i);
	sort(A,A + n);
	reverse(A,A + n);
	while(n && A[n-1] == 0) n--;
	printf("%d\n",solve());
	return 0;
}
#endif
