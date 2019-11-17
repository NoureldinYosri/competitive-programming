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

const int MAX = 452;

int n,K;
char S[1 << 20];
ll dp[MAX][MAX];
int C[MAX][MAX];

ll solve(int i,int s) {
	if(i == n) return 0;
	ll & ret = dp[i][s];
	if(ret != -1) return ret;
	if(S[i] == '0') return ret = solve(i+1,s);
	ret = 1LL << 60;
	C[i][s] = -1;
	int sum = 0,k = 0,j;
	for(j = i;j < n;j++){
		if(S[j] == '0') {
			ret = min(ret,sum + solve(j+1,s));
			break;
		}
		if(s) ret = min(ret,solve(j+1,s-1) + sum);
		++k;
		sum += k;
	}
	if(j == n) ret = min(ret,(ll)sum);
//	cout << i << " " << s << ": " << ret << endl;
	return ret;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> n >> K >> S;
	memset(dp,-1,sizeof dp);
	for(int s = 0;s <= n;s++)
		if(solve(0,s) <= K){
			cout << s << endl;
			return 0;
		}
	return 0;
}
#endif
