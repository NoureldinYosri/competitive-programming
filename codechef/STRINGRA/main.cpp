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

const int MAX = 100*1000 + 10;
vi G[MAX];
int T,n,m;
int val[MAX],lst[MAX];



vi aux;
bool validate(){
	set<int> seen;
	for(int u = n;u >= 0;u--) {
		aux.clear();
		for(int v : G[u]) aux.pb(val[v]);
		sort(all(aux));
		aux.resize(unique(all(aux)) - aux.begin());
/*
 		cerr << u << endl;
		print(aux,int);
		print(seen,int);
		cerr << endl;
*/
		if(aux.size() != seen.size()) return 0;
		seen.insert(val[u]);
	}

	return 1;
}

bool solve(){
	set<int> place_holders{all(G[0])};
	int ctr = 0;
	for(int x : place_holders) val[x] = ++ctr;
	for(int u = 1;u <= n;u++){
		if(place_holders.find(u) == place_holders.end()) return 0;
		int val = ::val[u];
		place_holders.erase(u);
		int v = -1,cnt = 0;
		for(int t : G[u]) {
			if(place_holders.find(t) == place_holders.end()) {
				v = t;
				cnt++;
			}
		}
		if(cnt > 1) return 0;
		if(cnt == 1) {
			place_holders.insert(v);
			::val[v] = val;
		}
	}
	return 1;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&m);
		memset(lst,0,sizeof lst);
		loop(i,m){
			int x,y; scanf("%d %d",&x,&y);
			G[x].pb(y);
		}

		bool cond = solve();
//		prArr(val+1,n,int);
		cond = cond && validate();
		if(!cond) puts("-1");
		else {
			loop(i,n) printf("%d%c",val[i+1]," \n"[i==n-1]);
		}

		range(i,0,n) {
			G[i].clear();
		}
	}
	return 0;
}
