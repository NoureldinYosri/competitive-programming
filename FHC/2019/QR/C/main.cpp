#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
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
using namespace std;


int fAnd(int a,int b) {
	if(a > b) swap(a,b);
	if(a == 0) return 0;
	if(a == 1) return b;
	if(a == 2) return (b == 2) ? 2 : 0;
	// a = 3 && b >= a
	return 3;
}

int fOr(int a,int b) {
	if(a > b) swap(a,b);
	if(a == 0) return b;
	if(a == 1) return 1;
	if(a == 2) return (b == 2) ? 2 : 1;
	return 3;
}

int Not(int x){
	if(x <= 1) return x^1;
	if(x == 2) return 3;
	return 2;
}

int fXor(int a,int b){
	if(a > b) swap(a,b);
	if(a == 0) return b;
	if(a == 1) return Not(b);
	if(a == 2) return (b == 2) ? 0 : 1;
	return 0;
}

string out = "01xX";
char E[333];
int n;
typedef int boolFunc(int,int) ;

int evaluate() {
	vector<int> vals;
	vector<char> op;
	loop(i,n){
		if(E[i] == '(') continue;
		if(E[i] == ')') {
			assert(sz(vals) > 1 && !op.empty());
			char c = op.back(); op.pop_back();
			int x = vals.back(); vals.pop_back();
			int y = vals.back(); vals.pop_back();
			auto f = (c == '|') ? fOr : (c == '&' ? fAnd : fXor);
			vals.push_back(f(x,y));
		}
		else if(E[i] == 'x') vals.push_back(2);
		else if(E[i] == 'X') vals.push_back(3);
		else if(E[i] == '0') vals.push_back(0);
		else if(E[i] == '1') vals.push_back(1);
		else op.push_back(E[i]);
	}
	assert(sz(op) <= 1);
	if(!op.empty()) {
		assert(sz(vals) > 1 && !op.empty());
		char c = op.back(); op.pop_back();
		int x = vals.back(); vals.pop_back();
		int y = vals.back(); vals.pop_back();
		auto f = (c == '|') ? fOr : (c == '&' ? fAnd : fXor);
		vals.push_back(f(x,y));
	}
	assert(sz(vals) == 1);
	return vals.back();
}

struct node{
	char c;
	node *l,*r;
	int x;
	node(){
		x = -1;
		l = r = 0;
		c = 0;
	}
	node (int v) {
		l = r = 0; c = 0;
		x = v;
	}
	node (char z,node *L,node *R) {
		c = z;
		l = L;
		r = R;
		x = -1;
	}
};


node* parse() {
	vector<node*> vals;
	vector<char> op;
	loop(i,n){
		if(E[i] == '(') continue;
		if(E[i] == ')') {
			assert(sz(vals) > 1 && !op.empty());
			char c = op.back(); op.pop_back();
			node *r = vals.back(); vals.pop_back();
			node *l = vals.back(); vals.pop_back();
			vals.push_back(new node(c,l,r));
		}
		else if(E[i] == 'x') vals.push_back(new node(2));
		else if(E[i] == 'X') vals.push_back(new node(3));
		else if(E[i] == '0') vals.push_back(new node(0));
		else if(E[i] == '1') vals.push_back(new node(1));
		else op.push_back(E[i]);
	}
	assert(sz(op) <= 1);
	if(!op.empty()) {
		assert(sz(vals) > 1 && !op.empty());
		char c = op.back(); op.pop_back();
		node *r = vals.back(); vals.pop_back();
		node *l = vals.back(); vals.pop_back();
		vals.push_back(new node(c,l,r));
	}
	assert(sz(vals) == 1);
	return vals.back();
}


map<node*,int> dp[4];

int solve(node *cur,int target) {
	if(dp[target].count(cur)) return dp[target][cur];
	int & ret = dp[target][cur];
	ret = 1 << 29;
	if(cur->x != -1) {
		ret = cur->x != target;
		return ret;
	}
	for(char c : "&^|") {
		loop(l,4) loop(r,4) {
			auto f = (c == '&') ? fAnd : ((c == '|') ? fOr : fXor);
			if(f(l,r) != target) continue;
			int tmp = solve(cur->l,l) + solve(cur->r,r) + (c != cur->c);
			ret = min(ret,tmp);
		}
	}
//	cerr << cur->c << ": " << ret << endl;
	return ret;
}

const int MAXL = 20;
string L[MAXL];
int D;

void dfs(node *root,int d = 0) {
	assert(d >= 0);
	D = max(d,D);
	L[d] += string(MAXL-d,' ');
	if(root->x != -1) {
		L[d] += out[root->x];
		return;
	}
	L[d] += root->c;
	dfs(root->l,d + 1);
	dfs(root->r,d + 1);
}

int main(int argc,char **argv){
#ifdef HOME
//	freopen("in.in","r",stdin);
	freopen("data.txt","r",stdin);
//	freopen("out.out","w",stdout);
#endif
	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++) {
		scanf("%s",E);
		n = strlen(E);
		node *root = parse();
//		D = -1;
//		loop(d,MAXL) L[d] = "";
//		dfs(root);
//		for(int d = 0;d <= D;d++)
//			cout << L[d] << endl;
		loop(i,4) dp[i].clear();
		int ans = min(solve(root,0),solve(root,1));
		printf("Case #%d: %d\n",t,ans);
	}
	return 0;
}
