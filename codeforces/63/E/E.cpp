#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

struct node{
	int count,value;
	node *left,*right;
public: 
	node():count(0),right(0),left(0),value(INT_MIN){}
	node(int a):count(1),value(a),right(0),left(0){};
};

void insert(node *& root,int s,int e,int value,int d){
	if(!root) root = new node();	
	if(s == e){
		root->count += d;
		if(root->count == 1) root->value = value;
		else root->value = INT_MIN;
		return;
	}
	int m = s + ((e - s) >> 1);
	if(value <= m) insert(root->left,s,m,value,d);
	else insert(root->right,m + 1,e,value,d);
	root->value = INT_MIN;
	if(root->left) root->value = max(root->value ,root->left->value);
	if(root->right) root->value = max(root->value ,root->right->value);
}


int A[1 << 20];

int main(){
	int n,k; scanf("%d %d",&n,&k);
	node *root = new node();	
	loop(i,k) {
		scanf("%d",A + i);
		insert(root,-1e9,1e9,A[i],1);
	}		
	loop(i,n - k){
		if(root->value != INT_MIN) printf("%d\n",root->value);
		else puts("Nothing");
		scanf("%d",A + i + k);
		insert(root,-1e9,1e9,A[i + k],1);
		insert(root,-1e9,1e9,A[i],-1);
	}
	if(root->value != INT_MIN) printf("%d\n",root->value);
	else puts("Nothing");
	return 0;
}
