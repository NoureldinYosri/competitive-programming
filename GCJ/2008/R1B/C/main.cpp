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
	int val,siz;
	node *left,*right,*parent;
	static node *sentinal;
	node(){
		val=siz=0;
		left=right=parent = sentinal;
	}
	node(int x) {
		val = x;
		siz = 1;
		left=right=parent=sentinal;
	}
	bool isLeftChild(){
		return parent->left == this;
	}
	void pushup(){
		if(this == sentinal) return;
		siz = 1 + left->siz + right->siz;
	}
	void setLeftChild(node *u) {
		left = u;
		u->parent = this;
		pushup();
	}
	void setRightChild(node *u) {
		right = u;
		u->parent = this;
		pushup();
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
		pnode p = u->parent,R = u->right,pp = p->parent;

		if(p->isLeftChild()) pp->setLeftChild(u);
		else pp->setRightChild(u);
//		u->parent = pp;
//		if(p->isLeftChild()) pp->left = u;
//		else pp->right = v;

		p->setLeftChild(R);
//		p->left = R;
//		R->parent = p;


		u->setRightChild(p);;
//		u->right = p;
//		p->parent = u;
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

		if(p->isLeftChild()) pp->setLeftChild(u);
		else pp->setRightChild(u);
//		u->parent = pp;
//		if(p->isLeftChild()) pp->left = u;
//		else pp->right = u;

		u->setLeftChild(p);
//		u->left = p;
//		p->parent = u;

		p->setRightChild(L);
//		p->right = L;
//		L->parent = p;
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

	pnode access(pnode cur) {
		splay(cur);
		return root = cur;
	}
	bool isEmpty(){
		return root == node::sentinal;
	}

	pnode getRightMost(){
		pnode cur = root;
		while(cur->right != node::sentinal)
			cur = cur->right;
		return cur;
	}

	pnode get(int x) {
		pnode cur = root;
		while(cur != node::sentinal) {
			int cidx = cur->left->siz + 1;
			if(cidx == x) return cur;
			if(cidx < x) {
				x -= cidx;
				cur = cur->right;
			}
			else cur = cur->left;
		}
		assert(cur != node::sentinal);
		return cur;
	}
	void insert(int ts,pnode u){
		if(root == node::sentinal) {
			root = u;
			return;
		}

		pnode cur = root;
		pnode prv = node::sentinal;
		while(cur != node::sentinal) {
			int cidx = cur->left->siz + 1;
			if(ts == cidx) {
				if(prv == node::sentinal) root = u;
				else {
					if(cur->isLeftChild()) prv->setLeftChild(u);
					else prv->setRightChild(u);
				}
				u->setRightChild(cur);
				access(u);
				return;
			}
			if(cidx < ts) {
				ts -= cidx;
				prv = cur;
				cur = cur->right;
			}
			else {
				prv = cur;
				cur = cur->left;
			}
		}
		prv->setRightChild(u);
		access(u);
	}
private:
	void preOrder(pnode u){
		if(u == node::sentinal) return;
		cout << " " << u->val;

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
//	L.access(L.getMax());
	L.access(L.getRightMost());
	assert(L.root->right == node::sentinal);
	L.root->right = R.root;
	R.root->parent = L.root;
	return L;
}



int seq[1 << 20];

void build(int n) {
	splayTree T;
	for(int i = 1;i <= n;i++)
		T.insert(i,new node(i));

	for(int i = 1;i <= n;i++) {
		int len = n - i + 1;
		int ts = (i-1)%len + 1;
		pnode u = T.get(ts);
		T.access(u);
		seq[u->val] = i;

		pnode L = u->left;
		pnode R = u->right;

		L->parent = R->parent = node::sentinal;

		if(R == node::sentinal) {
			T.root = L;
		}
		else {
			T.root = R;
			T.access(T.getRightMost());
			T.root->setRightChild(L);
		}
//		T.preOrder();
		delete u;
	}

//	prArr(seq+1,n,int);
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++) {
		int n; scanf("%d",&n);
		cerr << "t = " << t << " n = " << n << endl;
		build(n);
		cerr << "done building" << endl;
		int m; scanf("%d",&m);
		printf("Case #%d:",t);
		for(int i = 0;i < m;i++) {
			int j; scanf("%d",&j);
			printf(" %d",seq[j]);
		}
		puts("");
	}

	return 0;
}
