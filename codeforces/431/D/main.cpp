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

ll t; int k;
ll C[65][65];

ll add(ll x,ll y){
	if(x >= LLONG_MAX - y) return LLONG_MAX;
	return x + y;
}

ll g(ll n){
	int q = k; ll ret = 0;
	for(int i = 61;i >= 0 && q;i--){
		if(n & (1LL << i)) {
			ret = add(ret, C[i][q]);
			q--;
		}
	}
	ret = add(ret ,q == 0);
	return ret;
}

ll f(ll n){
	return g(2*n) - g(n);
}

int main(){
	loop(i,65){
		C[i][0] = C[i][i] = 1;
		range(j,1,i-1) C[i][j] = add(C[i - 1][j - 1] ,C[i - 1][j]); 
	}
	cin >> t >> k;
	ll s = 1,e = 1LL << 61;
	while(s < e){
		ll m = s + (e - s) / 2;
		if(f(m) >= t) e = m;
		else s = m + 1;
	}
	cout << s << endl;
	return 0;
}
