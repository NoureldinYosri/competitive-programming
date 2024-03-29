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

const int MAXN = 5000 + 10;
int A[MAXN], n;
int nxt[MAXN];
int bestIndex[MAXN][MAXN];

int dp[MAXN][MAXN];
int solve(int s, int e, int h0){
	if(e-s-1 <= 0) return 0;
	int & ret = dp[s][e];
	if(ret != -1) return ret;
	ret = e-s-1;
	int h = A[bestIndex[s + 1][e - 1]];
	int prv = s;
	ll  tmp = h - h0;
	for(int i = bestIndex[s + 1][e - 1]; i < e; i = nxt[i]) {
		tmp += solve(prv, i, h);
		prv = i; 		
	}
	tmp += solve(prv, e, h);
	ret = min(ret + 0LL, tmp);
//	cerr << s << " " << e << ": " << ret << endl;
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", A + i);
	}	
	for(int i = 1; i <= n; i++) {
		int mn = -1;
		for(int j = i; j <= n; j++){
			if(mn == -1) mn = j;
			else if(A[j] < A[mn]) mn = j;
			bestIndex[i][j] = mn;
		}
	}
	map<int, int> lst;
	for(int i = n; i; i--){
		if(lst.count(A[i])) nxt[i] = lst[A[i]];
		else nxt[i] = n + 1;
		lst[A[i]] = i;
	}
	memset(dp, -1, sizeof dp);
	cout << solve(0, n + 1, 0) << endl;

	return 0;
}
