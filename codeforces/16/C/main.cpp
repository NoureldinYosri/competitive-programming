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

int main(){
	ll a,b,x,y; cin >> a >> b >> x >> y;
	ll d = __gcd(x,y);
	x /= d,y /= d;	
	ll k1 = min(a/x,b/y),k2 = min(a/y,b/x); 
	ll w1 = k1*x,h1 = k1*y;
	ll w2 = k2*y,h2 = k2*x;
	//if(w2*h2 > w1*h1) w1 = w2,h1 = h2;
	cerr << w1 << " " << h1 << endl;
	cout << w1 << " " << h1 << endl;

			
	
	
	return 0;
}
