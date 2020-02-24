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

const int MAX = 410;
int dp[MAX][MAX];
char S[MAX], T[MAX];
int n, m, m1, m2;
int mid;
vi IDX[126];


int solve(int a, int b){
	if(a == 0 && b == 0) return -1;
	int & ret = dp[a][b];
	if(ret != -1) return ret;

	ret = n;
	
	if(a) {
		int x = solve(a-1, b);
		if(x < n) {
			int c = T[a-1];
			x = *upper_bound(all(IDX[c]), x);
		}
		ret = min(ret, x);
	}
	if(b) {
		int x = solve(a, b-1);
		if(x < n){
			int c = T[mid + b - 1];
			x = *upper_bound(all(IDX[c]), x);
		}
		ret = min(ret, x);
	}

//	cerr << a << " " << b << ": " << ret << endl;
	return ret;
}

bool solve(){
	n = strlen(S);
	for(int c = 'a'; c <= 'z'; c++) IDX[c].clear();
	loop(i, n) IDX[(int)S[i]].pb(i);
	for(int c = 'a'; c <= 'z'; c++) IDX[c].pb(n);
	
	m = strlen(T);
	for(mid = 0; mid <= m; mid++){
		m1 = mid;
		m2 = m - m1;
		loop(j, m1+1) loop(k, m2+1) dp[j][k] = -1; 
		//cerr << "try " << m1 << " " << m2 << endl;
		if(solve(m1, m2) < n) return 1;
	}
	return 0;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%s %s", S, ::T);
		puts(solve() ? "YES" : "NO");
	}
	return 0;
}
