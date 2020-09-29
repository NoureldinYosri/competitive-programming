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

struct Seq{
	vector<ll> V;
	bool free_prefix;
	int s, e;
	Seq(){}
	Seq(const vector<ll> & ST, bool l, bool r){
		V = vector<ll>(ST);
		s = 0;
		e = sz(V)-1;
		if(l && r) free_prefix = 1;
		else {
			free_prefix = 0;
			if(l) reverse(all(V));
		}
	}
	
	ll get_max(){
		if(free_prefix) return max(V[s], V[e]);
		return V[e];
	}
	
	void pop(){
		if(free_prefix){
			ll mi = max(V[s], V[e]);
			if(V[e] == mi) e--;
			else s++;
		}
		else e--;
	}
	bool is_empty(){
		return s > e;
	}
	int get_size(){
		return e-s+1;
	}
};



vector<Seq> S;

int A[1 << 20], n;
vector<ll> ST;

void merge(int s, int e){
	ST.clear();
	for(int i = s; i <= e;i ++){
		int x = A[i];
		ST.pb(x);
		while(sz(ST) > 2 && ST[sz(ST)-3] <= ST[sz(ST)-2] && ST.back() <= ST[sz(ST)-2]){
			ll c = ST.back(); ST.pop_back();
			ll b = ST.back(); ST.pop_back();
			ll a = ST.back(); ST.pop_back();
			ST.pb(a-b+c);
		}
	}
	if(ST.empty()) return;
	S.emplace_back(ST, s != 0, e != n-1);
//	print(ST, int);
}

ll trim(Seq & s, int sgn){
	if(s.free_prefix) return 0;
	ll diff = 0;
	while(s.get_size() > 1 && s.V[s.s] >= s.V[s.e]){
		ll M = s.V[s.s++];
		ll x = s.V[s.s++];
		diff += sgn*(x - M);
	}
	return diff;
}

ll play(){
	ll diff = 0;
	int sgn = 1;
	for(const Seq & s : S){
		if(sz(s.V) & 1) sgn *= -1;
	}
	for(Seq & s : S) diff += trim(s, sgn);
	
	
	set<pair<ll, int> > MS;
	
	int s = 1;
	
	
	loop(i, sz(S)) if(!S[i].is_empty()) {
		MS.emplace(S[i].get_max(), i);
//		cerr << "+ " << i << " " << S[i].get_max() << endl;
	}
	while(!MS.empty()){
		int i = MS.rbegin()->second;
//		cerr << "- " << i << endl;
		
		diff += s*S[i].get_max();
		s = -s;

		S[i].pop();
		sgn = -sgn;
		MS.erase(*MS.rbegin());

		diff += s*trim(S[i], sgn);
		if(!S[i].is_empty()) {
//			cerr << "+ " << i << " " << S[i].get_max() << endl;
			MS.emplace(S[i].get_max(), i);
		}
	}
	
	
	
	return diff;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	int l = -1;
	loop(i, n) if(!A[i]){
		merge(l+1, i-1);
		l = i;
	}
	merge(l+1, n-1);
	ll sum = 0;
	loop(i, n) sum += A[i];
	
	
	ll diff = play();
	
	assert((sum + diff)%2 == 0);
	
	ll a = (sum + diff)/2;
	ll b = sum - a;
	cout << a << " " << b << endl;
	return 0;
}
