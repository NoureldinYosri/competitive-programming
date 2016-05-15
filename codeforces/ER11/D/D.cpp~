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

ll P[2000][2],n;
vector<pair<pl,ll> > lines;

bool cmp(const pair<pl,ll> & p1,const pair<pl,ll> & p2){
	ll a = p1.xx.yy*p2.xx.xx;
	ll b =  p1.xx.xx*p2.xx.yy;
	return a < b;
}

ll f(vector<ll> V){
	sort(all(V));
	ll ret = 0;
	loop(i,sz(V)){
		int j = i;
		while(j < sz(V) && V[i] == V[j]) j++;
		ll L = j - i;
		ret += L*(L - 1)/2;
		i = j - 1;
	}
	return ret;
}

int main(){
	scanf("%I64d",&n);
	loop(i,n) loop(j,2) scanf("%I64d",&P[i][j]);
	loop(i,n) loop(j,i) {
		ll x = P[i][0] - P[j][0],y = P[i][1] - P[j][1];
		ll l2 = x*x + y*y;
		if(x < 0) x = -x,y = -y;	
		else if(x == 0) y = 1;
		lines.pb(mp(mp(x,y),l2)); 
	}
	sort(all(lines),&cmp);
	ll ans = 0;	
	loop(i,sz(lines)){
		int j = i;
		vector<ll> V;		
		while(j < sz(lines) && !(cmp(lines[i],lines[j]) || cmp(lines[j],lines[i]))) {
			V.pb(lines[j].yy);
			j++;
		}
		ans += f(V);
		i = j - 1; 
	}
	ans >>= 1;
	cout << ans << endl;
	return 0;
}
