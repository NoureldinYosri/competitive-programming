#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
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
const double PI = acos(-1);
using namespace std;


const int MAX = 300*1000 + 10,mod = 1e9 + 7;
struct matrix{
	int A[2][2];
	matrix(){
		A[0][0] = A[1][1] = 1;
		A[0][1] = A[1][0] = 0;
	}
	void move(){
		static int a,b,c,d;
		a = A[0][0] + A[1][0];
		b = A[0][1] + A[1][1];
		c = A[0][0],d = A[0][1];
		A[0][0] = a,A[0][1] = b;
		A[1][0] = c,A[1][1] = d;
		loop(j,2) if(A[0][j] >= mod) A[0][j] -= mod;
	}
	void back(){
		static int M[2][2] = {{0,1},{1,mod-1}},C[2][2];
		loop(i,2) loop(j,2) {
			C[i][j] = 0;
			loop(k,2) {
				C[i][j] += (M[i][k]*1LL*A[k][j])%mod;
				if(C[i][j] >= mod) C[i][j] -= mod;
			}
		}
		loop(i,2) loop(j,2) A[i][j] = C[i][j];
	}
	friend ostream& operator << (ostream & st,const matrix & A) {
		st << endl;
		st << "[" << A.A[0][0] << ", " << A.A[0][1] << endl;
		st << " " << A.A[1][0] << ", " << A.A[1][1] << "]" << endl;
		return st;
	}
	void jump(int & a,int & b) {
		static int c,d;
		d = (A[0][0]*1LL*b)%mod + (A[0][1]*1LL*a)%mod;
		c = (A[1][0]*1LL*b)%mod + (A[1][1]*1LL*a)%mod;
		if(c >= mod) c -= mod;
		if(d >= mod) d -= mod;
		a = c,b = d;
	}
};

inline int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}

struct node {
	node *left, *right,*root;
	int value, freq, priority, size,a,b,sa,sb;
	static node* sentinel;
	node() {
		memset(this, 0, sizeof *this);
		value = INT_MIN;
		root = sentinel;
	}
	node(int v,int _a,int _b) {
		value = v; freq = size = 1;
		priority = rand(); left = right = sentinel;
		sa = a = _a;
		sb = b = _b;
		root = sentinel;
	}
	void update() {
		if(!left) left = sentinel;
		if(!right) right = sentinel;
		size = freq + left->size + right->size;
		sa = add(a,add(left->sa,right->sa));
		sb = add(b,add(left->sb,right->sb));
	}
};

node* node::sentinel = new node();

node* rotateRight(node* Q) {
	node* P = Q->left;
	Q->left = P->right;
	P->right = Q;
	Q->update();
	P->update();
	return P;
}

node* rotateLeft(node* P) {
	node* Q = P->right;
	P->right = Q->left;
	Q->left = P;
	P->update();
	Q->update();
	return Q;
}

node* balance(node* root) {
	if(root == node::sentinel) return root;
	if (root->left->priority > root->priority)
		root = rotateRight(root);
	else if (root->right->priority > root->priority)
		root = rotateLeft(root);
	return root;
}

node* insert(node* root, int val,int a,int b) {
	if (root == node::sentinel)
		return new node(val,a,b);
	if (val == root->value) {
		root->freq++;
		root->size++;
		root->a = add(root->a,a);
		root->b = add(root->b,b);
		root->sa = add(root->sa,a);
		root->sb = add(root->sb,b);
		return root;
	}
	if (val < root->value)
		root->left = insert(root->left, val,a,b);
	else
		root->right = insert(root->right, val,a,b);
	root->update();
	root = balance(root);
	assert(node::sentinel->sa == 0 && node::sentinel->sb == 0);
	return root;
}

vi G[MAX];
int siz[MAX],pref_child[MAX],parent[MAX],n,m,val[MAX];
int depth[MAX],dfs_in[MAX],dfs_out[MAX],dfs_time;
int hID[MAX],head[MAX],euler[MAX],hsiz[MAX],hcnt;
node *hT[MAX][2]; // every chain has 2
node  *T[MAX][2]; // every node has 2
matrix fib[2*MAX],rfib[2*MAX];

void erase(node *root) {
	if(!root || root == node::sentinel) return;
	erase(root->left);
	erase(root->right);
	erase(root->root);
	delete root;
}

