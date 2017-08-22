#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

string s1,s2;
int n;

const int MAXN = 52,mod = 1e9 + 7;
int dp[MAXN][4][4];

int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

int solve(int cur,int top,int bottom){
	if(cur == n) return 1;
	if(dp[cur][top][bottom] != -1) return dp[cur][top][bottom];
	int & ret = dp[cur][top][bottom];
	ret = 0;
	if(s1[cur] == s2[cur]) {
		for(int c = 1;c <= 3;c++)
			if(c != top && c != bottom) {
				ret = add(ret,solve(cur+1,c,c));
			}
		return ret;
	}
	if(!cur) {
		for(int c1 = 1;c1 <= 3;c1++)
			for(int c2 = 1;c2 <= 3;c2++)
				if(c1 != c2)
					ret = add(ret,solve(cur + 1,c1,c2));
		return ret;
	}
	bool t = s1[cur] == s1[cur - 1];
	bool b = s2[cur] == s2[cur - 1];
	vi T,B;
	if(t) T = vi{top};
	else {
		range(c,1,3) if(c != top) T.pb(c);
	}
	if(b) B = vi{bottom};
	else {
		range(c,1,3) if(c != bottom) B.pb(c);
	}
	for(int c1 : T) for(int c2 : B) if(c1 != c2) ret = add(ret,solve(cur+1,c1,c2));
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	cin >> n >> s1 >> s2;
	memset(dp,-1,sizeof dp);
	cout << solve(0,0,0) << endl;
	return 0;
}
