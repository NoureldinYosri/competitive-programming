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

const int MAX = 4 << 10;
int val[MAX],n,N,head[MAX],snk;
vi fr,to,nxt,cost,C,f;
int E[MAX],ans[MAX];
ll dist[MAX];
const ll oo = 1LL << 60;

void add_edge(int a,int b,int c,int d = 1){
	int e = sz(to);
	fr.pb(a);	
	to.pb(b);
	nxt.pb(head[a]);
	cost.pb(c);
	C.pb(d);
	f.pb(0);
	head[a] = e;
	if(d) add_edge(b,a,-c,0);
}


bool BellmanFord(){
	fill(dist,dist + MAX,oo);
	dist[0] = 0;
	int E = sz(to);
	loop(i,N-1) {
		bool done = 1;
		loop(e,E){
			if(C[e]){
				int a = fr[e],b = to[e],c = cost[e];
				if(dist[a] + c < dist[b]){
					dist[b] = dist[a] + c;
					::E[b] = e;
					done = 0;
				}
			}
		}
		if(done) break;
	}
	return dist[snk] != oo;
}

void augment(){
	int u = snk;
	while(u){
		int e = E[u];
		f[e] = 1;
		C[e] = 0;
		C[e ^ 1] = 1;
		f[e ^ 1] = 0;
		u = fr[e];
	}
}

ll MCMF(){
	ll cost = 0;
	while(BellmanFord()){
		cost += dist[snk];
		augment();	
	}
	return cost;
}

int main(){
	freopen("beloved.in","r",stdin);
	freopen("beloved.out","w",stdout);
	memset(head,-1,sizeof head);
	scanf("%d",&n);
	range(i,1,n) {
		scanf("%d",val + i);
		val[i] = val[i]*val[i];
		add_edge(0,i,-val[i]);		
	}
	int mx = 0;
	range(i,1,n){
		int k; scanf("%d",&k);
		while(k--){
			int x; scanf("%d",&x);
			mx = max(mx,x);
			x += n;
			add_edge(i,x,0);
		}
	}
	int aux = mx;
	range(i,1,n){
		aux++;
		add_edge(i,aux + n,val[i]);
	}
	range(i,1,aux) add_edge(i+n,n+aux+1,0);
	snk = n + aux + 1;
	N = n + aux + 2;
	cerr << -MCMF() << endl;
	int E = sz(to);
	loop(e,E) if(f[e] && 1 <= fr[e] && fr[e] <= n){
		int a = fr[e],b = to[e];
		if(n < b && b-n <= mx) ans[a] = b - n;
	}		
	range(i,1,n) printf("%d%c",ans[i]," \n"[i==n]);
	return 0;
}
