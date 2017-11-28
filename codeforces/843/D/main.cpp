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

const int MAXN = 100*1000 + 10,MAXE = MAXN,MAXQ = 2000,MAXQSIZ = 1 << 20;
const ll oo = 1LL << 60;

vi E[MAXE];
int fr[MAXE],to[MAXE],weight[MAXE];
vi to_modify[MAXQ];
int type[MAXQ],n,m,q;
ll dist[MAXN];
int inque[MAXN],que[MAXQSIZ],FRONT,END;



inline void SPFA(){
	while(FRONT < END) {
		int u = que[FRONT%MAXQSIZ];
		FRONT++;
		inque[u] = 0;
		for(int e : E[u]){
			int v = to[e];
			if(dist[u] + weight[e] < dist[v]){
				dist[v] = dist[u] + weight[e];
				if(!inque[v]) {
					inque[v] = 1;
					que[END%MAXQSIZ] = v;
					END++;
				}
			}
		}
	}
	for(int i = 1;i <= n;i++) assert(inque[i] == 0);
	FRONT = END = 0;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&n,&m,&q);
	loop(e,m){
		scanf("%d %d %d",fr + e,to + e,weight + e);
		E[fr[e]].pb(e);
	}
	loop(i,q){
		scanf("%d",type + i);
		if(type[i] == 1) {
			int x; scanf("%d",&x);
			to_modify[i].pb(x);
		}
		else {
			int c; scanf("%d",&c);
			to_modify[i].resize(c);
			loop(j,c) {
				scanf("%d",&to_modify[i][j]);
				to_modify[i][j]--;
				weight[to_modify[i][j]]++;
			}
		}
	}
	fill(dist,dist + MAXN,oo);
	dist[1] = 0;
	que[END++] = 1;
	inque[1] = 1;
	SPFA();
	vl ans;
	ans.reserve(q);
	for(int i = q-1;i >= 0;i--){
		if(type[i] == 1) {
			int u = to_modify[i].back();
			ll val = dist[u];
			if(val >= oo) val = -1;
			ans.pb(val);
		}
		else {
			for(int e : to_modify[i]){
				weight[e]--;
				int u = fr[e],v = to[e];
				if(dist[u] + weight[e] < dist[v]){
					dist[v] = dist[u] + weight[e];
					if(!inque[v]) {
						inque[v] = 1;
						que[END%MAXQSIZ] = v;
						END++;
					}
				}
			}
			SPFA();
		}
	}
	reverse(all(ans));
	for(ll x : ans) printf("%lld\n",x);
	return 0;
}
