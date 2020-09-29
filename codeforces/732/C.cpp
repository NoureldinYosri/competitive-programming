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
 
 
 
bool applySuff(ll & nb,ll & nd,ll & ns,int x,ll & cost){
	if(x) ns--;
	if(x > 1) nd--;
	cost += nd < 0;
	cost += ns < 0;
	nd = max(nd,0LL);
	ns = max(ns,0LL);
}
 
void applyPref(ll & nb,ll & nd,ll & ns,int x,ll & cost){
	if(x) nb--;
	if(x > 1) nd--;
	cost += nb < 0;
	cost += nd < 0;
	nb = max(nb,0LL);
	nd = max(nd,0LL);
}
 
ll b,d,s;
 
 
int main(){
	cin >> b >> d >> s;
	ll ans = LLONG_MAX;
	for(int pref = 0; pref < 3;pref++)
		for(int suff = 0;suff < 3;suff++){
			ll nb = b,nd = d,ns = s,cost = 0;
			applyPref(nb,nd,ns,pref,cost);
			applySuff(nb,nd,ns,suff,cost);
			cost += 3*max(nb,max(nd,ns)) - nb - nd - ns;
			ans = min(ans, cost);
		}
	if(b == 0 && s == 0 && d == 1) ans = 0;
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
