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

const int MAX = 200*1000 + 10,mod = 1e9 + 7;
int fr[MAX],to[MAX],type[MAX];
vi E[MAX];
int n;
int Start[MAX][2],End[MAX][2];


ll dfs(int u,int p) {
	ll res = 0;
	for(int e : E[u]) {
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		res += dfs(v,u);
		ll tmp = 0;
		int s0 = 0,s1 = 0;
		int e0 = 0,e1 = 0;
		if(type[e] == 0){
			s0 = Start[v][0] + Start[v][1] + 1;
			e0 = End[v][0] + 1;
		}
		else{
			s1 = Start[v][1] + 1;
			e1 = End[v][0] + End[v][1] + 1;
		}
		tmp = End[u][0] * (ll)(s0 + s1);
		tmp += End[u][1] * (ll)s1;

		tmp += e0 * (ll) Start[u][0];
		tmp += (e0 + e1) * (ll)Start[u][1];

		res += tmp;
		res += s0 + s1 + e0 + e1;

		Start[u][0] += s0;
		Start[u][1] += s1;

		End[u][0] += e0;
		End[u][1] += e1;
	}
//	cout << u << ": " << res << " " << Start[u][0] << " " << Start[u][1] << endl;
	return res;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	loop(e,n-1) {
		scanf("%d %d %d",fr + e,to + e,type + e);
		E[fr[e]].push_back(e);
		E[to[e]].push_back(e);
	}
	printf("%lld\n",dfs(1,0));
	return 0;
}
