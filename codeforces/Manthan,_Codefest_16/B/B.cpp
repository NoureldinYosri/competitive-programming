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


ll f(ll n){
	ll ans = 0;
	ll p = 5;
	while(p <= n){
		ans += n/p;
		p *= 5;
	}
	return ans;
}
int main(){
	int m;
	cin >> m;
	ll s = 0,e = LLONG_MAX;
	while(s < e){
		ll mid = s + ((e - s) >> 1);
		if(f(mid) > m) e = mid;
		else s = mid + 1;
	}
	cerr << endl;
	ll u = s;
	s = 0,e = LLONG_MAX;
	while(s < e){
		ll mid = s + ((e - s) >> 1);
		if(f(mid) >= m) e = mid;
		else s = mid + 1;
	}
	ll l = s;
	printf("%I64d\n",u - l);	
	while(l < u){
		printf("%I64d%s",l,(u - l - 1) ? " " : "\n");
		l++;
	}
	return 0;
}
