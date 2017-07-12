#include <bits/stdc++.h>
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

const int LIM = 100000;
int main(){
	node *root = new node(0);
	for(int i = 1;i <= LIM;i++) root = insert(root,i);	
	cout << lower_bound(root,5) << endl;
}
