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
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 100'000 + 10;
int ctr[MAX][20][2];
int A[MAX],n;
vi G[MAX];
ll ans = 0;


void dfs(int u,int p){
	for(int i = 0;i < 20;i++)
		if(A[u] & (1 << i)) ctr[u][i][1]++;
		else ctr[u][i][0]++;	
	for(int v : G[u]) if(v != p) {
		dfs(v,u);
		for(int i = 0;i < 20;i++){
			ll cnt = ctr[u][i][1]*1LL*ctr[v][i][0] + ctr[u][i][0]*1LL*ctr[v][i][1];
			ans += cnt * (1LL << i);
			int t = 0;
			if(A[u] & (1 << i)) t = 1;
			loop(j,2) ctr[u][i][j] += ctr[v][i][j^t];
		}
	}
}


int main(){
	scanf("%d",&n);
	range(i,1,n) scanf("%d",A + i),ans += A[i];
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1,0);
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
