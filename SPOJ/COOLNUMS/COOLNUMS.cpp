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



bool solve(int i, int s, const vi & T, vector<vi> & dp, vector<vi> & visId, int visNum) {
	if(s == 0) return true;
	if(i == sz(T)) return false;
	if(visId[i][s] == visNum) return dp[i][s];
	visId[i][s] = visNum;
	dp[i][s] = solve(i + 1, s, T, dp, visId, visNum);
	if(T[i] <= s && !dp[i][s]) dp[i][s] |= solve(i + 1, s - T[i], T, dp, visId, visNum);
	return dp[i][s];
}

bool check(vi T){
	reverse(all(T));
	while(!T.empty() && T.back() == 0) T.pop_back();
	if(T.empty()) return true;
	int s = accumulate(all(T), 0);
	if(s & 1) return 0;
	s >>= 1;
	static vector<vi> dp(12, vi(10*9 + 1, 0));
	static vector<vi> visId(12, vi(10*9 + 1, 0));
	static int visNum = 0;
	visNum++;
	return solve(0, s, T, dp, visId, visNum);

/*	static int f[1 << 11];
	for(int msk = 1; msk < (1 << sz(T)); msk++){
		int b = LSOne(msk);
		int i = bit_lg(b);
		f[msk] = f[msk^b] + T[i];
		if(f[msk] == s) return true;
	}
	return false;
*/
}

vi state;
vector<vi> adj;

int bt(vi & T){
	int u = state.size();
	state.push_back(check(T));
	adj.emplace_back(10, -1);
	if(sz(T) == 10) return u;
	for(int d = T.empty() ? 0 : T.back(); d < 10; d++){
		T.push_back(d);
		adj[u][d] = bt(T);
		T.pop_back();
	}
	return u;
}

int get(vi T){
	sort(all(T));
	int u = 0;
	for(int d : T){
		u = adj[u][d];
		assert(u != -1);
	}
	return u;
}

void fix(int u, vi & T){
	assert(u != -1);
	if(sz(T) == 10) return;
	int mid = T.empty() ? 0 : T.back();
	for(int d = 0; d < mid; d++){
		T.push_back(d);
		adj[u][d] = get(T);
		T.pop_back();
	}
	for(int d = mid; d < 10; d++){
		T.push_back(d);
		fix(adj[u][d], T);
		T.pop_back();
	}
}

vector<uint32_t> dp[12][2];
vi lastSolved[12][2];
int curTime;
vi D;
uint32_t solve(int i, int u, bool areEqual){
	assert(u != -1);
	if(i == sz(D)) return state[u];
	if(dp[i][areEqual].empty()) {
		dp[i][areEqual].resize(sz(state), 0);
		lastSolved[i][areEqual].resize(sz(state), 0);
	}
	uint32_t & ret = dp[i][areEqual][u];
	if(lastSolved[i][areEqual][u] == curTime) return ret;
	lastSolved[i][areEqual][u] = curTime;
	ret = 0;
	loop(d, 10){
		if(areEqual && (d > D[i])) continue;
		ret += solve(i + 1, adj[u][d], areEqual && (d == D[i]));
	}
	return ret;
}

uint32_t solve(uint32_t x){
	if(x == 0) return 1;
	curTime++;
	D.clear();
	while(x){
		D.push_back(x % 10);
		x /= 10;
	}
	reverse(all(D));
	return solve(0, 0, true);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	vi T;
	bt(T);
	assert(T.empty());
	fix(0, T);
	uint32_t A, B;
	while(scanf("%d %d", &A, &B) == 2 && !(A == 0 && B == 0)){
		printf("%u\n", solve(B) - solve(A - 1));
	}
	
	return 0;
}
