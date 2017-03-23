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

vi G[30];
int deg[30],n;
int X[30],Y[30];

void dfs(int u,int p,int dir,ll sx,ll ex,ll sy,ll ey){
	X[u] = (sx + ex) >> 1;
	Y[u] = (sy + ey) >> 1;

}


int main(){
	scanf("%d",&n);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		a--,b--;
		G[a].pb(b);
		G[b].pb(a);
		deg[a]++;
		deg[b]++;
	}
	loop(i,n) if(deg[i] > 4){
		puts("NO");
		return 0;
	}
	int dir = 0;
	int MX = 1 << 30;
	dfs(0,-1,-1,-MX,MX,-MX,MX);		

	puts("YES");
	loop(i,n) printf("%d %d",X[i],Y[i]);
	
	return 0;
}
