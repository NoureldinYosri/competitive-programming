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

const int MAX = 5 << 10;
vi G[MAX];
int n,m;
int E[MAX][2];

int main(){
	scanf("%d %d",&n,&m);
	loop(i,m){
		scanf("%d %d",&E[i][0],&E[i][1]);
		G[E[i][0]].pb(E[i][1]);
		G[E[i][1]].pb(E[i][0]);
	}	
	range(i,1,n) sort(all(G[i]));
	int ans = INT_MAX;	
	loop(i,m){
		int a = E[i][0],b = E[i][1];
		int sum = sz(G[a]) + sz(G[b]);
		for(int v : G[a])
			if(binary_search(all(G[b]),v)){
				ans = min(ans,sum + sz(G[v]) - 6);
			}		
	}
	if(ans == INT_MAX) ans = -1;
	cout << ans << endl;
	return 0;
}
