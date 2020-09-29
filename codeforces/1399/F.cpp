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

const int MAX = 6000 + 10;
int n, L[MAX], R[MAX];
int W[MAX];
bool yes[MAX][MAX];
int dp[MAX][MAX];
vector<vi> startAt, endAt;

int compress(){
	static vi aux;
	aux.clear();
	loop(i, n){
		aux.pb(L[i]);
		aux.pb(R[i]);
	}
	sort(all(aux));
	aux.resize(unique(all(aux)) - aux.begin());
	loop(i, n){
		L[i] = lower_bound(all(aux), L[i]) - aux.begin();
		R[i] = lower_bound(all(aux), R[i]) - aux.begin();
	}
	return aux.size(); 
}


int work(int m){
	vi col[m];
	vi row;
	for(int s = m-1; s >= 0; s--) {		
		for(int e = s; e < m; e++){
			int & res = dp[s][e];
			res = 0;
			
			for(int k : startAt[s]){
				if(k >= e) break;
				res = max(res, dp[s][k] + dp[k+1][e]);
			}
			for(int k : endAt[e]){
				if(k-1 < s) break;
				res = max(res, dp[s][k-1] + dp[k][e]);
			}
			
			if(s < e) res = max(res, dp[s+1][e]);
			res += yes[s][e];
			if(s && (col[e].empty() || dp[s][e] != dp[col[e].back() + 1][e])) col[e].pb(s-1);
			if(row.empty() || dp[s][row.back()] != dp[s][e]) row.pb(e);
		}
		row.clear();
	}
	return dp[0][m-1];
}

int solve(){
	int m = compress();
	loop(i, m) loop(j, m) yes[i][j] = false;
	loop(i, n) yes[L[i]][R[i]] = true;
	startAt.clear();
	endAt.clear();
	startAt.resize(m);
	endAt.resize(m);
	loop(i, n) {
		startAt[L[i]].pb(R[i]);
		endAt[R[i]].pb(L[i]);
	}
	loop(i, m) {
		sort(all(startAt[i]));
		sort(endAt[i].rbegin(), endAt[i].rend());
	}
	return work(m);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		loop(i, n) scanf("%d %d", L + i, R + i);
		printf("%d\n", solve());
	}
	
	return 0;
}
