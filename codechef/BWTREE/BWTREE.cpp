#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

struct sol{
	ll tot,black,white;
public:
	sol():tot(-1),black(0),white(0){}
	sol(ll a,ll b,ll c):tot(a),black(b),white(c){}
	friend ostream & operator << (ostream & stream,const sol & s){
		stream << "(" << s.tot << "," << s.black << "," << s.white << ")";
		return stream;
	}
};

vi G[1 << 20];
const int mod = 1e9 + 7;
sol dp[1 << 20];
char color[1 << 20];

sol solve(int u,int p){
	if(dp[u].tot != -1) return dp[u];
	dp[u] = sol(0,color[u] == 'B',color[u] == 'W');
	int white = color[u] == 'W',black = 1 - white;
	for(int v : G[u])
		if(v != p) {
			sol x = solve(v,u);
			dp[u].tot += x.tot;
			if(color[u] == 'W') {
				dp[u].tot += dp[u].black * x.black;
				dp[u].black += x.black;
				white += x.black;
			}
			else{
				dp[u].tot += dp[u].white * x.white;
				dp[u].white += x.white;
				black += x.white;
			}
		}
	dp[u].black = black;
	dp[u].white = white;
	dp[u].tot += black + white;
	//cerr << u << " " << dp[u] << endl;	
	return dp[u];
}

int main(){
  	int N,a,b;
	scanf("%d",&N);
	loop(i,N - 1) {
		scanf("%d %d",&a,&b); --a,--b;
		G[a].pb(b);
		G[b].pb(a);
	}
	loop(i,N) scanf(" %c ",color + i);
	ll tot = solve(0,-1).tot;
	tot %= mod;
	cout << tot << endl;
	return 0;
}
