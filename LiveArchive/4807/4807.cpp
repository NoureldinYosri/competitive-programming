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

#define f(a,b,c,d) (a*d - b*c)


struct circle{
	int i,j,k;
	ll h1,h2;
	ll k1,k2;
	ll r1,r2;
public:
	circle(){}
	circle(int i,int j,int k):i(i),j(j),k(k){
		ll a12 = P[i].xx*P[i].xx - P[j].xx*P[j].xx;
		ll a13 = P[i].xx*P[i].xx - P[k].xx*P[k].xx;
		ll b12 = 2*(P[i].xx - P[j].xx);
		ll b13 = 2*(P[i].xx - P[k].xx);
		ll c12 = P[i].yy*P[i].xx - P[j].yy*P[j].yy;
		ll c13 = P[i].yy*P[i].xx - P[j].yy*P[j].yy;
		ll d12 = 2*(P[i].yy - P[j].yy);
		ll d13 = 2*(P[i].yy - P[k].yy);
		ll e12 = a12 + c12;
		ll e13 = a13 + c13;
		h1 = b13*e12 - b12*e13;
		h2 = b13*d12 - b12*d13;
		k1 = d13*e12 - d12*e13;
		k2 = d13*b12 - d12*b13;
			
	}
	bool operator < (const circle & o) const {
		if(f(h1,h2,o.h1,o.h2) != 0) return f(h1,h2,o.h1,o.h2);
		if(f(k1,k2,o.k1,o.k2) != 0) return f(h1,h2,o.h1,o.h2);
		if(f(r1,r2,o.r1,o.r2) != 0) return f(h1,h2,o.h1,o.h2);
		return 0;
	}
	bool operator == (const circle & o) const {
		return !(*this < o || o < *this);
	}
};
pi P[100];
int n;
circle C[1000000];

ll ccw(int i,int j,int k){
	pl u = mp(P[i].xx - P[j].xx + 0LL,P[i].yy - P[j].yy + 0LL);
	pl v = mp(P[k].xx - P[j].xx + 0LL,P[k].yy - P[j].yy + 0LL);
	return u.xx*v.yy - u.yy*v.xx;
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",&P[i].xx,&P[i].yy);
	int ctr = 0;	
	loop(k,n) loop(j,k) loop(i,j) {
		if(!ccw(i,j,k)) continue;
		C[ctr++] = circle(i,j,k);
	}
	sort(C,C + ctr);
	int ans = 0;	
	loop(i,ctr){
		int j = i; vi p;
		while(j < ctr && C[i] == C[j]){
			p.pb(C[j].i);
			p.pb(C[j].j);
			p.pb(C[j].k);
		}
		sort(all(p));
		p.resize(unique(all(p)) - p.begin());
		ans = max(ans,(int)sz(p));
	}
	printf("%d\n",ans);
	return 0;
}
