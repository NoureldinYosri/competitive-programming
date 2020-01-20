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


const int MAXN = 111;
int ctr[2];
int P[MAXN],n;
int dp[MAXN][MAXN][MAXN][2];
bool in[MAXN];

int solve(int i,int even_cnt, int odd_cnt, bool prv){
	assert(even_cnt >= 0 && odd_cnt >= 0);
	if(i == n) return 0;
	int & ret = dp[i][even_cnt][odd_cnt][prv];
	if(ret != -1) return ret;
	int cand[2] = {0,1},ctr[] = {even_cnt, odd_cnt};
	int d = 1;
	if(P[i] != -1) cand[0] = cand[1] = P[i],d = 0;
	ret = 1 << 29;
	loop(q, 2){
		int k = cand[q];
		if(d > ctr[k]) continue;
		int tmp = solve(i + 1, even_cnt - d*(k == 0), odd_cnt - d*(k == 1), k);
		if(i && k != prv) tmp++;
		ret = min(ret, tmp);
	}
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",P + i);
		in[P[i]] = 1;
		if(P[i] == 0) P[i] = -1;
		else P[i] &= 1;
	}
	for(int i = 1;i <= n;i++)
		if(!in[i])
			ctr[i&1]++;
	memset(dp, -1, sizeof dp);
	cout << solve(0, ctr[0], ctr[1], 0) << endl;
	return 0;
}
