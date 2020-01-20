#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;


struct rational{
	ll a,b;
	rational():a(0),b(1){}
	rational(ll x,ll y){
		ll g = __gcd(x,y);
		a = x/g;
		b = y/g;
		assert(a >= 0 && b > 0);
	}
	bool operator < (const rational & o) const {
		return a*o.b < b*o.a;
	}
	friend ostream& operator << (ostream & st, const rational & r) {
		st << r.a << "/" << r.b;
		return st;
	}
};


struct Event{
	rational t;
	int i,j;
	int p;
	Event(){}
	Event(rational _t, int _i, int _j, int _p){
		t = _t;
		i = _i;
		j = _j;
		p = _p;
	}
	bool operator < (const Event & e) const {
		return t < e.t;
	}
	friend ostream& operator << (ostream & st, const Event & e){
		st << "(" << e.t << ", " << e.i << ", " << e.j << ", " << e.p << ")";
		return st;
	}
};


const int mod = 998244353;
int mul(int a,int b){
	return (a*(ll)b)%mod;
}
int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int powmod(int a,int x){
	if(x == 0) return 1;
	int b = 1;
	for(;x > 1;x >>= 1){
		if(x&1) b = mul(a,b);
		a = mul(a,a);
	}
	return mul(a,b);
}
int inv(int a){
	return powmod(a, mod-2);
}

const int MAX = 100*1000 + 10;
int n;
int X[MAX],V[MAX],P[MAX],notP[MAX];
vector<Event> events;

pair<int, pi> lst[MAX];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n; scanf("%d",&n);
	int inv100 = inv(100);
	for(int i = 1;i <= n;i++) {
		scanf("%d %d %d",X + i, V+i, P+i);
		notP[i] = 100 - P[i];
		P[i] = mul(P[i], inv100);
		notP[i] = mul(notP[i], inv100);
	}
	
	for(int i = 1;i+1 <= n;i++){
		int dx = X[i+1] - X[i];
		int j = i+1;
		events.emplace_back(rational(dx, V[i+1] + V[i]), i, -j, mul(P[i], notP[i+1]));
		if(V[i] > V[i+1]) events.emplace_back(rational(dx, V[i] - V[i+1]), i, j, mul(P[i], P[i+1]));
		else if(V[i] < V[i+1]) events.emplace_back(rational(dx, V[i+1] - V[i]), -i, -j, mul(notP[i], notP[i+1]));
	}
	
	sort(all(events));
	reverse(all(events));
	while(!events.empty() && events.back().p == 0) events.pop_back();
	reverse(all(events));
	for(auto e : events) cout << e << " " ;
	cout << endl;
	
	int res = 0;
	int P = 1;
	for(auto e : events){
		int t_m = mul(e.t.a, inv(e.t.b));
		int tmp = mul(t_m, e.p);
		
		res = add(res ,mul(P, tmp));
		P = mul(P, add(100, - e.p));
	}
	cout << res << endl;
	
	return 0;
}
