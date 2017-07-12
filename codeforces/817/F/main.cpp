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

const int MAX = 300*1000;

struct vertex{
	ll s,e,mex;
	bool to_invert,is_complete;
	vertex *l,*r;
public:
	vertex(){
		s = e = mex = l = r = to_invert = 0;
		is_complete = 1;
	}
	vertex(ll _s,ll _e){
		s = _s;
		e = _e;
		l = r = to_invert = 0;
		mex = LLONG_MAX;
		is_complete = 1;
	}
};


ll get_mex(vertex *node,ll s,ll e){
	if(!node) return s;
	return node->mex;
}

bool get_comp(vertex *node){
	return node ? node->is_complete : 0;
}

vertex* add_all(vertex *node,ll s,ll e,ll l,ll r){
	if(l <= s && e <= r) return new node(s,e);
	if(!node) node = new node(s,e);
	ll m = (s + e) >> 1;
	if(e <= m) node->l = add_all(node->l,s,m,l,r);
	else if(m < l) node->r = add_all(node->r,m+1,e,l,r);
	else{
		node->l = add_all(node->l,s,m,l,m);
		node->r = add_all(node->r,m+1,e,m+1,r);
	}
	node->mex = min(get_mex(node->l,s,m),get_mex(node->r,m+1,e));
	node->is_complete = get_comp(node->l) && get_comp(node->r);
	if(node->is_complete) {
		delete node->l;
		delete node->r;
		delete node;
		node = new node(s,e);
	}
	return node;
}

vertex* erase_all(vertex *node,ll s,ll e,ll l,ll r){
	if(l <= s && e <= r) return NULL;
	if(!node) node = new node(s,e);
	ll m = (s + e) >> 1;
	if(e <= m) node->l = erase_all(node->l,s,m,l,r);
	else if(m < l) node->r = erase_all(node->r,m+1,e,l,r);
	else{
		node->l = erase_all(node->l,s,m,l,m);
		node->r = erase_all(node->r,m+1,e,m+1,r);
	}
	node->mex = min(get_mex(node->l,s,m),get_mex(node->r,m+1,e));
	node->is_complete = 0;
	return node;
}

vertex* invert(vertex *node,ll s,ll e,ll l,ll r){
	if(l <= s && e <= r) {
		ll m = (s + e) >> 1;
		if(s == e) return node ? LLONG_MAX : s;
		if(!node) return new node(s,e);
		if(node->l && node->r) {

		}
		else if(node->l){
			node->r = new node(m+1,e);
			node->l = invert(node->l,s,m,l,min(l,m));
			node->mex =
		}
		else if(node->r){

		}
		else return NULL;
	}
	if(!node) node = new node(s,e);
	ll m = (s + e) >> 1;
	if(e <= m) node->l = invert(node->l,s,m,l,r);
	else if(m < l) node->r = invert(node->r,m+1,e,l,r);
	else{
		node->l = invert(node->l,s,m,l,m);
		node->r = invert(node->r,m+1,e,m+1,r);
	}
	node->mex = min(get_mex(node->l,s,m),get_mex(node->r,m+1,e));
	return node;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif

	return 0;
}
