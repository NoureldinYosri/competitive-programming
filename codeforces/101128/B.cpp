#ifdef ACITVE
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

const int alpha = 26;
const int N = 100;
char S[N][5];
int who[N],res[N];
int n;

const int MAX = 4*alpha;

vi G[MAX],rG[MAX];


int NOT(int x) {
	return x ^ 1;
}


int getID(int p,char c) {
	c -= 'A';
	return 2*alpha*p + 2*c;
}

void clear(){
	int m = 4*alpha;
	loop(i,m) G[i].clear(),rG[i].clear();
}

void addedge(int a,int b) {
	G[a].push_back(b);
	rG[b].push_back(a);
//	cerr << a << " " << b << endl;
}

void addOrEdge(int a,int b) {
	addedge(NOT(a),b);
	addedge(NOT(b),a);
}

void addXorEdge(int a,int b) {
	addOrEdge(a,b);
	addOrEdge(NOT(a),NOT(b));
}

void setTrue(int a) {
	addedge(NOT(a),a);
}

void setFalse(int a){
	addedge(a,NOT(a));
}

void build(char A,char B,char C) {
	for(char c = 'A';c < 'A' + alpha;c++){
		if(c == A || c == B || c == C) {
			setFalse(getID(0,c));
			setFalse(getID(1,c));
		}
		else {
			addXorEdge(getID(0,c),getID(1,c));
		}
	}
	loop(i,n){
		int p = who[i] - 1;
		char a = S[i][0],b = S[i][1];
		if(res[i] == 0) {
			setFalse(getID(p,a));
			setFalse(getID(p,b));
		}
		else if(res[i] == 1) {
			addXorEdge(getID(p,a),getID(p,b));
		}
		else {
			setTrue(getID(p,a));
			setTrue(getID(p,b));
		}
	}
}

vi ord;
bool vis[MAX];

void dfs(int u,vi *G){
	if(vis[u]) return;
	vis[u] = 1;
	for(int v : G[u])
		dfs(v,G);
	ord.push_back(u);
}

int SCC[MAX];

void dfs(int u,vi *G,int id) {
	if(vis[u]) return;
	SCC[u] = id;
	vis[u] = 1;
	for(int v : G[u])
		dfs(v,G,id);
}

bool valid(){
	ord.clear();
	int m = 4*alpha;
	loop(i,m) vis[i] = 0;
	loop(i,m) dfs(i,rG);
	reverse(all(ord));
//	print(ord,int);
	loop(i,m) vis[i] = 0;
	int z = 0;
	for(int u : ord) if(!vis[u]) {
		dfs(u,G,z);
//		prArr(SCC,m,int);
		z++;
	}
//	prArr(SCC,m,int);
	for(int i = 0;i < m;i += 2)
		if(SCC[i] == SCC[i+1])
			return 0;
	return 1;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%s %d %d",S[i],who + i,res + i);

	int ans = 0;

	for(char a = 'A';a < 'A' + alpha;a++)
		for(char b = 'A';b < a;b++)
			for(char c = 'A';c < b;c++){
				build(a,b,c);
				ans += valid();
				clear();
			}
	cout << ans << endl;
	return 0;
}
#endif
