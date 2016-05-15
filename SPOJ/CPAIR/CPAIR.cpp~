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
int usd[MAX],S[MAX],E[MAX];
pair<pi,pi> A[2*MAX];
pair<pl,ll> ST[MAX << 2];
ll ans[MAX];
int n,m;

pair<pl,ll> operator + (const pair<pl,ll> & a,const pair<pl,ll> & b){
	return mp(mp(a.xx.xx + b.xx.xx,a.xx.yy + b.xx.yy),a.yy + b.yy);
}

void update(int node,int s,int e,int p,int v){
	if(s == e){
		ST[node].xx.xx += v*s;
		ST[node].xx.yy += v;
		ST[node].yy += v*p*(p + 1LL)/2;
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m + 1,e,p,v);
	ST[node] = ST[left] + ST[right];
}

ll query(int node,int s,int e,int v){
	if(v <= s) return ST[node].xx.xx*v - ST[node].xx.yy*v*(v - 1)/2;
	if(e <  v) return ST[node].yy;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	return query(left,s,m,v) + query(right,m + 1,e,v);
}


void merge(int l,int r){
	update(1,1,n,E[l] - S[l] + 1,-1);
	update(1,1,n,E[r] - S[r] + 1,-1);
	update(1,1,n,E[r] - S[l] + 1,1);
	int s = S[l],e = E[r];
	usd[l] = usd[r] = 0;
	usd[s] = usd[e] = 1;
	E[s] = e;
	S[e] = s;
//	cerr << "create " << e - s + 1 << endl;
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) {
		scanf("%d",&A[i].xx.xx);
		A[i].xx.yy = i + 1;
	}
	loop(i,m) {
		scanf("%d %d %d",&A[i + n].xx.xx,&A[i + n].yy.xx,&A[i + n].yy.yy);
		A[i + n].xx.yy = -i-1;
	}
	sort(A,A + n + m);
	reverse(A,A + n + m);
	
	loop(i,n + m){
		int v = A[i].xx.xx,idx = A[i].xx.yy,s = A[i].yy.xx,e = A[i].yy.yy;
		if(idx > 0){
			usd[idx] = 1;
			S[idx] = E[idx] = idx;
			update(1,1,n,1,1);
			if(usd[idx - 1]) merge(idx - 1,idx);
			if(usd[idx + 1]) merge(idx,idx + 1);		
		}
		else {
			idx = - 1- idx;
			ans[idx] = query(1,1,n,e);
			s--;
			if(s) ans[idx] -= query(1,1,n,s);
	//		cerr << idx << " " << query(1,1,n,e) << " " << query(1,1,n,s) << endl;
		} 		
	}
	loop(i,m) printf("%lld\n",ans[i]);
	return 0;
}
