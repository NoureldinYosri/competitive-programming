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
	int val;
	node *l,*r;
};

const int MAX = 400*1000 + 10;
int oo;
int H[MAX],n,m;
vector<vi> LIS;
bool I[MAX],C[MAX];
int ans[MAX];
vp Q[MAX];
int X[MAX],Y[MAX],z;


node *update(node *root,int s,int e,int p,int v) {
	if(!root) root = new node();
	root->val = max(root->val,v);
	if(s == e) return root;
	int m = (s + e) >> 1;
	if(p <= m) root->l = update(root->l,s,m,p,v);
	else root->r = update(root->r,m+1,e,p,v);
	return root;
}

int query(node *root,int s,int e,int l,int r) {
	if(!root) return 0;
	if(l <= s && e <= r) return root->val;
	int m = (s + e) >> 1;
	if(r <= m) return query(root->l,s,m,l,r);
	if(m < l) return query(root->r,m+1,e,l,r);
	return max(query(root->l,s,m,l,m),query(root->r,m+1,e,m+1,r));
}

void doLIS(){
	LIS.push_back(vi{0});
	for(int i = 1;i < n;i++){
		if(H[i] > H[LIS.back().back()]) LIS.push_back(vi{i});
		else {
			int s = 0,e = sz(LIS) - 1;
			while(s < e) {
				int mid = (s + e) >> 1;
				if(H[LIS[mid].back()] >= H[i]) e = mid;
				else s = mid + 1;
			}
			LIS[s].push_back(i);
		}
	}
	for(int x : LIS.back()) C[x] = 1;
	vi aux;
	for(int k = sz(LIS) - 1;k > 0;k--) {
		for(int x : LIS[k]) if(C[x]) aux.push_back(x);
		if(sz(aux) == 1) {
			for(int x : aux) I[x] = 1;
		}

		for(int x : LIS[k - 1]) {
			if(x > aux.back()) continue;
			int y = *lower_bound(all(aux),x);
			if(H[x] < H[y]) C[x] = 1;
		}
		aux.clear();
	}

	for(int x : LIS[0]) if(C[x]) aux.push_back(x);
	if(sz(aux) == 1) {
		for(int x : aux)
			I[x] = 1;
	}
	aux.clear();
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",H + i);
	copy(H,H + n,X);
	sort(X,X + n);
	z = unique(X,X + n) - X;
	X[z++] = 1000*1000*1000 + 1;
	loop(i,n) H[i] = upper_bound(X,X + z,H[i]) - X;
	loop(i,z) Y[i] = upper_bound(X,X + z,X[i]) - X;
	oo = z + 1;

	loop(i,m) {
		int p ,h; scanf("%d %d",&p,&h);
		--p;
		Q[p].push_back(mp(h,i));
	}




	doLIS();

	node *root = 0;
	loop(i,n) {
		for(auto p : Q[i]) {
			int j = p.yy,h = p.xx;
			int th = lower_bound(X,X + z,h) - X;
			h = Y[th];
			ans[j] = query(root,0,oo,0,h-1);
		}
		int v = query(root,0,oo,0,H[i] - 1) + 1;
		root = update(root,0,oo,H[i],v);
	}

//	prArr(X,z,int);
//	prArr(Y,z,int);

	root = 0;
	for(int i = n-1;i >= 0;i--) {
		for(auto p : Q[i]) {
			int j = p.yy,h = p.xx;
			int th = upper_bound(X,X + z,h) - X;
			h = Y[th];
			ans[j] += query(root,0,oo,h,oo);
			ans[j]++;
			ans[j] = max(ans[j],sz(LIS) - I[i]);
		}
		int v = query(root,0,oo,H[i] + 1,oo) + 1;
		root = update(root,0,oo,H[i],v);
	}


	loop(i,m) printf("%d\n",ans[i]);

	return 0;
}
