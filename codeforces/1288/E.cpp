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
 
struct node;
extern node* empty;

struct node{
	node *l,*r,*p;
	int siz, id;
	int sum, mx, lazy;
	
	node(){
		l = r = p = this;
		siz = sum = mx = lazy = 0;
	}

	node(int x){
		siz = 1;
		sum = mx = x;
		lazy = 0;
		l = r = p = empty;
		id = x;
	}

	void add_lazy(int val){
		lazy += val;
		sum += val;
		mx = max(mx, sum);
	}
		
		
	void push_down(){
		if(this == empty) return;
		if(!this->lazy) return;
		this->l->add_lazy(this->lazy);
		this->r->add_lazy(this->lazy);
		this->lazy = 0;
	}
	
	string to_string(){
        if(this == empty) return "{}";
        stringstream ss;
        this->push_down();
        ss << "{" << make_pair(id, make_pair(sum, mx)) << " " << l->to_string() << " " << r->to_string() << "}" ;
        return ss.str();
    }


};
 
node *empty = new node();
 
 
 
void push_down(node *root) {
	root->push_down();
}
 
 
 
void push_up(node *root) {
	root->siz = root->l->siz + root->r->siz + 1;
	root->l->p = root;
	root->r->p = root;
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
	if(L == empty) root = R;
	else if(R == empty) root = L;
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
		R = empty;
	}
	else {
		splay(root,key);
		L = root->l;
		R = root;
		root->l = empty;
		L->p = empty;
		push_up(root);
	}
}

int getKey(node *cur){
	int ret = 0;
	node *prv = 0;
	while(cur != empty){
		if(prv != cur->l)
			ret += cur->l->siz + 1;
		prv = cur;
		cur = cur->p;
	}
	ret--;
	return ret;
}


node *T[1 << 20];
bool vis[1 << 20];
int ans[1 << 20];

void dfs(node *root){
	if(root == empty) return ;
	ans[root->id] = root->mx;
	root->push_down();
	dfs(root->l);
	dfs(root->r);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n, m; scanf("%d %d", &n, &m);
	node *root = empty;
	for(int i = 1;i <= n;i++) {
		T[i] = new node(i);
		merge(root, T[i], root);
	}
	
	//cout << root->to_string() << endl;
	
	node *l,*r;
	node *mid;
	int prv = -1;
	while(m--){
		int x; scanf("%d",&x);
		vis[x] = 1;
		if(prv == x) continue;
		prv = x;
	
		int k = getKey(T[x]);
		//cout << x << ": " << k << endl;
		split(root, l, r, k);
		split(r, mid, r, 1);
		
		assert(mid != empty);
		
		//cout << l->to_string() << " || " << mid->to_string() << " || " << r->to_string() << endl;
		
		l->add_lazy(1);
		mid->lazy = 0;
		mid->sum = 1;
		
		
		
		merge(mid, l, root);
		merge(root, r, root);
	}
	
	
	dfs(root);
	
	for(int i = 1;i <= n;i++){
		int mn = i;
		if(vis[i]) mn = 1;
		printf("%d %d\n",mn, ans[i]);
	}
	
	
	return 0;
}
