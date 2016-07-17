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
using namespace std;

ll dp[10][301];
ll solve(int s,int l){
	if(l == 0) return s == 0;
	if(dp[s][l] != -1) return dp[s][l];
	dp[s][l] = 0;
	loop(i,s + 1) dp[s][l] += solve(s - i,l - 1);
	return dp[s][l];
}

ll get_idx(ll x,int s,int l,ll p10){
	if(p10 == 0) return 0;
	int d = x/p10;
	ll sum = 0;
	loop(i,d) sum += solve(s - i,l - 1);
	return sum + get_idx(x%p10,s - d,l - 1,p10 / 10);
}

void build(int s,int l,ll idx,bool c){
	if(!l) return;
	ll sum = 0;	int d = 0;
	while(d <= s){
		sum += solve(s - d,l - 1);
		if(sum > idx) break;
		d += 1;
	}
	sum -= solve(s - d,l - 1);
	if(d || c) putchar(d + '0');
	build(s - d,l - 1,idx - sum,c | (d > 0) );
}

int main(){
	fill(&dp[0][0],&dp[10][0],-1);
	int T; ll x,d;
	scanf("%d",&T);
	while(T--){
		scanf("%lld %lld",&x,&d);
		build(9,300,d + get_idx(x,9,16,1000000000000000LL),0);
		puts("");
	}	
	return 0;
}
