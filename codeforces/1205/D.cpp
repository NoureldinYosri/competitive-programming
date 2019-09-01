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

const int MAX = 1 << 10;
vi E[MAX];
int fr[MAX],to[MAX],W[MAX],cnt[MAX];
int siz[MAX],lim;
bool done[MAX*MAX];
int n;

int getNext(){
	static int v = 1;
	while(v <= lim && done[v]) v++;
	return v;
}


void save(int x) {
	if(x <= lim && !done[x]) {
		cerr << "saving " << x << endl;
		done[x] = 1;
	}
}

void dfs(int u,int p) {
	siz[u] = 1;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		dfs(v,u);
		siz[u] += siz[v];
		cnt[e] = siz[v]*(n - siz[u]);
	}
}

int biggestChild[MAX];
bool dead[MAX];


int floodFill(int u,int p) {
	siz[u] = 1;
	biggestChild[u] = 0;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(dead[v] || v == p) continue;
		int s = floodFill(v,u);
		siz[u] += s;
		biggestChild[u] = max(biggestChild[u],s);
	}
	return siz[u];
}

int dfsCenter(int u,int p,int s) {
	biggestChild[u] = max(biggestChild[u],s - siz[u]);
	int c = u;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(dead[v] || v == p) continue;
		int g = dfsCenter(v,u,s);
		if(biggestChild[g] < biggestChild[c]) c = g;
	}
	return c;
}

int getCenter(int u) {
	int s = floodFill(u,0);
	return dfsCenter(u,0,s);
}

vi DC(int c) {
	c = getCenter(c);
	dead[c] = 1;
	vi tot;
	tot.push_back(0);
	for(int e : E[c]) {
		int v = fr[e] + to[e] - c;
		if(dead[v]) continue;
		vi aux = DC(v);
		int ss = *min_element(all(aux));
		int w = getNext() - ss;
		w = max(w,0);
		w = (w + W[e])/2;
		W[e] = w;
		for(int a : tot)
			for(int b : aux)
				save(a+b+w);
		for(int b : aux) tot.push_back(b + w);
	}
	return tot;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	lim = (2*n*n)/9;
	loop(e,n-1) {
		scanf("%d %d",fr + e,to + e);
		E[fr[e]].push_back(e);
		E[to[e]].push_back(e);
	}
	dfs(1,0);
	vi ord;
	loop(i,n-1) ord.push_back(i);
	sort(all(ord),[](const int & a,const int & b) {
		return cnt[a] > cnt[b];
	});
	loop(i,n-1) W[ord[i]] = i+1;
	DC(1);
	prArr(done,lim+1,bool);
	assert(getNext() > lim);
	loop(e,n-1) printf("%d %d %d\n",fr[e],to[e],W[e]);
	return 0;
}
