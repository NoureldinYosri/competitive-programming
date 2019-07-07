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
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
using namespace std;


struct node{
	int key,freq;
	node *left,*right,*parent;
	static node *sentinal;
	node(){
		key=freq=0;
		left=right=parent = sentinal;
	}
	node(int x) {
		key = x;
		freq = 1;
		left=right=parent=sentinal;
	}
	bool isLeftChild(){
		return parent->left == this;
	}
};
typedef node* pnode;
pnode node::sentinal = new node();

struct splayTree{
	pnode root;

	splayTree(){root = node::sentinal;}
	splayTree(pnode u){root = u;}

	pnode RightRotate(pnode u) {
		/*         p
		 *       u  v
		 *     L  R
		 *
		 *       u
		 *      L p
		 *       R v
		 */
		pnode p = u->parent,v = p->right,R = u->right,pp = p->parent;
		u->parent = pp;
		if(p->isLeftChild()) pp->left = u;
		else pp->right = v;

		p->left = R;
		R->parent = p;

		u->right = p;
		p->parent = u;
		return u;
	}
	pnode LeftRotate(pnode u) {
		/*
		 *         p
		 *       v   u
		 *          L R
		 *
		 *        u
		 *       p  R
		 *     v  L
		 */
		pnode p = u->parent,pp = p->parent,L = u->left;
		u->parent = pp;
		if(p->isLeftChild()) pp->left = u;
		else pp->right = u;

		u->left = p;
		p->parent = u;

		p->right = L;
		L->parent = p;
		return u;
	}

	void splay(pnode u) {
		while(u->parent != node::sentinal){
			bool isLeftChild = u->parent->left == u;
			if(u->parent->parent == node::sentinal) {
				if(isLeftChild) u = RightRotate(u);
				else u = LeftRotate(u);
			}
			else {
				pnode p = u->parent;
				if(u->isLeftChild()) {
					if(p->isLeftChild()) {
						RightRotate(p);
						RightRotate(u);
					}
					else {
						RightRotate(u);
						LeftRotate(u);
					}
				}
				else {
					if(p->isLeftChild()) {
						LeftRotate(u);
						RightRotate(u);
					}
					else {
						LeftRotate(p);
						LeftRotate(u);
					}
				}
			}
		}
	}
	void insert(int x){
		if(root == node::sentinal) {
			root = new node(x);
			return;
		}
		pnode prv = node::sentinal,cur = root;
		while(cur != node::sentinal && cur->key != x) {
			prv = cur;
			if(x < cur->key) cur = cur->left;
			else cur = cur->right;
		}
		pnode u = cur;
		if(u == node::sentinal) {
			u = new node(x);
			u->parent = prv;
			if(x < prv->key) prv->left = u;
			else prv->right = u;
		}
		else {
			u->freq++;
		}
		splay(u);
		root = u;
	}
	pnode LowerBound(int x) {
		pnode cur = root,lowerbound = node::sentinal;
		while(cur != node::sentinal) {
			if(cur->key == x) return cur;
			if(cur->key > x) lowerbound = cur;
			if(cur->key < x) cur = cur->right;
			else cur = cur->left;
		}
		return lowerbound;
	}
	int getMax(){
		pnode cur = root;
		while(cur->right != node::sentinal) cur = cur->right;
		return cur->key;
	}
	pnode access(int x) {
		pnode cur = LowerBound(x);
		if(cur == node::sentinal)
			throw new logic_error(to_string(x) + " is bigger than all in tree");
		splay(cur);
		return root = cur;
	}
	bool isEmpty(){
		return root == node::sentinal;
	}

private:
	void preOrder(pnode u){
		if(u == node::sentinal) return;
		cout << " " << u->key;

		cout << "{";
		preOrder(u->left);
		cout << "} {";
		preOrder(u->right);
		cout << "}";
	}
public:
	void preOrder(){
		preOrder(root);
		cout << endl;
	}
};

splayTree merge(splayTree & L,splayTree & R) {
	if(L.isEmpty()) return R;
	L.access(L.getMax());
	assert(L.root->right == node::sentinal);
	L.root->right = R.root;
	R.root->parent = L.root;
	return L;
}

void split(splayTree & T,int x,splayTree & L,splayTree & R) {
	// L has all nodes with key < x
	// R has all nodes with key >= x
	T.access(x);
	pnode root = T.root;
	L = splayTree(root->left);
	root->left->parent = node::sentinal;
	root->left = node::sentinal;
	R = splayTree(root);
}
int main(int argc,char **argv){

	return 0;
}
