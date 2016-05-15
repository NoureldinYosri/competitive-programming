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

const int MAX = 1e5 + 1e3;
pl ST[MAX << 2],LAZY[MAX << 2];
ll A[MAX];
int T,n,m;

pl operator + (const pl & a,const pl & b){
	return mp(a.xx + b.xx,a.yy + b.yy);
}

ostream & operator << (ostream & st ,const pl & a){
	st << "(" << a.xx << " ," << a.yy << ")";
	return st;
}

pl build(int node,int s,int e){
	LAZY[node] = mp(INT_MIN+0LL,0LL);
	if(s == e) return ST[node] = mp(A[s]*1LL*A[s],A[s]);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	return ST[node] = build(left,s,m) + build(right,m + 1,e);
}


void forward(int node,int child,int L){
	if(LAZY[node].xx != INT_MIN) {
		LAZY[child] = LAZY[node];
		ST[child].xx = (LAZY[node].xx + LAZY[node].yy)*(LAZY[node].xx + LAZY[node].yy) * L;
		ST[child].yy = (LAZY[node].xx + LAZY[node].yy) * L;
	}
	else {
		LAZY[child].yy += LAZY[node].yy;
		ST[child].xx += 2*ST[child].yy * LAZY[node].yy + LAZY[node].yy*LAZY[node].yy*L;
		ST[child].yy += LAZY[node].yy*L; 
	}
}

void update1(int node,int s,int e,int l,int r,ll v){
	if(l <= s && e <= r){
		ST[node] = mp(v*v*(e - s + 1),v*(e - s + 1));
		LAZY[node] = mp(v,0);
		return ;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	forward(node,left,m - s + 1);
	forward(node,right,e - m);	
	LAZY[node] = mp(INT_MIN,0LL);
	if(r <= m) update1(left,s,m,l,r,v);
	else if(m < l) update1(right,m + 1,e,l,r,v);
	else update1(left,s,m,l,m,v),update1(right,m + 1,e,m + 1,r,v);
	ST[node] = ST[left] + ST[right];
}

void update2(int node,int s,int e,int l,int r,ll v){
	if(l <= s && e <= r){
		ST[node].xx += 2*v*ST[node].yy + (e - s + 1)*v*v;
		ST[node].yy += v*(e - s + 1);
		LAZY[node].yy += v;
		return ;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	forward(node,left,m - s + 1);
	forward(node,right,e - m);	
	LAZY[node] = mp(INT_MIN,0LL);
	if(r <= m) update2(left,s,m,l,r,v);
	else if(m < l) update2(right,m + 1,e,l,r,v);
	else update2(left,s,m,l,m,v),update2(right,m + 1,e,m + 1,r,v);
	ST[node] = ST[left] + ST[right];
}

pl query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	pl ret;
	if(r <= m) ret = query(left,s,m,l,r);
	else if(m < l) ret = query(right,m + 1,e,l,r);
	else ret = query(left,s,m,l,m) + query(right,m + 1,e,m + 1,r);
	if(LAZY[node].xx == INT_MIN){
		ret.xx += ret.yy * 2 * LAZY[node].yy + LAZY[node].yy*LAZY[node].yy * (r - l + 1);
		ret.yy += LAZY[node].yy * (r - l + 1);
	}
	else {
		ret.xx = (LAZY[node].xx + LAZY[node].yy)*(LAZY[node].xx + LAZY[node].yy)*(r - l + 1);
		ret.yy = (LAZY[node].xx + LAZY[node].yy)*(r - l + 1);
	}
	return ret;
}


int main(){
	int c,s,e,x;
	scanf("%d",&T);
	range(t,1,T){
		printf("Case %d:\n",t);
		scanf("%d %d",&n,&m);
		loop(i,n) scanf("%lld",A + i);
		build(1,0,n - 1);
		while(m--){
			scanf("%d %d %d",&c,&s,&e);
			s--,e--;			
			if(c == 2) printf("%lld\n",query(1,0,n - 1,s,e).xx);
			else {
				scanf("%d",&x);
				if(c == 1) update2(1,0,n - 1,s,e,x);
				else update1(1,0,n - 1,s,e,x);
			}
		}
	}			
	return 0;
}
