//WA
#pragma GCC optimize ("O3")
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
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
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

const int MAXN = 400;
const double oo = 1e15;
vi G[MAXN],H,who[MAXN];
int X[MAXN],Y[MAXN],Z[MAXN],K[MAXN];
int n,m;
double euclidean_dist[MAXN][MAXN];
pair<pi,double> component_dist[MAXN][MAXN][4];
double dist[MAXN][5];
int in[MAXN][5];
int cost[MAXN];
int id[MAXN];
bool usable[MAXN];
vector<pair<double,pi> > aux[MAXN][MAXN];

void flood_fill(int u,int idx){
	who[idx].pb(u);
	id[u] = idx;
	cost[idx] += K[u];
	for(int v : G[u]) if(id[v] == -1 && usable[v]) flood_fill(v,idx);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif

	H.clear();
	for(int t = 1;scanf("%d %d",&n,&m) == 2;t++){
		H.clear();
		loop(i,n) {
			scanf("%d %d %d %d",X + i,Y + i,Z + i,K + i);
			H.pb(Z[i]);
			G[i].clear();
		}
		loop(i,m) {
			int a,b; scanf("%d %d",&a,&b);
			a--,b--;
			G[a].pb(b);
			G[b].pb(a);
		}
		loop(i,n) loop(j,n) {
			if(K[i] && K[j]) euclidean_dist[i][j] = hypot(hypot(X[i] - X[j],Y[i] - Y[j]),Z[i] - Z[j]);
			else euclidean_dist[i][j] = oo;
		}
		sort(all(H));
		H.resize(unique(all(H)) - H.begin());
		int mx = max(Z[0],Z[n - 1]);
		double ans = oo;
		for(int h : H) if(h >= mx){
			int idx = 0,src = -1,snk = -1;
			memset(id,-1,sizeof id);
			memset(cost,0,sizeof cost);
			loop(i,n) usable[i] = Z[i] <= h;
			loop(i,n) if(id[i] == -1 && usable[i]) {
				who[idx].clear();
				flood_fill(i,idx);
				if(id[0] == idx) src = idx;
				if(id[n-1] == idx) snk = idx;
				idx++;
			}
			loop(i,idx) loop(j,idx) aux[i][j].clear();
			loop(i,n) loop(j,n) if(id[i] != id[j] && id[i] != -1 && id[j] != -1 && K[i] && K[j]) {
				aux[i][j].pb(mp(euclidean_dist[i][j],mp(i,j)));
			}
			loop(i,idx) loop(j,idx) {
				sort(all(aux[i][j]));
				vector<pair<double,pi> > tmp;
				map<int,int> to,fr;
				for(auto e : aux[i][j]){
					int f = e.yy.xx,t = e.yy.yy;
					if(fr[f] == 2 || to[t] == 2) continue;
					fr[f]++,to[t]++;
					tmp.pb(e);
				}
				aux[i][j].swap(tmp);
			}
			if(!cost[src] || !cost[snk]) continue;
			fill(&dist[0][0],&dist[idx][0],oo);
			fill(&dist[0][0],&dist[1][0],(cost[0] - 1)/2.0);
			memset(in,-1,sizeof in);
			loop(ctr,4*idx){
				bool change = 0;
				loop(i,idx) loop(d,4) if(dist[i][d] < oo){
					loop(j,idx) {
						for(auto e : aux[i][j]) if(e.yy.xx != in[i][d] || K[e.yy.xx] > 1){
							dist[j][4] = dist[i][d] + e.xx + (cost[j] - 1)/2.0;
							in[j][4] = e.yy.yy;
							bool found = 0;
							loop(cur,4) {
								found = (in[j][cur] == e.yy.yy) && abs(dist[j][cur] - dist[j][4]) < 1e-9;
								if(found) break;
							}
							if(found) continue;
						//	cerr << dist[j][4] << endl;
							int cur = 4;
							while(cur && dist[j][cur - 1] > dist[j][cur]) {
								swap(dist[j][cur - 1],dist[j][cur]);
								swap(in[j][cur - 1],in[j][cur]);
								cur--;
								change = 1;
							}
						}
					}
				}
				if(!change) break;
				loop(i,idx) {prArr(dist[i],4,double);}
			}
			double tmp = dist[snk][0];
			ans = min(ans,tmp);
//			cerr << h << " -> " << tmp << endl;
		}
		printf("Case %d: ",t);
		if(ans >= oo) puts("impossible");
		else printf("%.3f\n",ans);
	}
	return 0;
}
