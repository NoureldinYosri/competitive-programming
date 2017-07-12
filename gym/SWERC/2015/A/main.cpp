#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 5000;
vi G[MAX],rG[MAX];
int A,B,E,P;
int pred[MAX],succ[MAX];
int siz[MAX];


int dfs(int u,int *siz,vi *G){
	if(siz[u] != -1) return 0;
	siz[u] = 1;
	for(int v : G[u])
		siz[u] += dfs(v,siz,G);
	return siz[u];
}

int main(){
	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	scanf("%d %d %d %d",&A,&B,&E,&P);
	while(P--){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		rG[b].pb(a);
	}
	loop(i,E){
		memset(siz,-1,sizeof siz);
		succ[i] = E - dfs(i,siz,G);
		memset(siz,-1,sizeof siz);
		pred[i] = dfs(i,siz,rG) - 1;
	}
	sort(succ,succ + E);
	sort(pred,pred + E);
	int x,y,z;
	x = lower_bound(succ,succ + E,A) - succ;
	y = lower_bound(succ,succ + E,B) - succ;
	z = pred + E - lower_bound(pred,pred + E,B);
	cout << x << endl;
	cout << y << endl;
	cout << z << endl;
	return 0;
}
