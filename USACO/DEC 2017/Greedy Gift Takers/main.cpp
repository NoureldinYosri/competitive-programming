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


struct node {
	node *left, *right;
	int value, freq, priority, size ,carry;
	static node* sentinel;
	node() {
		memset(this, 0, sizeof *this);
	}
	node(int v,int t) {
		value = v; freq = size = 1;
		priority = rand(); left = right = sentinel;
		carry = t;
	}
	void update() {
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

const int MAX = 100*1000;
int n;
int C[MAX];
int cnt[MAX];

int main(){
	freopen("greedy.in", "r", stdin);
	#ifndef HOME
		freopen("greedy.out", "w", stdout);
	#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",C + i);
	node *prv = &node::sentinal,*lst = prv;
	deque<pair<int,node*> > dq;
	loop(i,n) {
		node *root = update(lst,0,n-1,C[i]);
		dq.push_back(mp(i,root));
		lst = root;
	}
	while(1) {
		int c = C[dq.front()];
		int ctr = getCnt(q)
	}
	return 0;
}
