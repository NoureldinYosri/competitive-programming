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


const int MAX = 20* 1000 + 10, MAXN = 55;
int n, m, k;
int A[MAXN][MAX];
ll S[MAXN][MAX];
ll dp[2][MAX];

ll get_overlap(int i, int j, ll *S){
	if(i > j) swap(i, j);
	assert(j-i < k);
	return S[i+k-1] - (j ? S[j-1] : 0);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d", &n, &m, &k);
	loop(i, n) loop(j, m) {
		scanf("%d", &A[i][j]);
		S[i][j] = A[i][j];
		S[i][j] += j ? S[i][j-1] : 0;
	}
	int cur = 0, other = 1;
	for(int i = n-1;i >= 0;i--){
		swap(cur, other);
		loop(j, m-k+1){
			dp[cur][j] = 0;
			for(int q = max(j-k+1, 0); q < min(j+k, m); q++){
				ll tmp = dp[other][q] - get_overlap(q, j, S[i+1]);
				dp[cur][j] = max(dp[cur][j], tmp);
			}
		}
		
		ll mx = 0;
		for(int j = 0;j < m-k+1;j++){
			if(j-k >= 0) mx = max(mx, dp[other][j-k]);
			dp[cur][j] = max(dp[cur][j], mx);
		}
		
		mx = LLONG_MIN;
		for(int j = m-k;j >= 0;j--){
			if(j+k < m) mx = max(mx, dp[other][j+k]);
			dp[cur][j] = max(dp[cur][j], mx);
		}
		loop(j, m-k+1) {
			dp[cur][j] += S[i][j+k-1] - (j ? S[i][j-1] : 0) + S[i+1][j+k-1] - (j ? S[i+1][j-1] : 0);
		}
//		prArr(dp[cur], m, ll);
	}
	
	cout << *max_element(dp[cur], dp[cur] + m - k+1) << endl;
	
	return 0;
}
