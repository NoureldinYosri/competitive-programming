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


const int MAX = 1111;
int n;
int V[MAX];
char S[MAX];
int visNum[MAX][MAX],visID;
ll dp[MAX][MAX];
ll sum[MAX][MAX];

bool can(int a,int b) {
	return S[a] == '(' && S[b] == ')';
}

ll solve(int s,int c) {
	if(s == n) return 0;
	ll & ret = dp[s][c];
	int & vis = visNum[s][c];
	if(vis == visID) return ret;
	vis = visID;
	ret = 0;
	if(c) ret = solve(s,c-1);
	if(S[s] == '(') ret = max(ret,solve(s+1,c+1));
	else ret = max(ret,sum[s][c]*V[s] + solve(s+1,c));
//	cerr << s << " " << c << ": " << ret << endl;
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	tc(){
		scanf("%d %s",&n,S);
		loop(i,n) scanf("%d",V + i);
		visID++;
		loop(i,n) loop(c,n+1) sum[i][c] = 0;
		for(int j = 0;j < n;j++) {
			int i = j,c = 0;
			ll s = 0;
			while(i >= 0) {
				if(S[i] == '(')
					s += V[i],c++;
				sum[j][c] = s;
				i--;
			}
		}
		printf("%lld\n",solve(0,0));
	}
	return 0;
}
#endif
