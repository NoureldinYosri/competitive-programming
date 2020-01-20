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

char S[10][10];
int n;
int dp[4][1 << 10];

int solve(int p, int msk) {
	if(!msk || (msk == LSOne(msk))) return 0;
	if(p == 4) return 1 << 29;
	int & ret = dp[p][msk];
	if(ret != -1) return ret;
	vi V,who[10];
	for(int i = 0,j = 0;i < n;i++)
		if(msk & (1 << i)){
			V.push_back(i);
			who[S[i][j]-'0'].push_back(i);
		}
	
	ret = 1 << 29;
	for(char c = '0'; c <= '9'; c++){
		int smsk = 0;
		int tmp = sz(V);
		for(int i : V)
			if(S[i][p] == c)
				smsk |= 1 << i,tmp--;
		ret = min(ret, solve(smsk) + tmp);
	}
	
	
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d",&n);
		loop(i,n) scanf("%s", S[i]);
		memset(dp, -1, sizeof dp);
		printf("%d\n", solve(0, (1 << n) - 1));
	}
	return 0;
}
