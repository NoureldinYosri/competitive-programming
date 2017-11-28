#pragma GCC optimize ("O3")
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

struct triple{
	int a,b,c;
};

const int MAX = 1 << 20;
set<int> E[MAX];
int fr[MAX],to[MAX],done[MAX];
int n,m;
vector<triple> ans;

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	loop(e,m) {
		scanf("%d %d",fr + e,to + e);
		E[fr[e]].insert(e);
		E[to[e]].insert(e);
	}
	set<pi> S;
	range(i,1,n) S.insert(mp(sz(E[i]),i));
	while(!S.empty()) {
		int u = S.begin()->yy;
		S.erase(S.begin());
		if(E[u].empty()) continue;
		int e1 = *E[u].begin();
		int v = fr[e1] + to[e1] - u;
		auto tmp = *S.find(mp(sz(E[v]),v));
		E[u].erase(e1);
		E[v].erase(e1);
		S.erase(tmp);
		if(!E[v].empty()) {
			int e2 = *E[v].begin();
			int t = fr[e2] + to[e2] - v;
			tmp = *S.find(mp(sz(E[t]),t));
			S.erase(tmp);
			E[t].erase(e2);
			E[v].erase(e2);
			ans.pb(triple({u,v,t}));
			if(!E[t].empty()) S.insert(mp(sz(E[t]),t));
		}
		if(!E[u].empty()) S.insert(mp(sz(E[u]),u));
		if(!E[v].empty()) S.insert(mp(sz(E[v]),v));
	}

	printf("%d\n",sz(ans));
	for(auto t : ans)
		printf("%d %d %d\n",t.a,t.b,t.c);
	return 0;
}
