#pragma GCC optimize ("O3")
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
#define pl pair<ll,ll>
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

char grid[15][105];
int LEFT[15],RIGHT[15];
int n,m;
int dp[15][2];
bool go[15];


int cost(int floor){
	if(floor == -1) return 0;
	return go[floor];
}

bool done(int floor){
	if(floor == -1) return 1;
	return !go[floor];
}

int solve(int floor,int side){
	if(floor == -1) return 0;
	if(dp[floor][side] != -1) return dp[floor][side];
	int & ret = dp[floor][side]; ret = 1 << 28;
	if(LEFT[floor] == -1){
		ret = cost(floor-1) + min(solve(floor - 1,side),solve(floor - 1,side ^ 1) + m + 1);
	}
	else{
		if(done(floor-1)){
			if(side == 0) ret = RIGHT[floor];
			else ret = m+1-LEFT[floor];
		}
		else{
			if(side == 0){
				ret = m+1 + cost(floor-1) + solve(floor-1,1);
				ret = min(ret,2*RIGHT[floor] + + cost(floor-1) + solve(floor-1,0));
			}
			else{
				ret = m+1 + cost(floor-1) + solve(floor-1,0);
				ret = min(ret,2*(m+1-LEFT[floor]) + cost(floor-1) + solve(floor-1,1));
			}
		}
	}
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	cin >> n >> m;
	loop(i,n) cin >> grid[i];
	memset(LEFT,-1,sizeof LEFT);
	memset(RIGHT,-1,sizeof RIGHT);
	memset(dp,-1,sizeof dp);
	loop(i,n) {
		for(int j = 1;j <= m;j++) if(grid[i][j] == '1') RIGHT[i] = j;
		for(int j = m;j >= 1;j--) if(grid[i][j] == '1') LEFT[i] = j;
		for(int j = 1;j <= m;j++) if(grid[i][j] == '1') go[i] = 1;
		if(i) go[i] |= go[i - 1];
	}

	cout << solve(n-1,0) << endl;
	return 0;
}
