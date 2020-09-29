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


const int MAX = 111;
int n, m;
int dp[MAX][MAX];
vi L[MAX], R[MAX];

int f(int s, int e, int k){
	int ret = 0;
	loop(r, n) {
		int i = lower_bound(all(R[r]), k) - R[r].begin();
		ret += s <= L[r][i] && R[r][i] <= e;
	}
	return ret*ret;
}

int solve(int l, int r){
	if(l > r) return 0;
	int & ret = dp[l][r];
	if(ret != -1) return ret;
	ret = 0;
	for(int k = l; k <= r; k++) {	
		ret = max(ret, solve(l, k-1) + f(l, r, k) + solve(k + 1, r));
	}
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(i, n){
		int k; scanf("%d", &k);
		loop(j, k){
			int l, r; scanf("%d %d", &l, &r);
			L[i].push_back(l);
			R[i].push_back(r);
		}
	}
	memset(dp, -1, sizeof dp);
	cout << solve(1, m) << endl;
	return 0;
}
