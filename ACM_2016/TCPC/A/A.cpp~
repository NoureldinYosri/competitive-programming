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

int n,m;
vi G[1024];
deque<int> val[1024],team[1024];
int color[1024],P[1024],V[1024];

void init(){
	fill(P,P + 1024,0);
	queue<pi> q;
	q.push(mp(1,0));
	while(!q.empty()){
		pi U = q.front(); q.pop();
		int u = U.xx,d = U.yy + 1;		
		for(int v : G[u]){
			if(v == P[u]) continue;
			P[v] = u;
			team[color[v]].pb(d);
			q.push(mp(v,d));
		}	
	}
}

int solve(){
	int ctr = 0;
	init();
	for(int c = 1;c < 1024;c++){
		sort(all(val[c]));	
		while(!val[c].empty() && !team[c].empty()){
			if(val[c].front() < team[c].front()) val[c].pop_front();
			else{
				ctr ++;
				val[c].pop_front();
				team[c].pop_front();
			}
		}
	}
	return ctr;
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		loop(i,1024) G[i].clear(),team[i].clear(),val[i].clear();
		scanf("%d %d",&n,&m);
		loop(i,n - 1){
			int a,b;
			scanf("%d %d",&a,&b);
			G[a].pb(b);
			G[b].pb(a);
		}
		loop(i,n - 1) scanf("%d",&color[i + 2]);
		loop(i,m) scanf("%d",V + i);
		loop(i,m){
			int a;
			scanf("%d",&a);
			val[V[i]].pb(a);
		}
		printf("%d\n",solve());
	}
	return 0;
}
