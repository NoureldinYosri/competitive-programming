#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;


ll euclid(ll A,ll B,ll & a,ll & b){
	if(!B){
		a = 1;
		b = 0;
		return A;
	}
	ll d = euclid(B,A%B,a,b);
	ll a_new = -b;
	ll b_new = -a - (A/B)*b;
	a = a_new;
	b = b_new;

	return d;
}

void make_nonneg(ll & a,ll & b,ll s1,ll s2){
	if(a >= 0 && b >= 0) return;
	ll x = 0,y = 0;
	if(a < 0) {
		x = (-a + s1 - 1)/s1;
	}
	if(b < 0){
		y = (-b + s2 -1)/s2;
	}
	x = max(x,y);
	a += x*s1;
	b += x*s2;
}

void reduce(ll & a,ll & b,ll s1,ll s2){
	ll x = a/s1,y = b/s2;
	x = min(x,y);
	a -= x*s1;
	b -= x*s2;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	while(T--){
		ll x,y,p,q; scanf("%lld %lld %lld %lld",&x,&y,&p,&q);
		ll A = q - p,B = p,C = p*y-q*x,ans;
		if(C%__gcd(A,B) != 0) ans = -1;
		else if(C == 0) ans = 0;
		else if(A == 0 && B == 0) ans = -1;
		else if(A == 0){
			if(C%B == 0) ans = -C/B;
			else ans = -1;
		}
		else if(B == 0){
			if(C%A == 0) ans = C/A;
			else ans = -1;
		}
		else {
			ll a,b,d = euclid(A,B,a,b);
			ll s1 = B/d,s2 = A/d;
			make_nonneg(a,b,s1,s2);
			reduce(a,b,s1,s2);
			a *= C/d;
			b *= C/d;
			make_nonneg(a,b,s1,s2);
			reduce(a,b,s1,s2);
			ans = a + b;
		}
		if(ans < 0) ans = -1;
		printf("%lld\n",ans);
	}
	return 0;
}
