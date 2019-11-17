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

#define plus 0
#define sub 1
#define power 2
#define mul 3

struct node{
	int v;
	bool is_x;
	int op;
	node *l,*r;
	node():v(0),is_x(0),op(-1),l(0),r(0){}
	node(int v,bool x,int op):v(v),is_x(x),op(op),l(0),r(0){}
};


string A,B;

node *reduce(vector<node*> & primary) {
	if(sz(primary) == 1) {
		node *ret = primary.back();
		primary.clear();
		return ret;
	}
	assert(sz(primary) == 2);
	node *cur = new node(0,0,mul);
	cur->l = primary[0];
	cur->r = primary[1];
	primary.clear();
	return cur;
}

node* parse(string A) {
	node *ret = new node();
	vector<node*> primary;
	int sgn = 1;
	for(int i = 0;i < sz(A);i++) {
//		cout << A << " processing " << i << " " << A[i] << endl;
		if(A[i] == 'x') {
			primary.push_back(new node(0,1,-1));
		}
		else if(A[i] == '^') {
			assert(!primary.empty());
			int j = i+1;
			int x = 0;
			sscanf(A.c_str() + j,"%d",&x);
			while(j < sz(A) && isdigit(A[j])) j++;
			i = j-1;
			node *cur = new node(0,0,power);
			cur->l = primary.back(); primary.pop_back();
			cur->r = new node(x,0,-1);
			primary.push_back(cur);
		}
		else if(A[i] == '+' || A[i] == '-') {
			if(!primary.empty()) {
				assert(sz(primary) <= 2);
				node *tmp = reduce(primary);
				node *cur = new node(0,0,(sgn == 1) ? plus : sub);
				cur->l = ret;
				cur->r = tmp;
				ret = cur;
			}
			sgn = (A[i] == '+') ? 1 : -1;
		}
		else if(A[i] == '(') {
			int j = i+1;
			int ctr = 1;
			while(ctr) {
				if(A[j] == '(') ctr++;
				else if(A[j] == ')') ctr--;
				j++;
			}
			int len = j-i-2;
			node *cur = parse(A.substr(i+1,len));
			primary.push_back(cur);
			i = j-1;
		}
		else {
			assert(isdigit(A[i]));
			int j = i;
			int x = 0;
			sscanf(A.c_str() + j,"%d",&x);
			while(j < sz(A) && isdigit(A[j])) j++;
			i = j-1;
			primary.push_back(new node(x,0,-1));
		}
//		for(node *u : primary) cout << "(" << u->v << ", " << u->is_x << ", " << u->op << ")";
//		cout << endl;
	}
	if(!primary.empty()) {
		node *tmp = reduce(primary);
		node *cur = new node(0,0,(sgn == 1) ? plus : sub);
		cur->l = ret;
		cur->r = tmp;
		ret = cur;
	}
//	cout << A << ": ";
	assert(primary.empty());
	return ret;
}

vi add(vi A,vi B) {
	int n = max(sz(A),sz(B));
	vi C(n,0);
	for(int i = 0;i < n;i++) {
		if(i < sz(A)) C[i] += A[i];
		if(i < sz(B)) C[i] += B[i];
	}
	return C;
}
vi Sub(vi A,vi B) {
	int n = max(sz(A),sz(B));
	vi C(n,0);
	for(int i = 0;i < n;i++) {
		if(i < sz(A)) C[i] += A[i];
		if(i < sz(B)) C[i] -= B[i];
	}
	return C;
}
vi Mul(vi A,vi B) {
	int n = sz(A)+sz(B)-1;
	vi C(n,0);
	for(int i = 0;i < sz(A);i++)
		for(int j = 0;j < sz(B);j++)
			C[i+j] += A[i]*B[j];
	return C;
}
vi EXP(vi A,int x) {
	vi B (1,1);
	for(int i = 0;i < x;i++)
		B = Mul(B,A);
	return B;
}

vi interpret(node *root) {
	if(root->op != -1) {
		vi L = interpret(root->l);
		vi R = interpret(root->r);
		vi ret;
		if(root->op == plus) ret = add(L,R);
		else if(root->op == sub) ret = Sub(L,R);
		else if(root->op == mul) ret = Mul(L,R);
		else ret = EXP(L,R[0]);
		return ret;
	}
	vi ret(2,0);
	if(root->is_x) ret[1] = 1;
	else ret[0] = root->v;
	return ret;
}

string toString(vi A) {
	while(!A.empty() && A.back() == 0) A.pop_back();
	if(A.empty()) return "0";
	string res;
	for(int i = sz(A)-1;i >= 0;i--) {
		if(A[i] == 0) continue;
		if(i > 0) {
			if(A[i] > 0) {
				if(!res.empty()) res.push_back('+');
			}
			else res.push_back('-');
			int c = abs(A[i]);
			if(c > 1) res += to_string(c);
			res += "x";
			if(i > 1) res += "^" + to_string(i);
		}
		else {
			if(A[i] > 0) {
				if(!res.empty()) res.push_back('+');
				res += to_string(A[i]);
			}
			else res += to_string(A[i]);
		}
	}
	return res;
}

vi divide(vi A,vi B) {
	while(!A.empty() && A.back() == 0) A.pop_back();
	while(!B.empty() && B.back() == 0) B.pop_back();
	if(sz(A) < sz(B)) return A;
	if(B.empty()) return A;
	int p = sz(A) - sz(B);
	int g = 0;
	for(int x : A) if(x) g = __gcd(g,abs(x));
	for(int x : B) if(x) g = __gcd(g,abs(x));
	for(int & x : A) x /= g;
	for(int & x : B) x /= g;
	vi C(sz(A),0);
	int a = A.back(),b = B.back();

	for(int i = 0;i < sz(B);i++)
		C[i+p] = B[i]*a;
	for(int & x : A) x *= b;
//	cout << toString(A) << " - " << toString(C) << endl;
	return Sub(A,C);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	while(cin >> A && A[0] != '.') {
		cin >> B;
		vi f = interpret(parse(A));
		vi g = interpret(parse(B));
//		cout << "gcd: " << toString(f) << " " << toString(g) << endl;
		while(!g.empty()) {
			vi tmp = divide(f,g);
			f = g;
			g = tmp;
//			cout << toString(f) << " " << toString(g) << endl;
		}
		while(!f.empty() && f.back() == 0) f.pop_back();
		if(f.empty()) f.push_back(0);
		int d = 0,is_neg = 1;
		for(int x : f) if(x) d = __gcd(d,abs(x)),is_neg &= x < 0;
		if(!d) d = 1;
		for(int & x : f) {
			x /= d;
			if(is_neg) x = -x;
		}
		cout << toString(f) << endl;
	}
	return 0;
}
