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

const int MAXN = 2010;

int dp[MAXN << 1][MAXN << 1][2];
int vis[MAXN << 1][MAXN][2], visNum;

int A[MAXN << 1], n;
int nxt[MAXN << 1];


int solve(int i, int r0, int side){
	int r1 = n - (i - (n - r0));
	if(r0 == 0 || r1 == 0) return 1;
	if(i == 2*n) return 0;
	int & ret = dp[i][r0][side];
	if(vis[i][r0][side] == visNum) return ret;
	vis[i][r0][side] = visNum;
	ret = 0;
	
	int m = side ? r1 : r0;
	for(int j = nxt[i]; j < 2*n && !ret; j = nxt[j]){
		int taken = j - i;
		if(taken > m) break;
		ret = solve(j, 	r0 - taken*(side == 0), side ^ 1);
	}	
//	cerr << i << " " << r0 << " " << side << ": " << ret << "\t" << r0 << " " << r1 << " " << m << endl;
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	vi ST;
	while(T--){
		scanf("%d", &n);
		loop(i, 2*n) scanf("%d", A + i);
		visNum++;
		ST.clear();
		for(int i = 2*n-1; i >= 0; i--){
			while(!ST.empty() && A[i] > A[ST.back()]) ST.pop_back();
			nxt[i] = ST.empty() ? (2*n) : ST.back();
			ST.pb(i);
		}
		puts(solve(0, n, 0) ? "YES" : "NO");
	}
	return 0;
}
