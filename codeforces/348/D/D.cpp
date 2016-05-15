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
int V[MAX],n,z;
pair<pi,pi> X[MAX];
vi T[MAX];
vi BIT[MAX];

int main(){
	scanf("%d",&n);
	loop(i,n){
		scanf("%d",&X[i].yy.xx);
		scanf("%d",&X[i].xx.xx);
		scanf("%d",&X[i].yy.yy);
		X[i].xx.yy = i;
		V[i] = X[i].yy.yy;
	}			
	sort(V,V + n);
	z = unique(V,V + n) - V;
	loop(i,n){
		int & x = X[i].yy.yy;
		x = lower_bound(V,V + z,x) - V + 1;
		T[x].pb(X[i].xx.xx);
	}
	loop(i,z) {
		sort(all(T[i + 1]));
		BIT[i + 1].resize(sz(T[i + 1]) + 1);
	}
	loop(i,n){
		int idx = X[i].xx.yy,type = X[i].yy.xx,x = X[i].yy.yy,t = X[i].xx.xx;	
		t = lower_bound(all(T[x]),t) - T[x].begin() + 1;
		if(type == 1) {
			for(;t < sz(BIT[x]);t += LSOne(t)) BIT[x][t]++;
		}
		else if(type == 2) {
			for(;t < sz(BIT[x]);t += LSOne(t)) BIT[x][t]--;
		}
		else {
			int ans = 0;
			for(;t;t -= LSOne(t)) ans += BIT[x][t];		
			printf("%d\n",ans);
		}
	}
	return 0;
}

