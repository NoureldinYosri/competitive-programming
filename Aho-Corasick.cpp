#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int ctr = 0;
char P[1000][3000];
int A[1000];

struct node{
	vi pats;
	bool visited;
	node *nxt[128],*fail;
	vector<char> chr;
	int idx;
public:
	node():visited(0),fail(0),idx(++ctr){loop(i,128) nxt[i] = NULL;}
	node(int x):visited(0),fail(0),idx(++ctr){pats.pb(x);loop(i,128) nxt[i] = NULL;}
};

void insert(const char* s,node* root,int x){
	for(;*s;s++){
		if(root->nxt[*s]) root = root->nxt[*s];
		else root->chr.pb(*s),root = root->nxt[*s] = new node();
	}
	root->pats.pb(x);
}

void build_fail(node* root){
	queue<node*> q;	
	for(auto c : root->chr) {
		q.push(root->nxt[c]);
		root->nxt[c]->fail = root;
	//	cout << root->nxt[c]->idx << " " << root->idx << endl;
	}
	node *u,*v;
	while(!q.empty()){
		u = q.front(); q.pop();
		for(auto c : u->chr){
			v = u->fail;
			while(v && !v->nxt[c]) v = v->fail;

			if(v) v = v->nxt[c];
			else v = root;
			u->nxt[c]->fail = v;
			//cout << u->nxt[c]->idx << " " << v->idx << endl;
			for(auto a : v->pats) u->nxt[c]->pats.pb(a);
			q.push(u->nxt[c]);	
		}
	}
}

void match(const char *T,node *root,vi & V){
	V.clear();
	node *u = root,*v;
	for(int i = 0,L = strlen(T);*T;T++,i++){
		v = u;
		while(u && !u->nxt[*T]) u = u->fail;		
		if(!u) {u = root; continue;}
		//cout << v->idx << " " << u->idx << endl;			
		u = u->nxt[*T];
		for(auto a : u->pats)		
			A[a] = 1;
	}
}

void remove(node *u){
	queue<node*> q;
	q.push(u);
	while(!q.empty()){
		u = q.front(); q.pop();
		for(auto c : u->chr) q.push(u->nxt[c]);
		delete u;
	}
}

bool cmp(const pi & p1,const pi & p2){
	return (p1.first == p2.first) ? p1.second > p2.second : p1.first < p2.first;
}


int main(){
	int n; char T[5000000];
	node *root = new node(); vi V;
	scanf("%s",T);
	scanf("%d",&n);
	loop(i,n) scanf("%s",P[i]),insert(P[i],root,i);
	build_fail(root);
	match(T,root,V);
	loop(i,n) puts(A[i] ? "Y" : "N");
	return 0;
}

