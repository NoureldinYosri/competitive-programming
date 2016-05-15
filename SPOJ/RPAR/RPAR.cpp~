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

const int mod = 10007;
const int MAX = 100000;

int add(ll a,ll b){
	a %= mod;
	b %= mod;
	return (a + b)%mod;	
}

int mul(ll a,ll b){
	a %= mod;
	b %= mod;
	return (a*b)%mod;
}

struct vertex{
	ll sum_x2,sum_x,size,tot;
	ll a,b,c;
public:
	vertex(){sum_x2 = sum_x = size = tot = a = b = c = 0;}
	vertex(int x){
		sum_x2 = mul(x,x);
		sum_x =  mul(1,x);;
		size = 1;
		tot = a = b = c = 0;
	}
	int update(int A,int B,int C){
		int v = add(mul(A,sum_x2),add(mul(B,sum_x),mul(C , size)));
		a = add(a,A); b = add(b,B); c = add(c,C);
		tot = add(tot,v);		
		return v;
	}
};

vertex ST[MAX << 2];

void build(int node,int s,int e){
	if(s == e){
		ST[node] = vertex(s);
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m + 1,e);
	ST[node] = vertex();
	ST[node].sum_x2 = add(ST[left].sum_x2,ST[right].sum_x2);
	ST[node].sum_x = add(ST[left].sum_x,ST[right].sum_x);
	ST[node].size = add(ST[left].size,ST[right].size);
}

int update(int node,int s,int e,int l,int r,int a,int b,int c){
	if(l <= s && e <= r) return ST[node].update(a,b,c);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) {
		int v = update(left,s,m,l,r,a,b,c);
		ST[node].tot = add(ST[node].tot,v);
		return v;
	}
	if(m < l) {
		int v = update(right,m + 1,e,l,r,a,b,c);
		ST[node].tot = add(ST[node].tot,v);
		return v;
	}
	int u = update(left,s,m,l,m,a,b,c);
	int v = update(right,m + 1,e,m + 1,r,a,b,c);
	ST[node].tot = add(ST[node].tot,add(u,v));
	return add(u,v);
}

int query(int node,int s,int e,int l,int r,int a,int b,int c){
	if(l <= s && e <= r){
		int v = ST[node].tot;
		v = add(v,mul(a , ST[node].sum_x2));
		v = add(v,mul(b , ST[node].sum_x));
		v = add(v,mul(c , ST[node].size));
		return v;
	}
	a = add(a,ST[node].a); b = add(b,ST[node].b); c = add(c,ST[node].c);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r,a,b,c);
	if(m  < l) return query(right,m + 1,e,l,r,a,b,c);
	int u = query(left,s,m,l,m,a,b,c);
	int v = query(right,m + 1,e,m + 1,r,a,b,c);
	return add(u,v);
}

int main(){
	int n,m,t,l,r,a,b,c;
	scanf("%d %d",&n,&m);
	build(1,0,n - 1);
	while(m--){
		scanf("%d %d %d",&t,&l,&r); 
		if(t) printf("%d\n",query(1,0,n - 1,l,r,0,0,0));
		else{
			scanf("%d %d %d",&a,&b,&c);
			update(1,0,n - 1,l,r,a,b,c);
		}
	}		
	return 0;
}
