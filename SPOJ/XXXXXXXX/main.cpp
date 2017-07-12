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
#define pl pair<ll,ll>
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

struct node {
	node *left, *right;
	int value, freq, priority, size;
	static node* sentinel;
	node() {
		memset(this, 0, sizeof *this);
	}
	node(int v) {
		value = v; freq = size = 1;
		priority = rand(); left = right = sentinel;
	}
	void update() {
		if(this == sentinel) return;
		size = freq + left->size + right->size;
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
	if (root->left->priority > root->priority)
	root = rotateRight(root);
	else if (root->right->priority > root->priority)
	root = rotateLeft(root);
	return root;
}

node* insert(node* root, int val) {
	if (root == node::sentinel)
		return new node(val);
	if (val == root->value) {
		root->freq++;
		root->size++;
		return root;
	}
	if (val < root->value)
		root->left = insert(root->left, val);
	else
		root->right = insert(root->right, val);
	root->update();
	root = balance(root);
	return root;
}
int lower_bound(node* root, int x) { //number of elements less than x in the tree
	if (root == node::sentinel)
		return 0;
	if (x == root->value)
		return root->left->size;
	return (x < root->value) ? lower_bound(root->left, x) : root->left->size + root->freq + lower_bound(root->right, x);
}
node* remove(node* root, int v) {
	if (root == node::sentinel)
		return root;
	if (v < root->value)
		root->left = remove(root->left, v);
	else if (v > root->value)
		root->right = remove(root->right, v);
	else {
		if (root->freq > 1) {
			root->freq--;
			root->size--;
			return root;
		}
		if (root->left == node::sentinel)
			root = root->right;
		else if (root->right == node::sentinel)
			root = root->left;
		else {
			if (root->left->priority < root->right->priority)
				root = rotateRight(root);
			else
				root = rotateLeft(root);
			root = remove(root, v);
		}
	}
	root->update();
	return root;
}

int upper_bound(node* root, int x) {
	//number of elements less than or equal to x in the tree
	if (root == node::sentinel)
		return 0;
	if (x == root->value)
		return root->left->size + root->freq;
	return (x < root->value) ? upper_bound(root->left, x) : root->left->size + root->freq + upper_bound(root->right, x);
}
int getByIndex(node* root, int idx) {
	if (idx < root->left->size)
		return getByIndex(root->left, idx);
	if (idx >= root->left->size + root->freq)
		return getByIndex(root->right,idx - (root->left->size + root->freq));
	return root->value;
}



const int MAX = 50000 + 10;
int n;
int A[MAX];
int nxt[MAX];
map<int,set<int> > M2S;
node *ST[MAX << 2];

void build(int vertex,int s,int e){
	ST[vertex] = node::sentinel;
	range(i,s,e) ST[vertex] = insert(ST[vertex],nxt[i]);
	if(s == e) return;
	int m = (s + e) >> 1,left = vertex << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
}

void update(int vertex,int s,int e,int p,int v){
	ST[vertex] = remove(ST[vertex],nxt[p]);
	ST[vertex] = insert(ST[vertex],v);
	if(s == e) return;
	int m = (s + e) >> 1,left = vertex << 1,right = left | 1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m+1,e,p,v);
}

int query(int vertex,int s,int e,int p,int v){
	if(e <= p) return e - s + 1 - lower_bound(ST[vertex],v);
	int m = (s + e) >> 1,left = vertex << 1,right = left | 1;
	if(p <= m) return query(left,s,m,p,v);
	return query(left,s,m,p,v) + query(right,m+1,e,p,v);
}

void preprocess(){
	for(int i = n-1;i >= 0;i--){
		int x = A[i];
		if(M2S[x].empty()) nxt[i] = n;
		else nxt[i] = *M2S[x].begin();
		M2S[x].insert(i);
	}
	build(1,0,n-1);
}

int get_prv(set<int> & S,int cur){
	auto p = S.lower_bound(cur);
	if(p == S.begin()) return -1;
	--p;
	return *p;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	preprocess();
	int m; scanf("%d",&m);
	while(m--){
		char type; int x,y;
		scanf(" %c %d %d",&type,&x,&y);
		if(type == 'Q'){
			x--,y--;
			printf("%d\n",query(1,0,n-1,y,y) - (x ? query(1,0,n-1,x-1,y) : 0));
		}
		else{
			x--;
			if(A[x] == y) continue;
			int prv = get_prv(M2S[A[x]],x);
			int nprv = get_prv(M2S[y],x);
			if(prv != -1) {
				nxt[prv] = nxt[x];
				update(1,0,n-1,prv,nxt[x]);
			}
			if(nprv != -1) {
				update(1,0,n-1,x,nxt[nprv]);
				nxt[x] = nxt[nprv];
				update(1,0,n-1,nprv,x);
				nxt[nprv] = x;
			}
			else{
				auto p = M2S[y].upper_bound(x);
				int v = n;
				if(p != M2S[y].end()) v = *p;
				update(1,0,n-1,x,v);
				nxt[x] = v;
			}
		}
	}
	return 0;
}
