#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int MAXM = 50,oo = 1000*1000*1000,MAXV = 10*MAXM;
vi X,Y;
pair<pi,pi> I[MAXM];
int n,m;
vi fr,to,cap;
vi E[MAXV];
int src,snk,N;

void addEdge(int a,int b,int c) {
	int e = fr.size();
	fr.push_back(a);
	to.push_back(b);
	cap.push_back(c);
	E[a].push_back(e);
}

void addBiEdge(int a,int b,int c) {
	addEdge(a,b,c);
	addEdge(b,a,0);
	cout << a << " " << b << " " << c << endl;
}

int iE[MAXV];

queue<int> q;
bool bfs(){
	fill(iE,iE + N,-1);
	q.push(src);
	iE[src] = -2;
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int e : E[u]) if(cap[e]){
			int v = to[e];
			if(iE[v] != -1) continue;
			iE[v] = e;
			q.push(v);
		}
	}
	return iE[snk] != -1;
}

int augment(){
	int c = oo;
	for(int u = snk;u != src;u = fr[iE[u]])
		c = min(c,cap[iE[u]]);
	for(int u = snk;u != src;u = fr[iE[u]]){
		int e = iE[u];
		cap[e] -= c;
		cap[e^1] += c;
	}
	return c;
}

int maxflow(){
	int f = 0;
	while(bfs()) f += augment();
	return f;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&n,&m);
	loop(i,m) {
		int x1,y1,x2,y2;
		scanf("%d %d",&x1,&y1);
		scanf("%d %d",&x2,&y2);
		X.push_back(x1);
		X.push_back(x2);
		Y.push_back(y1);
		Y.push_back(y2);
		I[i] = mp(pi(x1,y1),pi(x1,y2));
	}
	if(m == 0) {
		puts("0");
		return 0;
	}
	sort(all(X)); X.resize(unique(all(X)) - X.begin());
	sort(all(Y)); Y.resize(unique(all(Y)) - Y.begin());
	int cntX = n,cntY = n;
	src = 0;
	snk = cntX + cntY + 1;
	N = snk + 1;
//	for(int i = 0,x = X[0]-1;i < sz(X);i++) {
//		int cx = X[i] - x;
//		x = X[i];
//		addBiEdge(src,i+1,cx);
//	}
	for(int x = 1;x <= n;x++)
		addBiEdge(src,x,1);
	loop(i,m) {
		int x1 = I[i].first.first,y1 = I[i].first.second;
		int x2 = I[i].second.first,y2 = I[i].second.second;
//		y1 = lower_bound(all(Y),y1) - Y.begin();
//		y2 = lower_bound(all(Y),y2) - Y.begin();
//		x1 = lower_bound(all(X),x1) - X.begin();
//		x2 = lower_bound(all(X),x2) - X.begin();
//		cout << l << " " << r << " : " << s << " " << e << endl;
		for(int x = x1;x <= x2;x++)
			for(int y = y1;y <= y2;y++)
				addBiEdge(x+1,y+cntX+1,oo);
	}
//	for(int i = 0,y = Y[0]-1;i < sz(Y);i++) {
//		int cy = Y[i] - y;
//		y = Y[i];
//		addBiEdge(i+sz(X)+1,snk,cy);
//	}
	for(int y = 1;y <= n;y++)
		addBiEdge(y+cntX,snk,1);
	int tot = 0;
	for(int x = X[0]-1,i = 0;i < sz(X);i++) {
		tot += X[i] - x;

	}
	cout << tot-maxflow() << endl;
	return 0;
}
