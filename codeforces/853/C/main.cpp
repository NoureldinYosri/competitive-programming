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
	int siz;
	node *l,*r;
};

node *build(int s,int e){
	node *ret = new node();
	if(s == e) return ret;
	int m = (s + e) >> 1;
	ret->l = build(s,m);
	ret->r = build(m+1,e);
	return ret;
}

node* update(node *root,int s,int e,int p){
	node *ret = new node();
	*ret = *root;
	ret->siz++;
	if(s == e) return ret;
	int m = (s + e) >> 1;
	if(p <= m) ret->l = update(root->l,s,m,p);
	else ret->r = update(root->r,m+1,e,p);
	return ret;
}


int query(node *u,node *v,int s,int e,int p){
	if(e <= p) return v->siz - u->siz;
	int m = (s + e) >> 1;
	if(p <= m) return query(u->l,v->l,s,m,p);
	else return query(u->l,v->l,s,m,p) + query(u->r,v->r,m+1,e,p);
}


const int MAX = 200*1000 + 10;
int P[MAX],n,Q;
ll ans[MAX];
node *T[MAX];

// عربي
inline ll C(ll x){
	return x*(x - 1LL)/2;
}


ll get(int c1,int c2,int r1,int r2){
	if(c1 > c2 || r1 > r2) return 0;
	int cnt = query(T[c1-1],T[c2],0,n+1,r2);
	cnt -= query(T[c1-1],T[c2],0,n+1,r1 - 1);
	return C(cnt);
}
int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&Q);
	T[0] = build(0,n+1);
	range(i,1,n) {
		scanf("%d",P + i);
		T[i] = update(T[i-1],0,n+1,P[i]);
	}
	loop(i,Q){
		int c1,c2,r1,r2;
		scanf("%d %d %d %d",&c1,&r1,&c2,&r2);
		if(c1 > c2) swap(c1,c2);
		if(r1 > r2) swap(r1,r2);
		//cerr << r1 << " " << r2 << " " << c1 << " " << c2 << endl;
		ll ans = C(c1 - 1) + C(r1 - 1) + C(n - r2) + C(n - c2);
		//cerr << C(c1-1) << " " << C(r1-1) << " " << C(n-r2) << " " << C(n-c2) << endl;
		ans -= get(1,c1-1,1,r1-1);
		ans -= get(c2+1,n,1,r1-1);
		ans -= get(1,c1-1,r2+1,n);
		ans -= get(c2+1,n,r2+1,n);
		assert(ans >= 0);
		ans = C(n) - ans;
		printf("%lld\n",ans);
	}

	return 0;
}
