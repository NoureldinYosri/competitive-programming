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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

struct rational{
	ll a,b;
	rational():a(0),b(1){}
	rational(ll x,ll y):a(x),b(y){}
	bool operator == (const rational & o) const {
		return a*o.b == b*o.a;
	}
	bool operator < (const rational & o) const {
		return a*o.b < b*o.a;
	}
	bool operator <= (const rational & o) const {
		return a*o.b <= b*o.a;
	}

	friend ostream& operator << (ostream& st,const rational & r) {
		st << r.a << "/" << r.b;
		return st;
	}
};

struct node{
	map<rational,rational> S;
	node *l,*r;
};

void insert(rational l,rational r,map<rational,rational> & S) {
	static vector<rational> aux;
	auto ptr = S.lower_bound(r);
	if(ptr == S.end() || r < ptr->second) {
		S[r] = l;
		ptr = S.find(r);
	}
	else {
		r = ptr->first;
		l = min(ptr->second,l);
	}
	while(ptr != S.begin()) {
		ptr--;
		if(l <= ptr->first) {
			l = min(l,ptr->second);
			aux.push_back(ptr->first);
		}
		else break;
	}
	S[r] = l;
	for(auto x : aux) S.erase(x);
	aux.clear();
}

node* update(node *root,ll s,ll e,rational l,rational r,ll h) {
	if(!root) root = new node();

	insert(l,r,root->S);

	if(s == e) return root;
	ll m = s + (e-s)/2;
	if(h <= m) root->l = update(root->l,s,m,l,r,h);
	else root->r = update(root->r,m+1,e,l,r,h);
	return root;
}

ll query(node *root,ll s,ll e,rational l,rational r) {
	if(!root) return 0;
	map<rational,rational> & S = root->S;
	auto ptr = S.lower_bound(l);
//	cout << "@" << s << " " << e << " S = ";
//	for(auto p : S) cout << p << " ";
//	cout << endl;
	if(ptr == S.end() || r < ptr->second) return 0;
//	cout << "@" << s << " " << e << ": " << *ptr << " intersects " << l << " " << r << endl;
	if(s == e) return s;

	ll m = s + (e-s)/2;
	ll res = query(root->r,m+1,e,l,r);
	if(res) return res;
	return query(root->l,s,m,l,r);
}

inline rational readRational(ll v) {
	ll a,b;
	scanf("%lld %lld",&a,&b);
	a ^= v,b ^= v;
	ll g = __gcd(a,b);
	a /= g;
	b /= g;
	return rational(a,b);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
//	freopen("out.out","w",stdout);
#endif
	int n; scanf("%d",&n);
	ll res = 0;
	ll B = 1LL << 32;
	node *root = update(0,0,B,rational(0,1),rational(B,1),0);
	while(n--) {
		char c; scanf(" %c",&c);
		rational l = readRational(res);
		rational r = readRational(res);
		if(c == 'B') {
			ll h; scanf("%lld",&h);
			h ^= res;
			root = update(root,0,B,l,r,h);
		}
		else {
//			cout << "? " << l << " " << r << endl;
			printf("%lld\n",res = query(root,0,B,l,r));
		}
	}
	return 0;
}