void clean(){
	range(i,1,n) {
		G[i].clear();
		val[i] = 0;
	}

	loop(i,hcnt+1) hsiz[i] = 0;
	loop(i,hcnt+1) loop(j,2) {
		erase(hT[i][j]);
		hT[i][j] = 0;
	}
	range(i,1,n) loop(j,2) {
		erase(T[i][j]);
		T[i][j] = 0;
	}
	dfs_time = hcnt = 0;
}
void init(){
	for(int i = 1;i < 2*MAX;i++){
		fib[i] = fib[i - 1];
		fib[i].move();
		rfib[i] = rfib[i - 1];
		rfib[i].back();
	}

}


void dfs(int u,int p) {
	parent[u] = p;
	siz[u] = 1;
	pref_child[u] = 0;
	depth[u] = depth[p] + 1;

	for(int v : G[u]) if(v != p) {
		dfs(v,u);
		if(siz[v] > siz[pref_child[u]])
			pref_child[u] = v;
		siz[u] += siz[v];
	}
}

void hld(int u,int p){
	dfs_in[u] = dfs_time++;
	hID[u] = hcnt;
	if(hsiz[hcnt] == 0) head[hcnt] = u;
	hsiz[hcnt]++;

	if(pref_child[u]) hld(pref_child[u],u);

	for(int v : G[u]) if(v != p && v != pref_child[u]) {
		hcnt++;
		hld(v,u);
	}
	dfs_out[u] = dfs_time;
}

pi operator + (const pi & a,const pi & b){
	return mp(add(a.xx,b.xx),add(a.yy,b.yy));
}
pi operator - (const pi & a,const pi & b) {
	return mp(add(a.xx,-b.xx),add(a.yy,-b.yy));
}
ostream& operator << (ostream& st,const pi & a) {
	st << "(" << a.xx << "  ," << a.yy << ")";
	return st;
}

node* update(node *root,int s,int e,int pos,int a,int b) {
	if(!root) root = new node();
	root->a = add(root->a,a);
	root->b = add(root->b,b);
	if(s == e) return root;
	int m = s + (e-s)/2;
	if(pos <= m) root->left = update(root->left,s,m,pos,a,b);
	else root->right = update(root->right,m+1,e,pos,a,b);
	return root;
}

void inorder(node*);

node* update(node *root,int s,int e,int x,int y,int a,int b,int L,int R) {
	if(!root) root = new node();
//	cerr << "###############################" << endl;
//	cerr << "insert " << y << " " << a << " " << b << " into " << endl;
//	cerr << "{" << endl;
//	inorder(root->root);
//	cerr << "}" << endl;
	root->root = insert(root->root,y,a,b);
//	cerr << "got" << endl;
//	cerr << "{" << endl;
//	inorder(root->root);
//	cerr << "}" << endl;
//	cerr << "##############################" << endl;
//	root->root = update(root->root,L,R,y,a,b);
	if(s == e) return root;
	int m = s + (e-s)/2;
	if(x <= m) root->left = update(root->left,s,m,x,y,a,b,L,R);
	else root->right = update(root->right,m+1,e,x,y,a,b,L,R);
	return root;
}

void update(int u,int v,int a,int b,int k) {
	int hid = hID[u],h = head[hid];
	int pos = dfs_in[u] - dfs_in[h];
	int ta,tb,L = 0,R = 2*n;
//	cerr << "hid: " << hid << " ,pos: " << pos << endl;
//	cerr << "a: " << a << " b: " << b << endl;

	// right ray
	ta = a,tb = b;
	rfib[pos].jump(ta,tb);
	hT[hid][0] = update(hT[hid][0],L,R,pos,pos+k,ta,tb,L,R);
	if(v != -1) T[v][0] = update(T[v][0],L,R,pos,pos+k,ta,tb,L,R);
//	cerr << "for right ray: " << endl;
//	cerr << "hid: " << hid << " ,pos: " << pos << endl;
//	cerr << "ta: " << ta << " tb: " << tb << endl;

	// left ray
	ta = a,tb = b;
	pos += n;
	fib[pos].jump(ta,tb);
	hT[hid][1] = update(hT[hid][1],L,R,pos,pos-k,ta,tb,L,R);
	if(v != -1) T[v][1] = update(T[v][1],L,R,pos,pos-k,ta,tb,L,R);
//	cerr << "for left ray: " << endl;
//	cerr << "hid: " << hid << " ,pos: " << pos << endl;
//	cerr << "ta: " << ta << " tb: " << tb << endl;
}

void update(int u,int k,int a,int b){
	int v = -1;
	while(u && k >= 0) {
		int hid = hID[u],h = head[hid],dist = dfs_in[u] - dfs_in[h] + 1;
		update(u,v,a,b,k);
		fib[dist].jump(a,b);
		v = h;
		u = parent[h];
		k -= dist;
	}
}



