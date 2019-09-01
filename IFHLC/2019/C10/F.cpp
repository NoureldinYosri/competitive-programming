#ifdef ACTIVE
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

using line = pair<ll,ll>;
const int MAX = 1 << 20;

int A[MAX],B[MAX],n;
ll dp[MAX];

struct node{
	node *l,*r;
	line L;
	node() {
		l = r = 0;
		L = line(0,1LL << 60);
	}
};
auto f = [](const line & L,ll x) {
	return L.first*x + L.second;
};

node* insert(node *root,int s,int e,line L) {
	if(!root) root = new node();
	if(s == e) {
		if(f(L,s) < f(root->L,s)) swap(root->L,L);
		return root;
	}
    int m = (s + e) / 2;
    bool lef = f(L, s) < f(root->L, s);
    bool mid = f(L, m+1) < f(root->L, m+1);
    if(mid) swap(root->L,L);
    if(lef != mid) root->l = insert(root->l,s,m,L);
    else root->r = insert(root->r,m+1,e,L);
	return root;
}

ll query(node *root,int s,int e,int x) {
	if(!root) return 1LL << 60;
    int m = (s + e) / 2;
    ll ret = f(root->L,x);
    if(x <= m) ret = min(ret,query(root->l,s,m,x));
    else ret = min(ret,query(root->r,m+1,e,x));
    return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	loop(i,n) scanf("%d",B + i);
	dp[n-1] = 0;
	node *root = 0;
	int s = 1,e = 1000*1000;
	root = insert(root,s,e,line(A[n-1],0));
	for(int i = n-2;i >= 0;i--) {
		dp[i] = query(root,s,e,B[i]);
		root = insert(root,s,e,line(A[i],dp[i]));
	}
	cout << dp[0] << endl;
	return 0;
}
#endif
