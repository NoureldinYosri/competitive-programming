#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int MAX = 100*1000,MAXST = 1 << 18,B = 110;
struct node{
	double val,lazy;
	double taylor[B];
	bool has_lazy ;
	node(){
		has_lazy = 0;
		val = lazy = 1;
		fill(taylor,taylor + B,0);
	}
	node(double v) {
		has_lazy = 0;
		lazy = 1;
		val = 1 - v;
		double p = v;
		for(int i = 0;i < B;i++,p *= v)
			taylor[i] = -p / (i + 1);
	}
};
double A[MAX];
node ST[MAXST];
int n;


node merge(node L,node R) {
	node ret;
	ret.val = L.val * R.val;
	for(int i = 0;i < B;i++)
		ret.taylor[i] = L.taylor[i] + R.taylor[i];
	return ret;
}

void build(int cur,int s,int e) {
	if(s == e) {
		ST[cur] = node(A[s]);
		return;
	}
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	build(left,s,m);
	build(right,m+1,e);
	ST[cur] = merge(ST[left],ST[right]);
}


void update(node & u,double T) {
	double p = T;
	u.val = 0;
	for(int i = 0;i < B;i++){
		u.taylor[i] *= p;
		p *= T;
		u.val += u.taylor[i];
	}
	u.val = exp(u.val);
	u.lazy *= T;
	u.has_lazy = 1;
}

void push(int cur) {
	if(!ST[cur].has_lazy) return;
	int left = 2*cur + 1,right = left + 1;
	update(ST[left],ST[cur].lazy);
	update(ST[right],ST[cur].lazy);
	ST[cur].lazy = 1;
	ST[cur].has_lazy = 0;
}

void update(int cur,int s,int e,int l,int r,double T) {
	if(l <= s && e <= r) return update(ST[cur],T);
	push(cur);
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(r <= m) update(left,s,m,l,r,T);
	else if(m < l) update(right,m+1,e,l,r,T);
	else {
		update(left,s,m,l,m,T);
		update(right,m+1,e,m+1,r,T);
	}
	ST[cur] = merge(ST[left] , ST[right]);
}

node query(int cur,int s,int e,int l,int r) {
	if(l <= s && e <= r) return ST[cur];
	push(cur);
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(r <= m) return query(left,s,m,l,r);
	else if(m < l) return query(right,m+1,e,l,r);
	else return merge(query(left,s,m,l,m) , query(right,m+1,e,m+1,r));
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
//	freopen("err.log","w",stderr);
//	freopen("out.out","w",stdout);
#endif
	int m; scanf("%d %d",&n,&m);
	range(i,1,n) scanf("%lf",A + i);
	build(0,1,n);
	while(m--) {
		int t,l,r;scanf("%d %d %d",&t,&l,&r);
		if(t == 0) printf("%.10lf\n",query(0,1,n,l,r).val);
		else {
			double T; scanf("%lf",&T);
			update(0,1,n,l,r,T);
		}
	}
	return 0;
}
