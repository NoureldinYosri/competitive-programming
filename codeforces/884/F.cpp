#pragma GCC optimize ("O3")
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
using namespace std;

vi fr, to, capacity, cost, nxt;
vi head;
int N, src, snk;

void add_edge(int a, int b, int cap, int w){
	int e = sz(fr);
	fr.pb(a);
	to.pb(b);
	capacity.pb(cap);
	cost.pb(w);
	nxt.pb(head[a]);
	head[a] = e;
}

void add_bi_edge(int a, int b, int cap, int c){
	add_edge(a , b, cap, c);
	add_edge(b, a, 0, -c);
}

int n;
char txt[111];
int B[111];
int ctr[26];

vi dist, inEdge;

bool bellman(){
	dist.clear();
	inEdge.clear();
	dist.resize(N, 1 << 29);
	inEdge.resize(N, -1);
	
	dist[src] = 0;
	loop(i, n-1){
		bool done = 1;
		loop(e, sz(fr)) if(capacity[e]){
			int a = fr[e], b = to[e];
			if(dist[a] + cost[e] < dist[b]){
				dist[b] = dist[a] + cost[e];
				inEdge[b] = e;
			}
		}
		if(!done) break;
	}
	return inEdge[snk] != -1;
}

void augment(pi & ret){
	ret.first++;
	ret.second += dist[snk];
	for(int u = snk; u != src;){
		int e = inEdge[u];
		capacity[e] --;
		capacity[e^1] ++;
		u = fr[e];
	}
}

pair<int, int> MCMF(){
	pi ret;
	while(bellman())
		augment(ret);
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %s", &n, txt);
	loop(i, n) scanf("%d", B + i);
	loop(i, n) ctr[txt[i]-'a']++;
	
	N = 1 + 26 + 13*n + n + 1;
	src = 0;
	snk = N-1;
	head.resize(N, -1);

	vi L1, L2, L3;
	int m = 0;
	loop(i, 26) L1.pb(++m);
	loop(i, n/2) loop(j, 26) L2.pb(++m);
	loop(i, n) L3.pb(++m);
	
	loop(i, 26) add_bi_edge(src, L1[i], ctr[i], 0);
	m = n/2;
	loop(i, 26) loop(j, m) add_bi_edge(L1[i], L2[j*26 + i], 1, 0);
	loop(j, m) loop(c, 26) {
		int a = j, b = n-1-j;
		int s = L2[j*26 + c];
		add_bi_edge(s, L3[a], 1, -B[a]*(txt[a]-'a' == c));
		add_bi_edge(s, L3[b], 1, -B[b]*(txt[b]-'a' == c));
	}
	for(int i : L3) add_bi_edge(i, snk, 1, 0);
	cout << -MCMF().second << endl;
	return 0;
}
