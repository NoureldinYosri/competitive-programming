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

vl pref[4];
int n,m;
ll dp[300000 + 10];

void work(int s,vl one,vl two){
	if(s == 1) {
		if(!one.empty()) {
			dp[1] = one.back();
			one.pop_back();
		}
		s += 2;
	}
	for(;s <= m;s += 2){
		dp[s] = dp[s - 2];
		ll x = 0,y = 0;
		if(!two.empty()) x = two.back();
		int siz = one.size();
		if(siz >= 2) y = one[siz - 1] + one[siz - 2];
		if(x + y == 0) continue;
		if(x >= y){
			dp[s] += x;
			two.pop_back();
		}
		else{
			dp[s] += y;
			one.pop_back();
			one.pop_back();
		}
	}
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	loop(i,n){
		int w,c; scanf("%d %d",&w,&c);
		pref[w].pb(c);
	}
	loop(i,4) sort(all(pref[i]));
	work(2,pref[1],pref[2]);
	work(1,pref[1],pref[2]);
	range(i,1,m) dp[i] = max(dp[i],dp[i - 1]);
	prArr(dp,m+1,ll);
	ll sum = 0;
	reverse(all(pref[3]));
	for(ll & x : pref[3])
		x = sum += x;
	ll ans = 0;
	for(int i = 0;i <= sz(pref[3]) && 3*i <= m;i++){
		ll tmp = i ? pref[3][i - 1] : 0;
		tmp += dp[m - 3*i];
		ans = max(ans,tmp);
	}
	cout << ans << endl;
	return 0;
}
