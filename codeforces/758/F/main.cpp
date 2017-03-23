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

const int MAX = 10'000'000;
int prime[MAX + 1];
int n,l,r;

void sieve(){
	for(int i = 2;i <= MAX;i++)
		if(!prime[i]){
			prime[i] = i;
			for(ll j = i*1LL*i;j <= MAX;j += i)
				prime[j] = i;
		}
}



vp factor(int x){
	vp ret;
	while(x > 1){
		int p = prime[x],e = 0;
		while(x%p == 0){
			x /= p;
			e++;
		}
		ret.pb(mp(p,e));
	}
	return ret;
}

int get_lim(int a,int div){
	// a*x^(n-1)/div^(n-1) <= r
	double ret = r*1.0/a;
	if(div != 1) loop(i,n-1) ret *= div;
	return pow(ret,1/(n - 1.0)) + 1e-9;
}

int get_cnt(int div,int lim,vp & V){
	if(lim <= div) return 0;
	int x = 0,y = 0;
	loop(msk,1 << sz(V)){
		int m = 1,sgn = 1;
		loop(i,sz(V)){
			if(msk & (1 << i)) m *= V[i].xx,sgn*=-1;
		}
		x += sgn * (lim/m);
//		y += sgn * ((max(div,l-1))/m);
		y += sgn * (div/m);
	}
	int ret = x - y;
//	cerr << div << " " << lim << " " << ret << endl;
	return ret;
}

int main(){
	sieve();	
	cin >> n >> l >> r;
	ll ans = 0;
	if(n == 1) ans = r - l + 1;
	else if(n == 2) ans = (r - l)*(r - l + 1LL);
	else{
		for(int div = 1;div <= r;div++){
			ll x = 1;
			loop(i,n-1) {
				x *= div;
				if(x > r) break;
			}
			if(x > r) break;
			vp V = factor(div);
			for(int a = ((l + x - 1)/x)*x;a <= r;a += x){
				int lim = get_lim(a,div);
				int tmp = get_cnt(div,lim,V);
				ans += tmp;
			}
		}
		ans <<= 1;
	}
	cerr << ans << endl;
	cout << ans << endl;

	
	return 0;
}
