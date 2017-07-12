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


#define rep(i,X,n) for( int (i) = (X) ; (i)<(n) ; (i) ++)
inline int gInd(int x){
	return (x)%2?(x)-1:(x)+1;
}
int n,m;
struct Edge
{
	int fr,to,cost,flow;
	Edge(){fr=to=cost=flow=-1;}
	Edge(int a,int b,int c,int d)
	:fr(a),to(b),cost(c),flow(d)
	{
	}
};
struct MinCostMaxFlow
{
	vector<Edge> es;
	int flow[300];
	int cost[300];
	int p[300];
	void AddEdge(int fr,int to,int co,int fl)
	{
		es.pb(Edge(fr,to,co,fl));
		es.pb(Edge(to,fr,-co,0));
		m += 2;
	}
	MinCostMaxFlow()
	{
		clear();
	}
	int getPath(int src,int sink)
	{
		memset(flow,0,sizeof(flow));
		fill(cost,cost+n+m+2,100000000);
		cost[src]=0;
		flow[src]=100000000;
		memset(p,-1,sizeof(p));
		rep(i,0,n+m+2)
		{
		bool fl =0;
		rep(j,0,es.size())
		{
		if( cost[es[j].to] >
		cost[es[j].fr]+es[j].cost && es[j].flow!=0)
		{
		cost[es[j].to] =
		cost[es[j].fr]+es[j].cost;
		flow[es[j].to] =
		min(flow[es[j].fr],es[j].flow);
		p[es[j].to] = j;
		fl=1;
		}
		}
		if(!fl)
		break;
		}
	return flow[sink];
	}
	pair<int,int> MCMF(int src,int sink)
	{
	if(src == sink)
	return make_pair(100000000,0);
	int fl,totc=0,totf=0,cur;
	while(1)
	{
	fl = getPath(src,sink);
	if(p[sink]==-1)
	break;
	cur = sink;
	while(p[cur]!=-1)
	{
	es[p[cur]].flow-=fl;
	es[gInd(p[cur])].flow+=fl;
	totc +=fl*es[p[cur]].cost;
	cur = es[p[cur]].fr;
	}
	totf += fl;
	}
	return make_pair(totf,totc);
	}
	void clear()
	{
	es.clear();
	memset(flow,0,sizeof(flow));
	memset(cost,0,sizeof(cost));
	memset(p,-1,sizeof(p));
	}
};








int main(){
	freopen("in.in","r",stdin);
	int N,K,A[80],C[80];
	cin >> N >> K;
	loop(i,N) cin >> A[i],A[i]--;
	loop(i,N) cin >> C[i];

	n = 2*N + 3;
	MinCostMaxFlow MCMF;
	int src = 0,psrc = 2*n+1,snk = 2*N+2;
	const int oo = 1 << 28;
	MCMF.AddEdge(src,psrc,0,K);
	loop(i,N) MCMF.AddEdge(psrc,2*i+1,C[A[i]],1);
	loop(i,N) MCMF.AddEdge(2*i+1,2*i+2,-oo,1);
	loop(j,N) loop(i,j) MCMF.AddEdge(2*i+2,2*j+1,(A[i] != A[j])*C[A[j]],1);
	loop(i,N) MCMF.AddEdge(2*i+2,snk,0,1);
	auto ans = MCMF.MCMF(src,snk);
	while(ans.yy < 0) ans.yy += oo;
	prp(ans); cerr << endl;
	return 0;
}
