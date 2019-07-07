#ifdef ACTIVE
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int MAXN = 5 << 10,MAXV = 2*MAXN + 2,MAXE = 6*MAXN;
int n,m,D,strength[MAXN],club[MAXN],LeavingStudent[MAXN];
int fr[MAXE],to[MAXE],cap[MAXE],edgeCnt,src,snk,iE[MAXV];
vi E[MAXV],students[MAXN];
bool doesLeave[MAXN];
int EdgeIndex[MAXV],answers[MAXN];

int addEdge(int a,int b,int c) {
	int e = edgeCnt++;
	fr[e] = a;
	to[e] = b;
	cap[e] = c;
	E[a].push_back(e);
	return e;
}
int addEdge(int a,int b,int c1,int c2) {
	int e = addEdge(a,b,c1);
	addEdge(b,a,c2);
	return e;
}

void augment(){
	int u = snk;
	while(u != src) {
		int e = iE[u];
		cap[e] ^= 1;
		cap[e^1] ^= 1;
		u = fr[e];
	}
}

bool bfs() {
	static queue<int> q;
	fill(iE,iE+snk+1,-1);
	iE[src] = -2;
	q.push(src);
	for(;!q.empty();q.pop()){
		int u = q.front();
		for(int e : E[u]) if(cap[e]) {
			int v = to[e];
			if(iE[v] != -1) continue;
			q.push(v);
			iE[v] = e;
		}
	}
	return iE[snk] != -1;
}

int maxflow() {
	int f = 0;
	while(bfs()){
		f++;
		augment();
	}
	return f;
}

void improveAnswer(int & ans) {
	do{
		if(ans == m) return;
		int & e = EdgeIndex[ans];
		if(e != -1){
			cap[e] = 1;
			e = -1;
		}
		if(maxflow()) ans++;
		else break;
	}while(1);
}

void buildNetwork(){
	src = 0;
	snk = 2*m + 2;
	for(int i = 1;i <= m;i++)
		addEdge(src,i,1,0);

	for(int c = 1;c <= m;c++) {
		for(int s : students[c]) {
			if(doesLeave[s]) continue;
			int studentStrength = strength[s];
			if(studentStrength < m)
				addEdge(c,studentStrength+m+1,1,0);
		}
	}

	for(int s = 0;s < m;s++)
		EdgeIndex[s] = addEdge(s+m+1,snk,0,0);
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",strength + i);
	for(int i = 1;i <= n;i++) {
		scanf("%d",club + i);
		students[club[i]].push_back(i);
	}
	scanf("%d",&D);
	loop(i,D) {
		scanf("%d",LeavingStudent + i);
		doesLeave[LeavingStudent[i]] = 1;
	}

	buildNetwork();
	int ans = 0;
	improveAnswer(ans);

	for(int d = D-1;d >= 0;d--) {
		answers[d] = ans;
		int s = LeavingStudent[d];
		int ss = strength[s];
		int c = club[s];
		if(ss < m) {
			addEdge(c,ss+m+1,1,0);
			improveAnswer(ans);
		}
	}
	loop(d,D) printf("%d\n",answers[d]);
	return 0;
}
#endif
