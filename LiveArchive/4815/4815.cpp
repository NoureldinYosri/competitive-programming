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
int n,m;
int E[MAX][2],P[MAX << 1],W[MAX << 1];
int V[MAX << 1];
int deg[MAX << 1];

int get(int a){
	return P[a] = (a == P[a]) ? a : get(P[a]);
}

void join(int a,int b){
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	P[b] = a;
}

int main(){
	while(scanf("%d %d",&n,&m) == 2 && !(n == 0 && m == 0)){
		int k = 0;
		loop(i,m) loop(j,2) scanf("%d",&E[i][j]),V[k++] = E[i][j];
		sort(V,V + k);
		k = unique(V,V + k) - V;
		loop(i,k) W[i] = 1,P[i] = i,deg[i] = 0;
		bool c = 0;
		loop(i,m){
			int a = E[i][0],b = E[i][1];
			a = lower_bound(V,V + k,a) - V;
			b = lower_bound(V,V + k,b) - V;
			deg[b]++;
			a = get(a);
			b = get(b);
			if(deg[b] > 2) c = 1;
			if(a == b) c |= W[a] != n;
			else join(a,b);	
		}
		puts(c ? "N" : "Y");
	}		
	return 0;
}
