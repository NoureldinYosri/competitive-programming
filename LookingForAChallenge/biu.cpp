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

const int MAXN = 1024, MAXE = 2*MAXN + MAXN*MAXN;
int fr[MAXE], to[MAXE], nxt[MAXE];

int head[MAXN], edge_cnt;
int src, snk;
ll flow[MAXE], cap[MAXE];

void addedge(int a, int b,int c){
    int e = edge_cnt++;
    fr[e] = a;
    to[e] = b;
    cap[e] = c;
    nxt[e] = head[a];
    head[a] = e;
}

void addedge(int a, int b, int c1, int c2){
    addedge(a, b, c1);
    addedge(b, a, c2);
}

int parent_edge[MAXN];
queue<int> q;

bool bfs(int root = src){
    fill(parent_edge, parent_edge + snk + 1, -1);
    while(!q.empty()) q.pop();
    parent_edge[root] = -2;
    q.push(root);
    for(; !q.empty(); q.pop()){
        int u = q.front();
        for(int e = head[u]; ~e; e = nxt[e]) if(cap[e] - flow[e] > 0) {
            int v = to[e];
            if(parent_edge[v] == -1){
			   parent_edge[v] = e;
			   q.push(v);
            }
        }
    }
    return parent_edge[snk] != -1;
}

int augment(){
    ll f = LLONG_MAX;

    for(int v = snk; v != src; v = fr[parent_edge[v]]){
        int e = parent_edge[v];
        f = min(f, cap[e] - flow[e]);
    }
    for(int v = snk; v != src; v = fr[parent_edge[v]]){
        int e = parent_edge[v];
        flow[e] += f;
        flow[e^1] -= f;
    }
    return f;
}

ll X[MAXN];
vp H[MAXN];
bool bad[MAXN];

int main(int argc, char **argv){
	if(argc < 2){
		cerr << "open in.in" << endl;
		freopen("in.in", "r", stdin);
	}
	else{
		cerr << "open " << argv[1] << endl;
		freopen(argv[1], "r", stdin);
	}
    memset(head, -1, sizeof head);
    int n;
    assert(scanf("%d", &n) == 1);
    src = 0;
    snk = n+1;


	ll cost = 0;																	
    for(int i = 1; i <= n;i ++){
        int x; scanf("%d", &x);
        int k; scanf("%d", &k);
        while(k--){
            int v, b; scanf("%d %d", &v, &b);
            addedge(i, v, b, 0);
			H[i].emplace_back(v, b);
        }

        cost += max(x, 0);
        if(x >= 0) addedge(src, i, x, 0);
        else if(x < 0) addedge(i, snk, -x, 0);
		X[i] = x;
    }

    while(bfs()) cost -= augment();

																		
	vi V;
	bfs();
	for(int u = 1; u <= n;u++)
		if(parent_edge[u] != -1)
			V.pb(u);
	
	ll tmp = 0;
	for(int v : V){
		tmp += X[v];
		for(auto [u, b] : H[v])
			tmp -= b * (!binary_search(all(V), u));
	}

	assert(cost == tmp);
	
    printf("%d\n", sz(V));
	for(int v : V) printf("%d ", v);
	puts("");


    return 0;
}

