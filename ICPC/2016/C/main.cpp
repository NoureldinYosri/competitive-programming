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

const int MAX = 111;

struct node{
	node *l,*r;
	int val;
};

string canon;

node* insert(node *root,int v){
	if(root == NULL){
		root = new node();
		root->val = v;
		return root;
	}
	if(v < root->val) {
		root->l = insert(root->l,v);
		return root;
	}
	else{
		root->r = insert(root->r,v);
		return root;
	}
}

void canonize(node *root){
	canon.pb('(');
	if(root){
		canonize(root->l);
		canonize(root->r);
		delete root;		
	}
	canon.pb(')');
}

int main(){
	int n,k; scanf("%d %d",&n,&k);
	vector<string> V;
	loop(i,n){
		int x;
		node *root = NULL;			
		loop(j,k) {
			scanf("%d",&x);
			root = insert(root,x);
		}
		canonize(root);
		V.pb(canon);
		canon.clear();
	}
	sort(all(V));
	cerr << unique(all(V)) - V.begin() << endl;
	
	return 0;
}
