#include <bits/stdc++.h>
using namespace std;


struct node{
	long long value;
	int freq,prior,sz;
	node *left,*right;
	static node *empty;
public:
	node():left(empty),right(empty),prior(INT_MIN),sz(0),freq(0),value(INT_MIN){}
	node(long long value,int prior = rand() % INT_MAX):left(empty),right(empty),prior(prior),sz(1),freq(1),value(value){}
	bool operator < (const node & o){
		return value < o.value;
	}
};

node* node::empty = new node();
	

node* left_rotate(node *root){
	node *new_root = root->right;
	node *f = new_root->left;
	new_root->left = root;
	root->right = f;	
	new_root->sz = root->sz;
	root->sz = root->left->sz + root->right->sz + root->freq;
	return new_root;	
}

node* right_rotate(node *root){
	node *new_root = root->left;
	node *e = new_root->right;
	new_root->right = root;
	root->left = e;
	new_root->sz = root->sz;
	root->sz = root->left->sz + root->right->sz + root->freq;
	return new_root;
}

node* insert(node *root,long long v,int prior = rand() % 1000000){
	if(root == node::empty) return new node(v,prior);	
	if(root->value == v){
		root->freq++;
		root->sz++;
		return root;
	}
	if(root->value < v) {
		node *tmp = insert(root->right,v,prior);
		root->right = tmp;
		if(tmp->prior > root->prior)
			root = left_rotate(root);
	}
	else {	
		node *tmp = insert(root->left,v,prior);
		root->left = tmp;
		if(tmp->prior > root->prior)
			root = right_rotate(root);
	}
	root->sz = root->left->sz + root->right->sz + root->freq;
	return root;
}

int lower_bound(node *root,long long v){
	int ans = 0;
	while(root != node::empty) {
		if(root->value > v) root = root->left;
		else {ans += root->left->sz + root->freq; root = root->right;}  
	}
	return ans;
}

int upper_bound(node *root,long long v){
	int ans = 0;
	while(root != node::empty) {
		if(root->value > v) root = root->left;
		else if(root->value == v) {ans += root->left->sz; break;}
		else {ans += root->left->sz + root->freq; root = root->right;}  
	}
	return ans;
}

void preorder(node *root){
	if(root == node::empty) return;
	cout << root->value << " " << root->freq << " " << root->sz << endl;
	preorder(root->left);	
	preorder(root->right);
}

void inorder(node *root){
	if(root == node::empty) return;
	cout << root->value << " " << root->freq << " " << root->sz << endl;
	inorder(root->left);
	cout << root->value << " " << root->freq << " " << root->sz << endl;
	inorder(root->right);
	cout << root->value << " " << root->freq << " " << root->sz << endl;
}

void postorder(node *root){
	if(root == node::empty) return;
	postorder(root->left);
	postorder(root->right);
	cout << root->value << " " << root->freq << " " << root->sz << endl;
}

void sorted_order(node *root){
	if(root == node::empty) return;
	sorted_order(root->left);
	cout << root->value << endl;
	sorted_order(root->right);
}

void remove_all(node *root){
	if(root == node::empty) return;
	remove_all(root->left);
	remove_all(root->right);
	delete root;
}

pair<node*,node*> find_value(node *root,long long v,int c){
	node *p = node::empty;	
	while(root != node::empty){
		if(root->value == v) break;
		else if(root->value < v) p = root, root = root->right;
		else p = root,root = root->left;

		if(p != node::empty) p->sz -= c;	
	}
	return make_pair(p,root);
}

node *remove_node(node *u){
	if(u == node::empty) return node::empty;
	if(u->left == node::empty && u->right == node::empty){
		delete u;
		return node::empty;
	}
	node *new_root;
	if(u->right->prior > u->left->prior){
		new_root = left_rotate(u);
		new_root->left = remove_node(u);
	}
	else{
		new_root = right_rotate(u);
		new_root->right = remove_node(u);
	}
	new_root->sz--;
	return new_root;
}

node* remove_value(node *root,long long v){
	pair<node*,node*> tmp = find_value(root,v,0);
	node *p = tmp.first,*u = tmp.second;
	if(u == node::empty) return root;
	find_value(root,v,1);
	if(u->freq > 1) {--u->freq;return root;}
	if(p == node::empty) return remove_node(u);
	if(p->left == u) p->left = remove_node(u);
	else p->right = remove_node(u);
	return root;
}
