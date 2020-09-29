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


struct node{
	node *l, *r;
	ll sum = 0;
};

int A[1 << 20];
int n;
bool lazy[20], swapChildren[20];

node *build(int s, int k){
	node *ret = new node();
	if(k == 0){
		ret->sum = A[s];
		return ret;
	}
	ret->l = build(s, k-1);
	ret->r = build(s + (1 << (k-1)), k-1);
	ret->sum = ret->l->sum + ret->r->sum;
	return ret;
}

node* update(node *root, int s, int k, int pos, int val, bool fromParent){
	if(k == 0){
		root->sum = val;
		return root;
	}
	node *leftchild = root->l, *rightchild = root->r;
	bool hasLazy = lazy[k] ^ fromParent;
	if(fromParent^swapChildren[k]) swap(leftchild, rightchild);
	int m = s + (1 << (k-1)) - 1;
	
	if(pos <= m) leftchild = update(leftchild, s, k-1, pos, val, hasLazy);
	else rightchild = update(rightchild, m + 1, k-1, pos, val, hasLazy);
	
	root->sum = root->l->sum + root->r->sum;	
	return root;
}

ll query(node *root, int s, int k, int l, int r, bool fromParent){
	if(l <= s && (s + (1 << k) - 1) <= r) return root->sum;
	node *leftchild = root->l, *rightchild = root->r;
	bool hasLazy = lazy[k] ^ fromParent;
	if(fromParent^swapChildren[k]) swap(leftchild, rightchild);
	int m = s + (1 << (k-1)) - 1;
	if(r <= m) return query(leftchild, s, k-1, l, r, hasLazy);
	if(m < l) return query(rightchild, m+1, k-1, l, r, hasLazy);
	return query(leftchild, s, k-1, l, m, hasLazy) + 
			query(rightchild, m+1, k-1, m+1, r, hasLazy);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int m; scanf("%d %d", &n, &m);
	for(int i = 1; i <= (1 << n); i++) scanf("%d", A + i);
	node *root = build(1, n);
	while(m--){
		int t; scanf("%d", &t);
		if(t == 1){
			int pos, val; scanf("%d %d", &pos, &val);
			root = update(root, 1, n, pos, val, false);
		} else if (t == 2){
			//reverse
			int k; scanf("%d", &k);
			lazy[k] ^= 1;
			swapChildren[k] ^= 1;
		} else if (t == 3) {
			//swap
			int k; scanf("%d", &k);
			swapChildren[k+1] ^= 1;
		} else {
			int l, r; scanf("%d %d", &l, &r);
			printf("%lld\n", query(root, 1, n, l, r, false));
		}
	}
	return 0;
}
