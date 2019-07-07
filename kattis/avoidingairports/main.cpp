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
#define PRESTDIO() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
using namespace std;

struct flight{
	int fr,to;
	int b,e;
	friend istream& operator >> (istream & st,flight & f) {
		st >> f.fr >> f.to >> f.b >> f.e;
		return st;
	}
	bool operator < (const flight & o) const {
		return b < o.b;
	}
};
const int MAX = 200*1000 + 10,MAXX = 1000*1000;

typedef pair<ll,ll> line;
struct node {
	node *left,*right;
	line L;
};
auto f = [](const line & L,const ll & x) {
	return -2*L.first*x + L.second;
};
auto sq = [](const ll & x) {
	return x*x;
};

node* insert(node *root,int s,int e,line nL){
	if(!root) {
		root = new node();
		root->L = nL;
		return root;
	}
	if(s == e) {
		if(f(nL,s) < f(root->L,s)) root->L = nL;
		return root;
	}
	int m = (s + e)/2 + 1;
	bool lef = f(nL,s) < f(root->L,s);
	bool mid = f(nL,m) < f(root->L,m);
	if(mid) swap(nL,root->L);
	if(lef != mid) root->left = insert(root->left,s,m-1,nL);
	else root->right = insert(root->right,m,e,nL);
	return root;
}

ll query(node *root,int s,int e,int x) {
	if(!root) return LLONG_MAX;
	if(s == e) return f(root->L,x);
	int m = (s + e) >> 1;
	ll ret = f(root->L,x);
	if(x <= m) ret = min(ret,query(root->left,s,m,x));
	else ret = min(ret,query(root->right,m+1,e,x));
	return ret;
}

flight F[MAX];
ll res[MAX];
int n,m;
node *LIC[MAX];
vi ET[MAXX + 10],IT[MAXX + 10];
//vector<line> aux[MAX];
//
//ll bf(int u,ll x) {
//	ll ret = LLONG_MAX;
//	for(line L : aux[u])
//		ret = min(ret,f(L,x));
//	return ret;
//}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	PRESTDIO();
	cin >> n >> m;
	loop(i,m) {
		cin >> F[i];
		ET[F[i].b].push_back(i);
		IT[F[i].e].push_back(i);
	}
	LIC[1] = insert(0,0,MAXX,line(0,0));
//	aux[1].push_back(line(0,0));
	ll ans = LLONG_MAX;
	for(int t = 0;t <= MAXX;t++) {
		for(int i : ET[t]) {
			const flight & f = F[i];
			ll v = query(LIC[f.fr],0,MAXX,f.b);
//			cerr << v << " vs " << bf(f.fr,f.b) << endl;
//			assert(v == bf(f.fr,f.b));
			if(v <= LLONG_MAX - sq(f.b))
				v += sq(f.b);
			if(f.to == n) ans = min(ans,v);
			res[i] = v;
		}
		for(int i : IT[t]) {
			const flight & f = F[i];
			if(res[i] == LONG_MAX) continue;
			ll c = res[i] + sq(f.e);
			line L(f.e,c);
			LIC[f.to] = insert(LIC[f.to],0,MAXX,L);
//			aux[f.to].push_back(L);
		}
	}
	cout << ans << endl;
	return 0;
}
