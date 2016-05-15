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


struct cell{
	ll pref,suff,mx,tot;
public:
	cell(){pref = suff = mx = INT_MIN;tot = 0;}
	cell(ll x) {pref = suff = mx = tot = x;}
};
ll A[10000],B[10000];
int ST[10000 << 2][2];
cell ST2[10000 << 2];
int n;

void compine(int *a,int *b, int *c){
	c[0] = min(a[0],b[0]);
	c[1] = max(a[1],b[1]);
}

cell merge(cell a,cell b){
	cell ret;
	ret.pref = max(a.pref,a.tot + b.pref);
	ret.suff = max(b.suff,b.tot + a.suff);
	ret.tot  = a.tot + b.tot;
	ret.mx = max(a.mx,b.mx);
	ret.mx = max(ret.mx,a.suff + b.pref);
	ret.mx = max(ret.mx,ret.tot);
	ret.mx = max(ret.mx,ret.pref);
	ret.mx = max(ret.mx,ret.suff);
	return ret;
}

void build(int node,int s,int e){
	if(s == e) {
		loop(i,2) ST[node][i] = A[s];
		ST2[node] = cell(B[s]);
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m + 1,e);
	compine(ST[left],ST[right],ST[node]);
	ST2[node] = merge(ST2[left],ST2[right]);
	//cerr << s << " " << e << " " << ST2[node].pref << " " << ST2[node].suff << " " << ST2[node].mx << " " << ST2[node].tot << endl;
}

void query(int node,int s,int e,int l,int r,ll *ans){
	if(l <= s && e <= r){
		copy(ST[node],ST[node] + 2,ans);
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r,ans);
	if(m <  l) return query(right,m + 1,e,l,r,ans);
	ll a[2],b[2];
	query(left,s,m,l,m,a);
	query(right,m + 1,e,m + 1,r,b);
	ans[0] = min(a[0],b[0]);
	ans[1] = max(a[1],b[1]);	
}

cell query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST2[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m <  l) return query(right,m + 1,e,l,r);
	return merge(query(left,s,m,l,m),query(right,m + 1,e,m + 1,r));
}


ll f(int x1,int y1,int x2,int y2){
	x1--,y1--;
	ll A[2],B[2];
	query(1,0,n,x1,y1,A);
	query(1,0,n,x2,y2,B);
	return B[1] - A[0];		
}

int main(){
	int T,x1,x2,y1,y2,m;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		loop(i,n) {
			scanf("%lld",A + i + 1);
			B[i + 1] = A[i + 1];
			A[i + 1] += A[i];
		}
		build(1,0,n);
		scanf("%d",&m);
		while(m--){
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			if(y1 < x2) printf("%lld\n",f(x1,y1,x2,y2));
			else{
				ll ans = query(1,0,n,x2,y1).mx;
				if(x2 > x1) ans = max(ans,f(x1,x2 - 1,x2,y2));
				if(y1 < y2) ans = max(ans,f(x1,y1,y1 + 1,y2));
				printf("%lld\n",ans);
			}
		}
	}
	return 0;
}
