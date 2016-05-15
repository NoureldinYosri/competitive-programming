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

int ans = 0;
vi G[1 << 20];
int L[1 << 20];

int bfs(int s){
	ans = 0;
	L[1] = -1;	
	L[s] = 1;
	queue<int> q;
	q.push(s);
	while(!q.empty()){
		int u = q.front(); q.pop();
		if(sz(G[u]) == 1){
			if(ans < L[u]) ans = L[u];
			else ans++;
		}
		for(int v : G[u]){
			if(!L[v]) {
				q.push(v);
				L[v] = L[u] + 1;
			}
		}
	}
	return ans;
}

int main(){
	int n,a,b;
	scanf("%d",&n);
	loop(i,n - 1) {
		scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	int r = 0;
	for(int u : G[1]) r = max(r,bfs(u));
	cout << r << endl;
	return 0;
}
