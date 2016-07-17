#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

const int MAX = 5e4 + 1e3;
vi G[MAX];
int n,r1,r2;
int P[MAX];

void dfs(int u,int p){
	P[u] = p;
	for(int v : G[u]) if(v != p) dfs(v,u);
}

int main(){
	scanf("%d %d %d",&n,&r1,&r2);
	int j = 1;	
	loop(i,n - 1) {
		int a;
		scanf("%d",&a);
		if(j == r1) j++;
		G[a].pb(j);
		G[j].pb(a);
		j++;
	}
	dfs(r2,0);
	loop(i,n) if(i + 1 != r2) printf("%d ",P[i + 1]);		
	return 0;
}
