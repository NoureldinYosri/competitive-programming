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

const ll mod = 1e9 + 7;

ll mul(ll a,ll b){
	a %= mod; b%=mod;
	return (a*b)%mod;
}

struct vertex{
	ll S[6];
public:
	vertex(){S[0] = 1; fill(S + 1,S + 6,0);}
	vertex(ll p,ll v){
		S[0] = v%mod;
		loop(i,5) S[i + 1] = mul(S[i],p + 1);
	}
	vertex operator + (const vertex & o){
		vertex ret;
		loop(i,6) ret.S[i] = (S[i] + o.S[i])%mod;
		return ret;
	}
};

ostream & operator << (ostream & st,const vertex & v){
	st << "(";
	loop(i,6) {
		if(i) st << " ,";
		st << v.S[i];
	}
	st << " )";
	return st;
}

const int MAX = 1e5 + 1e3;
vertex ST[MAX << 2];
ll A[MAX],LAZY[MAX << 2],C[6][6];
int n,m;
ll SUMPOW[6][MAX];

vertex build(int node,int s,int e){
	LAZY[node] = -1;	
	if(s == e) return ST[node] = vertex(s+0LL,A[s]);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	return ST[node] = build(left,s,m) + build(right,m + 1,e);
}

void update(int node,int s,int e,ll v){
	v %= mod;
	LAZY[node] = v;
	loop(i,6) {
		ll tmp = SUMPOW[i][e] - SUMPOW[i][s - 1];
		if(tmp < 0) tmp += mod;
		ST[node].S[i] = mul(v,tmp);
	}	
}

void forward(int node,int s,int e){
	if(LAZY[node] == -1) return;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	update(left,s,m,LAZY[node]);
	update(right,m + 1,e,LAZY[node]);
	LAZY[node] = -1;
}

void update(int node,int s,int e,int l,int r,ll v){
	if(l <= s && e <= r) return update(node,s,e,v);
	forward(node,s,e);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) update(left,s,m,l,r,v);
	else if(m < l) update(right,m + 1,e,l,r,v);
	else update(left,s,m,l,m,v),update(right,m + 1,e,m + 1,r,v);
	ST[node] = ST[left] + ST[right];
}

vertex query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST[node];
	forward(node,s,e);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r);
	else if(m < l) return query(right,m + 1,e,l,r);
	else return query(left,s,m,l,m) + query(right,m + 1,e,m + 1,r);
}

void init(){
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%lld",A + i + 1);
	build(1,1,n) ;
	loop(i,n + 1){
		ll j = 1;
		loop(p,6) {
			SUMPOW[p][i] = j;
			if(i) {
				SUMPOW[p][i] += SUMPOW[p][i - 1];
				if(SUMPOW[p][i] >= mod) SUMPOW[p][i] -= mod;
			}
			j *= i + 1; j %= mod;
		}
	}	
	loop(i,6){
		C[i][0] = 1;
		range(j,1,i) C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	}
}

int main(){
	init();	
	char s[3]; int l,r,x;	
	while(m--){
		scanf("%s %d %d %d",s,&l,&r,&x);
		if(s[0] == '=') update(1,1,n,l,r,x);
		else {
			vertex Q = query(1,1,n,l,r); 
			ll ans = 0,q = 1;
			loop(i,x + 1){
				ans += mul(C[x][i],mul(q,Q.S[x - i]));
				ans %= mod;
				q *= -l;
				q %= mod;
				if(q < 0) q += mod;
			}
			printf("%lld\n",ans);
		}
	}	
	return 0;
}
