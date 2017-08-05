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
#define popcnt(x) __builtin_popcount(x)
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

struct node{
	node *l,*r;
	vp content;
	vi BIT;
};

const int MAX = 100*1000 + 10;
int X1[MAX],X2[MAX],Y1[MAX],Y2[MAX],n;
int type[MAX],which[MAX];
node *V,*H;
vector<node*> places [MAX];
int S = -1000000000,E = 1000000000;


node* init_insert(node *root,int s,int e,int l,int r,int y,int id){
	if(!root) root = new node();
	if(l <= s && e <= r) {
		root->content.pb(mp(y,id));
		places[id].pb(root);
	}
	else{
		int m = s + (e - s)/2;
		if(r <= m) root->l = init_insert(root->l,s,m,l,r,y,id);
		else if(m < l) root->r = init_insert(root->r,m+1,e,l,r,y,id);
		else {
			root->l = init_insert(root->l,s,m,l,m,y,id);
			root->r = init_insert(root->r,m+1,e,m+1,r,y,id);
		}
	}
	return root;
}

void traverse(node *root){
	if(!root) return;
	root->BIT = vi(sz(root->content) + 1);
	sort(all(root->content));
	traverse(root->l);
	traverse(root->r);
}

void update(int p,int v,vi & BIT){
	for(;p < sz(BIT);p += LSOne(p)) BIT[p] += v;
}

int get(int p,vi & BIT){
	int ret = 0;
	for(;p;p ^= LSOne(p)) ret += BIT[p];
	return ret;
}


void update(node *root,int v,int y,int id){
	int pos = lower_bound(all(root->content),mp(y,id)) - root->content.begin();
	assert(root->content[pos] == mp(y,id));
	update(pos+1,v,root->BIT);
}

/*
 * node* insert(node *root,int s,int e,int l,int r,int y,int id){
	assert(root != 0);
	if(!root) root = new node();
	if(l <= s && e <= r) {
		int pos = lower_bound(all(root->content),mp(y,id)) - root->BIT.begin();
		assert(root->content[pos] == mp(y,id));
		update(pos+1,1,root->BIT);
	}
	else{
		int m = s + (e - s)/2,left = node << 1,right = left | 1;
		if(r <= m) root->l = insert(root->l,s,m,l,r,y,id);
		else if(m < l) root->r = insert(root->r,m+1,e,l,r,y,id);
		else {
			root->l = insert(root->l,s,m,l,m,y,id);
			root->r = insert(root->r,m+1,e,m+1,r,y,id);
		}
	}
	return root;
}
*/

int get(node *root,int y){
	auto p = lower_bound(all(root->content),mp(y+1,-1))
			- root->content.begin();
	return get(p,root->BIT);
}

int eval(node *root,int y1,int y2){
	return get(root,y2) - get(root,y1-1);
}

int query(node *root,int s,int e,int x,int y1,int y2){
	if(!root) return 0;
	int ret = eval(root,y1,y2);
	int m = s + (e - s)/2;
	if(x <= m) ret += query(root->l,s,m,x,y1,y2);
	else ret += query(root->r,m+1,e,x,y1,y2);
	return ret;
}
vi T(MAX,0);

ll work(int i,int v){
	ll ret = 0;
	int y = (Y1[i] == Y2[i]) ? Y1[i] : X1[i];
	if(Y1[i] == Y2[i]) ret += query(V,S,E,Y1[i],X1[i],X2[i]);
	else ret += query(H,S,E,X1[i],Y1[i],Y2[i]);
	for(node* ptr : places[i])
		update(ptr,v,y,i);
	update(i+1,v,T);
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n){
		scanf("%d",type + i);
		if(type[i] == 1) {
			scanf("%d %d %d %d",X1 + i,Y1 + i,X2 + i,Y2 + i);
			if(Y1[i] == Y2[i] && X1[i] > X2[i]) swap(X1[i],X2[i]);
			if(X1[i] == X2[i] && Y1[i] > Y2[i]) swap(Y1[i],Y2[i]);
			if(Y1[i] == Y2[i]) H = init_insert(H,S,E,X1[i],X2[i],Y1[i],i);
			else V = init_insert(V,S,E,Y1[i],Y2[i],X1[i],i);
		}
		else scanf("%d",which + i);
	}

	traverse(H);
	traverse(V);

	ll ans = 0;
	loop(i,n){
		if(type[i] == 1) ans += work(i,1);
		else {
			int s = 0,e = i-1;
			while(s < e) {
				int m = (s + e) >> 1;
				if(get(m+1,T) >= which[i]) e = m;
				else s = m + 1;
			}
			ans -= work(s,-1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
