#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
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
using namespace std;


struct val{
	ll f1,f2,mx;
};

const int MAX = 100'010 * 2;
int n,m;
int A[MAX],h[MAX];
ll D[MAX];
ll f1[MAX],f2[MAX << 1];
val ST[MAX << 2];

val merge(val A,val B){
	val ret ;
	ret.mx = max(A.mx,B.mx);
	ret.mx = max(ret.mx,A.f2 + B.f1);
	ret.f2 = max(A.f2,B.f2);
	ret.f1 = max(A.f1,B.f1);
	return ret;
}

void build(int node,int s,int e){
	if(s == e){
		ST[node].mx = 0;
		ST[node].f1 = f1[s];
		ST[node].f2 = f2[s];
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
	ST[node] = merge(ST[left],ST[right]);
} 


val query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	return merge(query(left,s,m,l,m),query(right,m+1,e,m+1,r));
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i);
	loop(i,n) scanf("%d",h + i);
	
	range(i,1,2*n) {
		D[i + 1] = D[i] + A[(i - 1)%n];
		f1[i] = D[i] + 2*h[(i-1)%n];
		f2[i] = -D[i] + 2*h[(i-1)%n];
	}
//	prArr(D+1,2*n,ll);	
//	prArr(f1+1,2*n,ll);
//	prArr(f2+1,2*n,ll);
	build(1,1,2*n);
	
	while(m--){
		int l,r; scanf("%d %d",&l,&r);
		ll ans; 
		if(l <= r) {
			if(l == 1) ans = query(1,1,2*n,r+1,n).mx ;
			else ans = query(1,1,2*n,r+1,n+l-1).mx;
		}
		else ans = query(1,1,2*n,r+1,l-1).mx;
//		cerr << ans << endl;
		printf("%lld\n",ans);
	}
	
	return 0;
}
