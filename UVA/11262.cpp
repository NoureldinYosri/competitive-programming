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





#define MAX 100001
#define NIL 0
#define INF (1<<28)

vector< int > G[MAX];
int n, m, match[MAX], dist[MAX];
// n: number of nodes on left side, nodes are numbered 1 to n
// m: number of nodes on right side, nodes are numbered n+1 to n+m
// G = NIL[0] ∪ G1[G[1---n]] ∪ G2[G[n+1---n+m]]

bool bfs() {
    int i, u, v, len;
    queue< int > Q;
    for(i=1; i<=n; i++) {
        if(match[i]==NIL) {
            dist[i] = 0;
            Q.push(i);
        }
        else dist[i] = INF;
    }
    dist[NIL] = INF;
    while(!Q.empty()) {
        u = Q.front(); Q.pop();
        if(u!=NIL) {
            len = G[u].size();
            for(i=0; i<len; i++) {
                v = G[u][i];
                if(dist[match[v]]==INF) {
                    dist[match[v]] = dist[u] + 1;
                    Q.push(match[v]);
                }
            }
        }
    }
    return (dist[NIL]!=INF);
}

bool dfs(int u) {
    int i, v, len;
    if(u!=NIL) {
        len = G[u].size();
        for(i=0; i<len; i++) {
            v = G[u][i];
            if(dist[match[v]]==dist[u]+1) {
                if(dfs(match[v])) {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int hopcroft_karp() {
    int matching = 0, i;
    // match[] is assumed NIL for all vertex in G
    while(bfs())
        for(i=1; i<=n; i++)
            if(match[i]==NIL && dfs(i))
                matching++;
    return matching;
}

vector<pi> red,blue;
char buffer[10];


vector<pair<int,pi> > E;

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		int k; scanf("%d %d",&n,&k);
		red.clear();
		blue.clear();
		loop(i,n){
			int x,y;
			scanf("%d %d %s",&x,&y,buffer);
			if(buffer[0] == 'r') red.emplace_back(x,y);
			else blue.emplace_back(x,y);
		}
		E.clear();
		for(int i = 0;i < sz(blue);i++)
			for(int j = 0;j < sz(red);j++){
				int dx = blue[i].first - red[j].first;
				int dy = blue[i].second - red[j].second;
				E.emplace_back(dx*dx + dy*dy,pi(i+1,j+1+sz(blue)));
			}
		
		sort(all(E));
		loop(i,n+1) G[i].clear(),match[i] = NIL;
		
		int cnt = 0;
		for(auto e : E){
			int a = e.second.first;
			int b = e.second.second;
			G[a].push_back(b);
			cnt += hopcroft_karp();
			if(cnt >= k) {
				int q = 0;
				if(e.first){
					q = sqrt(e.first) + 2;
					while(q*q >= e.first) q--;
					q ++;
				}
				printf("%d\n",q);
				break;
			}
		}
		if(cnt < k) puts("Impossible");
	}
	return 0;
}
