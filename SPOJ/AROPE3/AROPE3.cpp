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

const ll INF = 1LL << 60,NINF = -INF;
 
struct node{
	node *l,*r,*p;
	int v,siz;
	bool is_rev;
	ll pref,suff,mx,sum;
	static node *empty;
	node():l(this),r(this),p(this),v(0),siz(0),is_rev(0),pref(NINF),suff(NINF),mx(NINF),sum(0){}
	node(int v):l(empty),r(empty),p(empty),v(v),siz(1),is_rev(0),pref(v),suff(v),mx(v),sum(v){}
};
 
node *node::empty = new node();
int depth = 20;
 
 
void flip(node *root){
	root->is_rev ^= 1;
	swap(root->l,root->r);
}
 
void push_down(node *root) {
	if(root->is_rev) {
		flip(root->l);
		flip(root->r);
		root->is_rev = 0;
	}
}

void PRINT(node *root) {
	if(root == node::empty) return;
//	push_down(root);
	cerr << string (depth,'\t');
	cerr << (char)root->v << "," << root->is_rev << endl;
	depth--;
	PRINT(root->l);
	depth += 2;
	PRINT(root->r);
	depth--;
}
 
void merge_vals(node *L,node *R,node *res) {
	
}
 
 
void push_up(node *root) {
	root->siz = root->l->siz + root->r->siz + 1;
	root->l->p = root;
	root->r->p = root;
 
	node dummy (root->v);
	root->sum = root->pref = root->suff = root->mx = root->v;
	merge_vals(root->l,root,&dummy);
	merge_vals(&dummy,root->r,root);
}
/*
   p
  / \
  a  q
    / \
   b   c
*/
/*
 *      q
 *     / \
 *    p   c
 *   / \
 *  a   b
 */
void rotate_left(node *& p) {
	node *q = p->r,*pp = p->p;
 
	p->r = q->l;
	q->l = p;
 
	q->p = pp;
 
	push_up(p);
	push_up(q);
	p = q;
}
void rotate_right(node *& q) {
	node *p = q->l,*pp = q->p;
 
	q->l = p->r;
	p->r = q;
 
	p->p = pp;
 
	push_up(q);
	push_up(p);
	q = p;
}
 
void splay(node *& root,int key) {
	push_down(root);
	int v = root->l->siz;
	if(key == v) return ;
	if(key < v) {
		push_down(root->l);
		int vv = root->l->l->siz;
		if(vv == key) rotate_right(root);
		else {
			if(key < vv){
				splay(root->l->l,key);
				rotate_right(root);
				rotate_right(root);
			}
			else {
				splay(root->l->r,key - vv - 1);
				rotate_left(root->l);
				rotate_right(root);
			}
		}
	}
	else{
		push_down(root->r);
		int vv = root->r->l->siz;
		key -= v + 1;
		if(vv == key) rotate_left(root);
		else {
			if(key < vv) {
				splay(root->r->l,key);
				rotate_right(root->r);
				rotate_left(root);
			}
			else {
				splay(root->r->r,key - vv - 1);
				rotate_left(root);
				rotate_left(root);
			}
		}
	}
}
 
 
void merge(node *L,node *R,node *& root) {
	if(L == node::empty) root = R;
	else if(R == node::empty) root = L;
	else {
		splay(R,0);
		R->l = L;
		root = R;
		push_up(root);
	}
}
 
void split(node *root,node *& L,node *& R,int key) {
	if(key >= root->siz) {
		splay(root,root->siz-1);
		L = root;
		R = node::empty;
	}
	else {
		splay(root,key);
		L = root->l;
		R = root;
		root->l = node::empty;
		L->p = node::empty;
		push_up(root);
	}
}


const int MAXN = 100000 + 10;
char txt[MAXN];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%s", txt);
	int n = strlen(txt);
	node *root = node::empty;
	for(int i = 0;i < n;i++) merge(root, new node(txt[i]), root);
	int m; scanf("%d",&m);
	//PRINT(root);

	node *L,*mid,*R;
	for(int q = 0;q < m;q++){
		int t; scanf("%d",&t);
		
		if(t == 3) {
			int x; scanf("%d",&x);
			splay(root,x);
			printf("%c\n",(char)root->v);
		}
		else {
			int s, e; scanf("%d %d",&s,&e);
			split(root,mid,R,e+1);
			split(mid,L,mid,s);
			flip(mid);
			if(t == 1){
				merge(mid,L,root);
				merge(root,R,root);
			}
			else {
				merge(L,R,root);
				merge(root,mid,root);
			}
		}
//		PRINT(root);
	}

	return 0;
}
