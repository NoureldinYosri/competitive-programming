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

struct node{
	ll sum,lazy;
	int siz;
	node *l,*r;
};

const int MAX = 100*1000 + 10;
int A[MAX],n,cur_time;
node *T[MAX];

node *build(int s,int e) {
	node *ret = new node();
	ret->siz = e-s+1;
	if(s == e) {
		ret->sum = A[s];
		return ret;
	}
	int m = (s + e) >> 1;
	ret->l = build(s,m);
	ret->r = build(m+1,e);
	ret->sum = ret->l->sum + ret->r->sum;
	return ret;
}


node *clone(node *root,ll d){
	node *ret = new node();
	*ret = *root;
	ret->lazy += d;
	ret->sum += d*ret->siz;
	return ret;
}

void push(node *root) {
	if(!root->lazy) return;
	root->l = clone(root->l,root->lazy);
	root->r = clone(root->r,root->lazy);
	root->lazy = 0;
}

node *update(node *root,int s,int e,int l,int r,int d) {
	node *ret = new node();
	*ret = *root;
	if(l <= s && e <= r) {
		ret->sum += d*(e-s+1LL);
		ret->lazy += d;
	}
	else{
		push(ret);
		int m = (s + e) >> 1;
		if(r <= m) ret->l = update(ret->l,s,m,l,r,d);
		else if(m < l) ret->r = update(ret->r,m+1,e,l,r,d);
		else {
			ret->l = update(ret->l,s,m,l,m,d);
			ret->r = update(ret->r,m+1,e,m+1,r,d);
		}
		ret->sum = ret->l->sum + ret->r->sum;
	}
//	cerr << s << " " << e << " -> " << (ret->sum) << " after adding " << d << endl;
	return ret;
}


ll query(node *root,int s,int e,int l,int r) {
	if(l <= s && e <= r) return root->sum;
	int m = (s + e) >> 1;
	push(root);
	ll ret = 0;
	if(r <= m) ret = query(root->l,s,m,l,r);
	else if(m < l) ret = query(root->r,m+1,e,l,r);
	else ret = query(root->l,s,m,l,m) + query(root->r,m+1,e,m+1,r);
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int m;
	scanf("%d %d",&n,&m);
	range(i,1,n) scanf("%d",A + i);
	node *root = T[0] = build(1,n);
	loop(i,m) {
		char c; scanf(" %c",&c);
		if(c == 'C') {
			int l,r; scanf("%d %d",&l,&r);
			int d; scanf("%d",&d);
			root = T[++cur_time] = update(root,1,n,l,r,d);
		}
		else if(c == 'Q') {
			int l,r; scanf("%d %d",&l,&r);
			printf("%lld\n",query(root,1,n,l,r));
		}
		else if(c == 'H') {
			int l,r; scanf("%d %d",&l,&r);
			int t; scanf("%d",&t);
			printf("%lld\n",query(T[t],1,n,l,r));
		}
		else {
			int t; scanf("%d",&t);
			root = T[t];
		}
	}
	return 0;
}
