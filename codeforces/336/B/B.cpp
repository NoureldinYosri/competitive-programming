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

string u,v;

vi zero,one;

int main(){
	pre();
	cin >> u >> v;
	loop(i,len(v)){
		if(v[i] == '0') zero.pb(i);
		else one.pb(i);
	}
	ll ans = 0;
	loop(i,len(u)){
		vi *V;
		if(u[i] == '0') V = & one;
		else V = & zero;
		ans += upper_bound(V->begin(),V->end(),len(v) - len(u) + i) - lower_bound(V->begin(),V->end(),i);
	}
	cout << ans << endl;
	//cerr << ans << endl;
	return 0;
}
