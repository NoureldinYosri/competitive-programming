#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
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
#define pl pair<ll,ll>
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

struct vertex{
	vertex *l,*r;
	int mn,lazy;
};

const int MAX = 3*100*1000 + 10;
int A[MAX],n,k,q,m;
int L[MAX],R[MAX],type[MAX],ans[MAX],val[MAX];
int ST1[MAX << 2];

void build1(int node,int s,int e){
	if(s == e){
		ST1[node] = A[s];
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build1(left,s,m);
	build1(right,m+1,e);
	ST1[node] = min(ST1[left],ST1[right]);
}

int query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST1[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	return min(query(left,s,m,l,m),query(right,m+1,e,m+1,r));
}

vertex* update(vertex *root,int s,int e,int v){
	if(!root) root = new vertex();
	root->lazy = root->mn = v;
	return root;
}

void push(vertex *root,int s,int e){
	if(!root->lazy) return;
	int m = (s + e) >> 1;
	root->l = update(root->l,s,m,root->lazy);
	root->r = update(root->r,m+1,e,root->lazy);
	root->lazy = 0;
}

int get_val(vertex *root,int s,int e){
	if(root) return root->mn;
	if(e - s + 1 >= n) return ST1[1];
	s %= n;
	e %= n;
	if(s <= e) return query(1,0,n-1,s,e);
	else return min(query(1,0,n-1,s,n-1),query(1,0,n-1,0,e));
}

vertex* update(vertex *root,int s,int e,int l,int r,int v){
	if(l <= s && e <= r) return update(root,s,e,v);
	if(!root) root = new vertex();
	push(root,s,e);
	int m = (s + e) >> 1;
	if(r <= m) root->l = update(root->l,s,m,l,r,v);
	else if(m < l) root->r = update(root->r,m+1,e,l,r,v);
	else {
		root->l = update(root->l,s,m,l,m,v);
		root->r = update(root->r,m+1,e,m+1,r,v);
	}
	root->mn = min(get_val(root->l,s,m),get_val(root->r,m+1,e));
	return root;
}

int query(vertex *root,int s,int e,int l,int r){
	if(l <= s && e <= r) return get_val(root,s,e);
	if(!root) return get_val(0,l,r);
	push(root,s,e);
	int m = (s + e) >> 1;
	if(r <= m) return query(root->l,s,m,l,r);
	if(m < l)return query(root->r,m+1,e,l,r);
	return min(query(root->l,s,m,l,m),query(root->r,m+1,e,m+1,r));
}


int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
		freopen("out.out", "w", stdout);
	#endif
	scanf("%d %d",&n,&k);
	loop(i,n) scanf("%d",A + i);
	build1(1,0,n-1);

	vertex *root = NULL;

	scanf("%d",&q);

	loop(i,q){
		scanf("%d %d %d",type + i,L + i,R + i);
		L[i]--,R[i]--;
		if(type[i] == 1) {
			scanf("%d",val + i);
			root = update(root,0,n*k-1,L[i],R[i],val[i]);
		}
		else printf("%d\n",query(root,0,n*k-1,L[i],R[i]));
	}

	return 0;
}
