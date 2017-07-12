#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 200000 + 10;


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



node *ST[MAX << 2];
int n,m;
int A[MAX];



void build(int ver,int s,int e){
	ST[ver] = node::sentinel;
	for(int x = s;x <= e;x++) ST[ver] = insert(ST[ver],x);
	if(s == e) return;
	int m = (s + e) >> 1,left = ver << 1,right = left | 1;
	build(left,s,m);
	build(right,m + 1,e);
}

int query(int ver,int s,int e,int p,int v){
	if(e <= p) return upper_bound(ST[ver],v);
	int m = (s + e) >> 1,left = ver << 1,right = left | 1;
	if(p <= m) return query(left,s,m,p,v);
	else return query(left,s,m,p,v) + query(right,m+1,e,p,v);
}

void update(int ver,int s,int e,int p,int v1,int v2){
	ST[ver] = insert(ST[ver],v2);
	ST[ver] = remove(ST[ver],v1);
	if(s == e) return;
	int m = (s + e) >> 1,left = ver << 1,right = left | 1;
	if(p <= m) update(left,s,m,p,v1,v2);
	else update(right,m+1,e,p,v1,v2);
}

int get_inv(int pos){
	int le = query(1,1,n,pos,A[pos]) ;
	return  pos - le + A[pos] - le;
}

int main(){
	scanf("%d %d",&n,&m);		
	build(1,1,n);
	range(i,1,n) A[i] = i;
	ll inv = 0;
	while(m--){
		int x,y; scanf("%d %d",&x,&y);
		if(x != y){
			if(x > y) swap(x,y);
			inv -= get_inv(x) + get_inv(y) - (A[x] > A[y]);
			update(1,1,n,x,A[x],A[y]);
			update(1,1,n,y,A[y],A[x]);
			swap(A[x],A[y]);
			inv += get_inv(x) + get_inv(y) - (A[x] > A[y]);
		}
		printf("%lld\n",inv); 
	}
	return 0;
}
