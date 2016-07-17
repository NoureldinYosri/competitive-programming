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

char line[1 << 20];
vector<pair<ll,int> > input;
ll N; 

void parse(){
	input.clear(); N = 0;
	int L = strlen(line);
	loop(i,L){
		int j = i; ll n = 0,t = 0,f = 0;
		while(j < L && isdigit(line[j])){
			n = n * 10 + line[j] - '0';
			j++;
		} 
		if(line[j] == 'T') input.pb(mp(n,1));
		else input.pb(mp(n,0));
		i = j;
		N += n;
	}
}

void update(ll & x,ll v,int f,int p){
	x += (p == f) * v;
}

ll SQRT(ll N){
	ll s = 1,e = 1e8;
	while(s < e){
		ll m = s + ((e - s) >> 1);
		if(m*m > N) e = m;
		else s = m + 1;
	}
	return s - 1;
}

ll solve(){
	ll x = 0,u = SQRT(N),r,f = 1;
	r = u;
	for(auto p : input){
		ll n = p.xx;
		update(x,min(n,r),f,p.yy);
		if(n < r) r -= n;
		else{
			n -= r;
			f ^= 1;
			ll tmp = n/u; ll q = n%u;			
			update(x,(tmp + 1)/2 * u,f,p.yy);
			f ^= tmp & 1;
			r = u - q;
			update(x,q,f,p.yy);			
		}
	//	cerr << x << " " << f << endl;
	}
	return max(x,N - x);
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%s",line);
		parse();
		printf("%lld\n",solve());
	}
	return 0;
}

