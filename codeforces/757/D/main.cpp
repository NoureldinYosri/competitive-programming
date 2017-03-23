#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
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
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int mod = 1e9 + 7;
char line[80];
int n;
int dp[76][1 << 20];
int m;

bool correct(int x){
	if(!x) return 0;
	x ++;
	return x == LSOne(x);
}

int solve(int pos,int msk){
	if(pos == n) return correct(msk);
	if(dp[pos][msk] != -1) return dp[pos][msk];
	int & ret = dp[pos][msk]; ret = correct(msk);
	int num = 0;
	for(int e = pos; e < n;e++){
		num = (num << 1) + line[e] - '0';
		if(num > 20) break;
		if(!num) continue;
		ret += solve(e+1,msk | (1 << (num - 1)));
		if(ret >= mod) ret -= mod;
	}
	return ret;
}

int main(){
	memset(dp,-1,sizeof dp);
	scanf("%d %s",&n,line);
	int ans = 0;
	loop(s,n) {
		int tmp = solve(s,0);
		ans += tmp;
		if(ans >= mod) ans -= mod;
	}
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
