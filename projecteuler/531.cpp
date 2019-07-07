//#pragma GCC optimize ("O3")
//#include <bits/stdc++.h>
//#define loop(i,n) for(int i = 0;i < (n);i++)
//#define range(i,a,b) for(int i = (a);i <= (b);i++)
//#define all(A) A.begin(),A.end()
//#define pb push_back
//#define mp make_pair
//#define sz(A) ((int)A.size())
//#define vi vector<int>
//#define vd vector<double>
//#define vp vector<pair<int,int> >
//#define ll long long
//#define pi pair<int,int>
//#define popcnt(x) __builtin_popcountll(x)
//#define LSOne(x) ((x) & (-(x)))
//#define xx first
//#define yy second
//#define PQ priority_queue
//#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
//#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
//#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
//#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
//#define what_is(x) cerr << #x << " is " << x << endl
//#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
//using namespace std;
//
//const int LOW = 1000000,UP = 1005000,LEN = UP - LOW + 1;
//
//int prime[UP+1],phi[UP+1];
//void sieve(){
//	phi[1] = 1;
//	for(int i = 2;i <= UP;i++){
//		if(prime[i] == 0) {
//			prime[i] = i;
//			for(ll j = i*(ll)i;j <= UP;j += i)
//				prime[j] = i;
//		}
//		int p = prime[i],q = 1,m = i;
//		while(m%p == 0) m /= p,q *= p;
//		phi[i] = phi[m]*(q - q/p);
//	}
//}
//
//int extendedEuclid(int a,int b,ll & x,ll & y) {
//	if(b == 0) {
//		x = 1;
//		y = 0;
//		return a;
//	}
//	int d = extendedEuclid(b,a%b,x,y);
//	// b*x + y*(a - (a/b)*b) = d
//	// y*a + (x - (a/b)*y)*b = d
//	ll t = x;
//	x = y;
//	y = t - (a/b)*y;
//	return d;
//}
//
//ll g(int n,int m) {
//	int a = phi[m],b = phi[n];
//	ll u,v;
//	int g = extendedEuclid(m,n,u,v);
//	if(a%g != b%g) return 0;
//	assert(a%g == b%g);
//	ll lcm = m*(ll)(n/g);
//	auto f = [a,b,n,m,g,lcm](const ll u,const ll v) {
//		ll res = (a*v*(n/g) + b*u*(m/g));
//		res = (res%lcm + lcm)%lcm;
//		return res;
//	};
//	ll res = f(u,v);
//	assert(res%n == phi[n]);
//	assert(res%m == phi[m]);
//	return res;
//}
//
//int main(int argc,char **argv){
//	sieve();
//	ll ans = 0;
//	for(int m = LOW;m < UP;m++){
//		for(int n = LOW;n < m;n++){
//			ll x = g(n,m);
//			ans += x;
//		}
//	}
//	cout << ans << endl;
//	return 0;
//}
