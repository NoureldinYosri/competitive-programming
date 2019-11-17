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


const int MAXM = 5e5 * 10;
struct node{
	int val;
	node *l,*r;
	node(){val = INT_MAX; l = r = 0;}
};
node MEM[MAXM];
int mem;
node *ST[500*1000];

node* insert(node *root,int s,int e,int l,int r,int v){
	assert(mem < MAXM);
	node *cur = &MEM[mem++];
	if(root) *cur = *root;
	if(cur->val <= v) return cur;
	if(l <= s && e <= r) {
		cur->val = min(cur->val,v);
		return cur;
	}
	int m = s + (e-s)/2;
	if(r <= m) cur->l = insert(cur->l,s,m,l,r,v);
	else if(m < l) cur->r = insert(cur->r,m+1,e,l,r,v);
	else {
		cur->l = insert(cur->l,s,m,l,m,v);
		cur->r = insert(cur->r,m+1,e,m+1,r,v);
	}
	return cur;
}

int query(node *root,int s,int e,int p) {
	if(!root) return INT_MAX;
	if(s == e) return root->val;
	int m = s + (e-s)/2;
	int res = root->val;
	if(p <= m) res = min(res,query(root->l,s,m,p));
	else res = min(res,query(root->r,m+1,e,p));
	return res;
}

int main(){
	freopen("invazia.in","r",stdin);
	freopen("invazia.out","w",stdout);
	int n,m; scanf("%d %d",&n,&m);
	int sz = 0;
	while(m--) {
		char c; scanf(" %c",&c);
		if(c == 'I') {
			int x,y,z;
			scanf("%d %d %d",&x,&y,&z);
			assert(x <= y);
			node *prv = 0;
			if(sz) prv = ST[sz-1];
			ST[sz++] = insert(prv,1,n,x,y,z);
		}
		else if(c == 'R') {
			int x; scanf("%d",&x);
			int ans = INT_MAX;
			if(sz) ans = query(ST[sz-1],1,n,x);
			if(ans == INT_MAX) puts("GUITZZZ!");
			else printf("%d\n",ans);
		}
		else {
			assert(sz);
			sz--;
		}
	}
	return 0;
}
#endif
