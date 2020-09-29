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

const int oo = 1 << 29;
const int MAX = 1024;
int E2[MAX][MAX], E5[MAX][MAX];
int n;
bool vis[MAX][MAX];
pair<pi, pi> dp[MAX][MAX];

pi operator + (const pi & a, const pi &b){
	return pi(a.first + b.first, a.second + b.second);
}

pair<pi, pi> solve(int i, int j){
	if(i >= n || j >= n) return mp(pi(oo, oo), pi(oo, oo));
	if(i == n-1 && j == n-1) return mp(pi(E2[i][j], E5[i][j]), pi(E5[i][j], E2[i][j]));		
	if(vis[i][j]) return dp[i][j];
	vis[i][j] = true;
	pair<pi, pi> & ret = dp[i][j];
	
	auto [a2, a5] = solve(i + 1, j);
	auto [b2, b5] = solve(i, j + 1);
	
	dp[i][j].first = min(a2, b2);
	dp[i][j].second = min(a5, b5);
	dp[i][j].first = dp[i][j].first + pi(E2[i][j], E5[i][j]);
	auto [x, y] = dp[i][j].second;
	dp[i][j].second = pi(x + E5[i][j], y + E2[i][j]);
	
	
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	bool foundZero = false;
	pi Zero;
	
	loop(i, n) loop(j, n){
		int x; scanf("%d", &x);
		if(x == 0){
			E2[i][j] = E5[i][j] = oo;
			foundZero = true;
			Zero = pi(i, j);
		} else {
			while(x%2 == 0) E2[i][j]++, x /= 2;
			while(x%5 == 0) E5[i][j]++, x /= 5;			
		}
	}
	auto [A, B] = solve(0, 0);
	int ans = min(min(A.first, A.second), min(B.first, B.second));
	if(ans > 1 && foundZero){
		cout << 1 << endl;
		int i = 0, j = 0;
		while(i < Zero.first) putchar('D'), i++;
		while(j < Zero.second) putchar('R'), j++;
		while(i < n-1) putchar('D'), i++;
		while(j < n-1) putchar('R'), j++;
	} else {
		cout << ans << endl;
		int e2 = 0, e5 = 0;
		for(int i = 0, j = 0, x, y; pi(i, j) != pi(n-1, n-1); ){
			assert(i <= n);
			assert(j <= n);
			if(i == n-1){
				putchar('R');
				e2 += E2[i][j];
				e5 += E5[i][j];
				j++;
				continue;
			} else if(j == n-1){
				putchar('D');
				e2 += E2[i][j];
				e5 += E5[i][j];
				i++;
				continue;
			}
			
			tie(A, B) = solve(i, j);
			
			bool choose2 = min(A.first + e2, A.second + e5) <= min(B.first + e5, B.second + e2);
			
			tie(x, y) = A;
			x -= E2[i][j], y -= E5[i][j];
			A = pi(x, y);
			tie(y, x) = B;
			x -= E2[i][j], y -= E5[i][j];
			B = pi(y, x);
			
			e2 += E2[i][j];
			e5 += E5[i][j];
			
			auto [D2, D5] = solve(i+1, j);
			
			if(choose2){
				if(A == D2) putchar('D'), i++;
				else putchar('R'), j++;
			} else {
				if(B == D5) putchar('D'), i++;
				else putchar('R'), j++;
			}
		}
		puts("");
	//	assert(ans == min(e2 + E2[n-1][n-1], e5 + E5[n-1][n-1]));	
	}
	return 0;
}