pi query(node *root,int s,int e,int l,int r) {
	if(!root) return mp(0,0);
	if(l <= s && e <= r) return mp(root->a,root->b);
	int m = s + (e - s)/2;
	if(r <= m) return query(root->left,s,m,l,r);
	if(m < l) return query(root->right,m+1,e,l,r);
	return query(root->left,s,m,l,m) + query(root->right,m+1,e,m+1,r);
}

pi lower_bound(node *root,int target) {
	pi ret = mp(0,0);
	while(root && root != node::sentinel){
		if(root->value <= target) {
			ret.xx = add(ret.xx,root->a);
			ret.yy = add(ret.yy,root->b);
			ret.xx = add(ret.xx,root->left->sa);
			ret.yy = add(ret.yy,root->left->sb);
			root = root->right;
		}
		else root = root->left;
	}
	return ret;
}

ostream & operator << (ostream &st,const node & root) {
	st << "(" << root.value << " " << root.freq << " " << root.a << " " << root.b << " " << root.sa << " " << root.sb << ")";
	return st;
}

void inorder(node *root){
	if(root==node::sentinel || !root) return;
	inorder(root->left);
	cerr << *root << endl;
	inorder(root->right);
}

pi query(node *root,int s,int e,int l,int r,int L,int R,int l2,int r2) {
	if(root == 0) return mp(0,0);
	if(l <= s && e <= r){
//		cerr << "====================" << endl;
//		inorder(root->root);
		pi ret = lower_bound(root->root,r2) - lower_bound(root->root,l2-1);
//		cerr << "in range " << l2 << " " << r2 << " got " << ret << endl;
//		cerr << "====================" << endl;
		return ret;
		//		return query(root->root,L,R,l2,r2);
	}
	int m = s + (e - s)/2;
	if(r <= m) return query(root->left,s,m,l,r,L,R,l2,r2);
	if(m < l) return query(root->right,m+1,e,l,r,L,R,l2,r2);
	return query(root->left,s,m,l,m,L,R,l2,r2) + query(root->right,m+1,e,m+1,r,L,R,l2,r2);
}

inline int query(int u,int v,int k){
	int hid = hID[u],h = head[hid],pos = dfs_in[u] - dfs_in[h];
	int L = 0,R = 2*n;

	// look left
	pi A = mp(0,0); //query(hT[hid][0],L,R,0,pos,L,R,pos+k,R);
	pi B = mp(0,0);
	if(v != -1) B = query(T[v][0],L,R,0,pos,L,R,pos+k,R);
//	cerr << "pos: " << pos << "\t" << A << " " << B << " ";
	fib[pos+k].jump(A.xx,A.yy);
	fib[pos+k].jump(B.xx,B.yy);

	// look right
	pos += n;
	pi C = query(hT[hid][1],L,R,pos+1,R,L,R,L,pos-k);
	pi D = mp(0,0);
	if(v != -1) query(T[v][1],L,R,pos+1,R,L,R,L,pos-k);
//	cerr << C << " " << D << endl;
	rfib[pos-k].jump(C.xx,C.yy);
	rfib[pos-k].jump(D.xx,D.yy);

//	cerr << A << " " << B << " " << C << " " << D << endl;

	int ret = add(A.xx,C.xx);
	ret = add(ret,-add(B.xx,D.xx));
	return ret;
}

int query(int u) {
	int k = 0,v = -1,ret = 0;
	while(u){
		int hid = hID[u],h = head[hid],dist = dfs_in[u] - dfs_in[h] + 1;
		ret = add(ret,query(u,v,k));
		v = h;
		u = parent[h];
		k += dist;
	}
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
//		freopen("out.out","w",stdout);
	#endif

	init();
	int T; scanf("%d",&T);
	range(t,1,T){
		scanf("%d %d",&n,&m);
		loop(e,n-1) {
			int a,b; scanf("%d %d",&a,&b);
			G[a].pb(b);
			G[b].pb(a);
		}
		dfs(1,0);
		hld(1,0);
		loop(i,m){
			int type; scanf("%d",&type);
			if(type == 1) {
				int u,k,a,b; scanf("%d %d %d %d",&u,&k,&a,&b);
				update(u,k,a,b);
			}
			else {
				int u; scanf("%d",&u);
				printf("%d\n",query(u));
			}
		}
		clean();
	}
	return 0;
}
