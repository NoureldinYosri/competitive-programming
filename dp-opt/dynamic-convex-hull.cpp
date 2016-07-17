#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

const int INF = INT_MAX;

struct line{
	int a,b;
	int left;
	line(){} 
	line(int a,int b,int c):a(a),b(b),left(c){}
	friend ostream& operator<<(ostream &stream, const line &v) {
		stream << "(" << v.a << " ," << v.b << " ," << v.left << " )";
		return stream;
	}
};
struct cmp1{
public:
	bool operator () (const line l1,const line l2){
		if(l1.a == l2.a){
			if(l1.b == l2.b) return l1.left < l2.left;
			else return l1.b < l2.b;
		}
		else return l1.a < l2.a;
	}
};
struct cmp2{
public:
	bool operator () (const line l1,const line l2){
		if(l1.left == l2.left){
			if(l1.a == l2.a) return l1.b < l2.b;
			else return l1.a < l2.a;
		}
		else return l1.left < l2.left;
	}
};

//u.a * x + u.b <= v.a * x + v.b
//x <= (v.b - u.b)/(u.a - v.a)
//      0 - 12 / 5 - 6 13
inline long double g(line u,line v){
	//cout << u << " " << v << " " << (v.b - u.b + 0.0)/(u.a - v.a + 0.0) << endl;
	return (v.b - u.b + 0.0)/(u.a - v.a);
}

inline ll f(line u,ll x){
	return u.a * x + u.b;
}

set<line,cmp1> S;
set<line,cmp2> Z;

void insert_new_line(line u){
	u.left = INF;
	while(sz(S)){
		auto p = S.upper_bound(u);
		if(p == S.begin()) break;
		--p;
		if(p->a == u.a)
			if(p->b <= u.b) {
				Z.erase(Z.find(*p));
				S.erase(p);
			}
			else return;
		else
			break; 
	}
	while(sz(S) > 1){
	//	cout << "here" << endl;
		auto p = S.upper_bound(u);
		if(p == S.begin()) break;
		--p;
		if(p == S.begin()) break;
		auto t = p;
		--t;
		if(g(*t,u) <= g(*t,*p)) {
			Z.erase(Z.find(*p));
			S.erase(p);	
		}
		else break; 
	}
	while(sz(S) > 1){
	//	cout << "here" << endl;
		auto p = S.upper_bound(u);
		if(p == S.end()) break;
		auto t = p;
		++t;
		if(t == S.end()) break;
		if(g(u,*p) >= g(*p,*t)) {
			Z.erase(Z.find(*p));
			S.erase(p);	
		}
		else break; 
	}
	auto p = S.upper_bound(u);
	if(p == S.end()) u.left = INT_MAX;
	else{
		u.left = g(u,*p);
		if(p != S.begin()){
			--p;
			auto tt = *p;
			S.erase(p);
			Z.erase(Z.find(tt));
			tt.left = g(tt,u);
			S.insert(tt);
			Z.insert(tt);	
		}
	}	
	S.insert(u);
	Z.insert(u);
}

int main(){
	int a,b;
	while(cin >> a >> b){
		ll c;
		if(sz(Z)) {
			auto p = Z.lower_bound(line(INT_MAX,INT_MAX,a));
//			cout << *p << endl;
			c = f(*p,a);
		}
		else c =  0;
		cout << c << endl;
		insert_new_line(line(b,c,0));
//		for(auto l : Z) cout << l << endl;
	}
}
