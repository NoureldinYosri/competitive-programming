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


const int mod = 1e9 + 7;
int color[10][10];
int m,n;

int dp[10][1 << 10];
int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

bool isConsistent(int r,int msk) {
	loop(c,n) {
		int t = (msk >> c) & 1;
		if(color[r][c] != -1 && color[r][c] != t) return 0;
	}
	return 1;
}

bool isBeutiful(int prv,int cur) {
	static int G[2][10];
	loop(c,n){
		G[0][c] = (prv >> c) & 1;
		G[1][c] = (cur >> c) & 1;
	}
	for(int c = 0;c+1 < n;c++) {
		int ctr = 0;
		loop(i,2) loop(j,2) ctr += G[i][j + c];
		if(ctr != 1 && ctr != 3) return 0;
	}
	return 1;
}

int solve(int r,int prv) {
	if(r == m) return 1;
	int & ret = dp[r][prv];
	if(ret != -1) return ret;
	ret = 0;
	loop(msk,1 << n) {
		if(isConsistent(r,msk)) {
			if(!r || isBeutiful(prv,msk))
				ret = add(ret,solve(r+1,msk));
		}
	}

	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	memset(color,-1,sizeof color);
	int K;
	cin >> m >> n >> K;
	loop(i,K){
		int x,y;
		cin >> x >> y;
		x--,y--;
		cin >> color[x][y];
	}
	memset(dp,-1,sizeof dp);
	cout << solve(0,0) << endl;
	return 0;
}
#endif
