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

const int MAX = 111;
const int MAXV = MAX*3,MAXE = 1 << 20;
int n,m,p;
vi category[MAX],boy[MAX];
int use[MAX],isUsed[MAX],id[MAX];
int fr[MAXE],to[MAXE],cap[MAXE];
int head[MAXV],nxt[MAXE],edge_cnt;
int E[MAXV],src,snk;

void addedge(int a,int b,int c){
	fr[edge_cnt] = a;
	to[edge_cnt] = b;
	cap[edge_cnt] = c;
	nxt[edge_cnt] = head[a];
	head[a] = edge_cnt;
	edge_cnt++;
}

void addedge(int a,int b,int c1,int c2){
	addedge(a,b,c1);
	addedge(b,a,c2);
}


void build_graph(){
	int tot = n + m + (p + 1) + 2;
	src = 0,snk = tot - 1;
	memset(head,-1,sizeof head);
	edge_cnt = 0;
	int offset1 = 1,offset2 = 1;
	for(int i = 0;i < n;i++) addedge(src,i+1,1,0);
	offset2 += n;
	for(int i = 0;i < n;i++)
		for(int toy : boy[i]) {
			int x = toy;
			addedge(i+offset1,x + offset2,1,0);
		}
	offset1 = offset2 + m;
	swap(offset1,offset2);
	for(int i = 0;i < m;i++){
		int x = id[i];
		addedge(i + offset1,x + offset2,1,0);
	}
	offset1 = offset2 + p + 1;
	swap(offset1,offset2);
	for(int i = 0;i <= p;i++){
		addedge(i+offset1,snk,use[i],0);
	}
}

bool bfs(){
	memset(E,-1,sizeof E);
	queue<int> q;
	E[src] = -2;
	q.push(src);
	while(!q.empty()){
		int u = q.front(); q.pop();
		if(u == snk) return 1;
		for(int e = head[u];e != -1;e = nxt[e]){
			int v = to[e];
			if(cap[e] && E[v] == -1) {
				E[v] = e;
				q.push(v);
			}
		}
	}
	return 0;
}


void augment(){
	int cur = snk;
	while(E[cur] >= 0) {
		int e = E[cur];
		cap[e] --;
		cap[e ^ 1]++;
		cur = fr[e];
	}
}
int maxflow(){
	int f = 0;
	while(bfs()){
		f++;
		augment();
	}
	return f;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	bool first = 1;
	while(scanf("%d %d %d",&n,&m,&p) == 3){
		memset(isUsed,0,sizeof isUsed);
		memset(id,0,sizeof id);
		loop(i,n){
			boy[i].clear();
			int cnt; scanf("%d",&cnt);
			boy[i].resize(cnt);
			loop(j,cnt) {
				scanf("%d",&boy[i][j]);
				boy[i][j]--;
			}
		}
		range(i,1,p) {
			category[i].clear();
			int cnt; scanf("%d",&cnt);
			category[i].resize(cnt);
			loop(j,cnt) {
				scanf("%d",&category[i][j]);
				category[i][j]--;
				assert(isUsed[category[i][j]] == 0);
				id[category[i][j]] = i;
				isUsed[category[i][j]] = 1;
			}
			scanf("%d",use + i);
		}
		use[0] = MAX;
		build_graph();
		printf("%d\n",maxflow());
	}
	return 0;
}
