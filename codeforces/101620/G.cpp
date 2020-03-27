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


const double eps = 1e-9;
const int MAX = 300*1000 + 10;
vi G[MAX];
int n, m;
double E[MAX];
bool inQ[MAX];
map<int, double> F[MAX];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(e, m){
		int a, b; scanf("%d %d", &a, &b);
		G[a].pb(b);
		G[b].pb(a);
	}
	for(int i = 1;i < n;i++)
		E[i] = sz(G[i]);
	queue<int> q;
	inQ[n] = 1;
	for(int i = n;i >= 1; i--)
		q.push(i);
	while(!q.empty()){
		int v = q.front(); q.pop();
		for(int u : G[v]){
			double delta = E[v] - F[u][v];
			delta /= sz(G[u]);
			if(delta <= eps) continue;
			E[u] += delta;
			F[u][v] = E[v];
			if(!inQ[u]){
				inQ[u] = 1;
				q.push(u);
			}
		}
	}

	printf("%.10f\n", E[1]);
	return 0;
}
