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

const int MAX = 100'010;
int n; ll k;
ll S[MAX];
int A[MAX];
map<ll,int> dp;

ll solve(ll t){
	dp.clear();
	dp[0]++;
	ll ret = 0;
	loop(i,n){
		ll v = S[i] - t;
		if(dp.find(v) != dp.end()) ret += dp[v];
		dp[S[i]]++;
	}
	return ret;
}

int main(){
	scanf("%d %lld",&n,&k);
	ll mx = 0;
	loop(i,n) {
		scanf("%d",A + i);
		S[i] = A[i] + (i ? S[i - 1] : 0);	
		mx = max(mx,abs(S[i]));
	}
	ll ans = 0;
	if(k == 1) ans = solve(1);
	else if(k == -1) ans = solve(-1) + solve(1);
	else {
		ll q = 1;
		for(int i = 0;i < 64;i++){
			ans += solve(q);
			if(abs(q) >= LLONG_MAX/abs(k)) break;
			q *= k;
		}
	}
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
