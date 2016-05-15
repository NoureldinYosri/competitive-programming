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

int BIT[301],m,n,k;
ll G[301][301],A,B;
ll values[301],tmp,ans = 0;

void read();
inline void update(int);
inline int query(int);
inline int f(ll);

int main(){
	read();
	loop(x2,m)
		loop(x1,x2 + 1){
			loop(y,n){
				values[y] = G[x2][y];
				if(x1) values[y] -= G[x1 - 1][y];	
			}
			values[n] = 0;
			sort(values,values + n + 1);
			k = unique(values,values + n + 1) - values;
			fill(BIT,BIT + 300,0);			
			update(lower_bound(values,values + k,0) - values + 1);			
			loop(y,n){
				tmp = G[x2][y];
				if(x1) tmp -= G[x1 - 1][y];
				ans += f(tmp - A) - f(tmp - B - 1);
				update(lower_bound(values,values + k,tmp) - values + 1);
			}
		}
	printf("%lld\n",ans);		
	return 0;
}

void read(){
	scanf("%d %d",&m,&n);
	loop(i,m) loop(j,n){
		scanf("%lld",&G[i][j]);
		if(i) G[i][j] += G[i - 1][j];
		if(j) G[i][j] += G[i][j - 1];
		if(i && j) G[i][j] -= G[i - 1][j - 1];
	}
	scanf("%lld %lld",&A,&B);
}

inline void update(int p){
	for(;p <= 300;p += LSOne(p)) BIT[p]++;
}

inline int query(int p){
	int ret = 0;
	for(;p;p -= LSOne(p)) ret += BIT[p];
	return ret;
}

inline int f(ll v){
	ll* x = lower_bound(values,values + k,v);
	if(*x == v) return query(x - values + 1);
	else return query(x - values);
}
