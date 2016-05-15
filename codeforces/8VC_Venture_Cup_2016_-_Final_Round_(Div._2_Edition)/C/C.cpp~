#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

ll dp[50][2];
ll x,s;

ll solve(int p,int c){	
	if(((1LL << p) > s) && ((1LL << p) > x)) return c == 0;
	if(dp[p][c] != -1) return dp[p][c];
	dp[p][c] = 0;	
	loop(i,2) loop(j,2){
		int z = i + j + c;
		int sb = (s >> p) & 1LL;
		int xb = (x >> p) & 1LL;
		if(xb == (i ^ j) && sb == (z & 1)){
			dp[p][c] += solve(p + 1,z / 2);
		}
	}
	//cerr << p << " " << c << " " << dp[p][c] << endl;
	return dp[p][c];
}

int main(){
	cin >> s >> x;
	fill(&dp[0][0],&dp[50][0],-1);
	ll ans = solve(0,0);
	ans -= 2*(x == s);
	cout << ans << endl;
	return 0;
}
