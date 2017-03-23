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

ll n;
ll a,b;

ll f(ll a,ll b){
	return (a*b)/6;
}

int main(){
	cin >> n >> a >> b;
	if(f(a,b) < n){	
		ll ta = INT_MAX,tb = INT_MAX;
		for(int offset = 10;(a*a <= 6*n || offset--);a++){
			ll lb = (6*n + a - 1)/a;
			lb = max(lb,b);
			if(a*lb < ta*tb) ta = a,tb = lb;
		}
		for(int offset = 10;(b*b <= 6*n || offset--);b++){
			ll la = (6*n + b - 1)/b;
			la = max(la,a);
			if(la*b < ta*tb) ta = la,tb = b;
		}
		a = ta,b = tb;	
	}
	cout << a*b << endl;
	cout << a << " " << b << endl;
	cerr << a*b << endl;
	
	return 0;
}
