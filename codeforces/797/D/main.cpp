#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
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

using namespace std;



typedef long long llong;
typedef pair<int, int> int2;
typedef pair<llong, llong> llong2;
#define foreach(v,c) for (typeof((c).begin()) v = (c).begin(); v != (c).end(); ++v)
#define rep(i,n) for (int i = 0; i < (n); ++i)

static const int maxn = 2*5000 + 2;
static const int maxm = 5000*5000 + 2*5000;
int graph[maxn], queue[maxn], pre[maxn], con[maxn];
bool inq[maxn];
ll dis[maxn];
struct edge {
    int node, next; int flow; ll value;
} edges[maxm<<1];

struct MinCostFlow {
  typedef int Captype;
  typedef ll Valtype;
  static const Captype flowlimit = 100000;
  int  n, m, source, target, top;
  Captype maxflow;
  Valtype mincost;
  MinCostFlow() {
	  memset(graph, -1, sizeof(graph));
	  top=0;
  }
  inline int inverse(int x) { return 1 + ((x>>1)<<2)-x; }
  inline void addedge(int u, int v, Captype c, Valtype w) {
    if (c == 0) return;
    //cout << u << " -> " << v << ": " << c << "/" << w << endl;
    edges[top].value = w; edges[top].flow = c; edges[top].node = v;
    edges[top].next = graph[u]; graph[u] = top++;
    edges[top].value = -w; edges[top].flow = 0; edges[top].node = u;
    edges[top].next = graph[v]; graph[v] = top++;
  }
  bool SPFA() {
    int point, nod, now, head = 0, tail = 1;
    memset(pre, -1, sizeof pre);
    memset(inq, 0, sizeof inq);
    memset(dis, 0x7f, sizeof dis);
    dis[source] = 0; queue[0] = source; pre[source] = source; inq[source] = true;
    while (head != tail) {
      now = queue[head++]; point = graph[now]; inq[now] = false; head %= maxn;
      while (point != -1) {
        nod = edges[point].node;
        if (edges[point].flow > 0 && dis[nod]>dis[now]+edges[point].value) {
          dis[nod] = dis[now] + edges[point].value;
          pre[nod] = now;
          con[nod] = point;
          if (!inq[nod]) {
            inq[nod] = true;
            queue[tail++] = nod;
            tail %= maxn;
          }
        }
        point = edges[point].next;
      }
    }
    return pre[target]!=-1;
  }
  void extend() {
    Captype w = flowlimit;
    for (int u = target; pre[u] != u; u = pre[u])
      w = min(w, edges[con[u]].flow);
    maxflow += w;
    mincost += dis[target]*w;
    for (int u = target; pre[u] != u; u = pre[u]) {
      edges[con[u]].flow -= w;
      edges[inverse(con[u])].flow += w;
    }
  }
  void mincostflow() {
    maxflow = 0; mincost = 0;
    while (SPFA()) extend();
  }
};




const int MAX = 5000;
int n,m;
int X[MAX],P[MAX],C[MAX];


int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",X + i);
	loop(i,m) scanf("%d %d",P + i,C + i);
	MinCostFlow MCMF ;
	loop(i,n) MCMF.addedge(0,i+1,5010,0);
	loop(i,n) loop(j,m) MCMF.addedge(i+1,n+j+1,5010,abs(X[i] - P[j]));
	loop(i,m) MCMF.addedge(n+i+1,n+m+1,C[i],0);
	MCMF.mincostflow();
	cerr << MCMF.maxflow << endl;
	if(MCMF.maxflow != n) puts("-1");
	else cout << MCMF.mincost << endl;
	return 0;
}
