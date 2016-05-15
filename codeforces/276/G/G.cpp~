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

struct vertex{
	int mx,pref,suff,size;
	vertex *left,*right;
public:
	vertex():mx(0),pref(0),suff(0),size(0),left(0),right(0){}
	vertex(int x):mx(x == 1),pref(x == 1),suff(x == 1),size(1),left(0),right(0){}
};

const int MAX = 1e5 + 1e3;
pi SO[MAX];
int H[MAX],n,m;
int V[MAX];
vertex *T[MAX];

vertex* build(int s,int e){
	vertex * r = new vertex(2);
	if(s == e) return r;
	int m = (s + e) >> 1;
	r->left = build(s,m);
	r->right = build(m + 1,e);
	return r;
}

void merge(vertex v1,vertex v2,vertex & r){
	r.size = v1.size + v2.size;
	
	r.mx = max(v1.suff + v2.pref,max(v1.mx,v2.mx));
	
	if(v1.pref == v1.size) r.pref = v1.size + v2.pref;
	else r.pref = v1.pref;
	
	if(v2.suff == v2.size) r.suff = v1.suff + v2.size;
	else r.suff = v2.suff;
}

vertex *update(vertex *root,int s,int e,int p){
	vertex *nr = new vertex(); *nr = *root;
	if(s == e){
		*nr = vertex(1);
		return nr;
	}
	int m = (s + e) >> 1;
	if(p <= m) nr->left = update(root->left,s,m,p);
	else nr->right = update(root->right,m + 1,e,p);
	merge(*nr->left,*nr->right,*nr);
	return nr;
}

vertex query(vertex *root,int s,int e,int l,int r){
	if(l <= s && e <= r) return *root;
	int m = (s + e) >> 1;
	if(r <= m) return query(root->left,s,m,l,r);
	if(m <  l) return query(root->right,m + 1,e,l,r);
	vertex v1,v2,v3;
	v1 = query(root->left,s,m,l,m);
	v2 = query(root->right,m + 1,e,m + 1,r);
	merge(v1,v2,v3);
	return v3;
}



int main(){
	scanf("%d",&n);
	loop(i,n){
		scanf("%d",H + i);
		SO[i].xx = H[i];
		SO[i].yy = i + 1;
		V[i] = H[i];
	}
	sort(SO,SO + n);
	T[n] = build(1,n);
	for(int i = n - 1;i >= 0;i--) T[i] = update(T[i + 1],1,n,SO[i].yy);
	
	sort(V,V + n);
	int N = unique(V,V + n) - V;
	int l,r,w;	
	scanf("%d",&m);
	while(m--){
		scanf("%d %d %d",&l,&r,&w);
		int s = 0,e = N - 1;
		while(s < e){
			int m = s + (e - s + 1)/2;
			int v = lower_bound(SO,SO + n,mp(V[m],0)) - SO;;
			vertex f = query(T[v],1,n,l,r);
			if(f.mx >= w) s = m;
			else e = m - 1;
		}
		printf("%d\n",V[s]);
	}
	return 0;
}
