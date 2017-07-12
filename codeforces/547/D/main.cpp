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
#define pl pair<ll,ll>
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
const int MAX = 200*1000 + 10;
int X[MAX],Y[MAX],n;
vi vX,vY;
set<int> adj[MAX*2];
bool discarded[MAX];
int cnt[MAX*2];
char color[MAX];

void erase(int e){
	int u = X[e],v = Y[e];
	adj[u].erase(e);
	adj[v].erase(e);
}

vi euler(int u){
	vp ST;
	vi circuit;
	ST.pb(mp(-1,u));
	while(!ST.empty()){
		int e = ST.back().xx;
		u = ST.back().yy;
		ST.pop_back();
		if(adj[u].empty()) {
			if(e != -1) circuit.pb(e);
			continue;
		}
		int oe = *adj[u].begin();
		int v = X[oe] + Y[oe] - u;
		erase(oe);
		ST.pb(mp(e,u));
		ST.pb(mp(oe,v));
	}
	return circuit;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	vX.reserve(n);
	vY.reserve(n);
	loop(i,n) {
		scanf("%d %d",X + i,Y + i);
		vX.pb(X[i]);
		vY.pb(Y[i]);
	}
	sort(all(vX));
	vX.resize(unique(all(vX)) - vX.begin());
	sort(all(vY));
	vY.resize(unique(all(vY)) - vY.begin());

	loop(i,n){
		X[i] = lower_bound(all(vX),X[i]) - vX.begin();
		Y[i] = lower_bound(all(vY),Y[i]) - vY.begin() + vX.size();
		adj[X[i]].insert(i);
		adj[Y[i]].insert(i);
	}
	queue<int> q;
	loop(i,sz(vX) + sz(vY)) if(adj[i].size()%2 == 1) q.push(i);
	vi killed;
	while(!q.empty()){
		int u = q.front(); q.pop();
		if(adj[u].size()%2 == 0) continue;
		int e = *adj[u].begin();
		int v = X[e] + Y[e] - u;
		erase(e);
		if(adj[v].size()%2 == 1) q.push(v);
		discarded[e] = 1;
		killed.pb(e);
	}
	reverse(all(killed));
	loop(i,sz(vX)) if(adj[i].size()) {
		vi circuit = euler(i);
		int c = 1;
		for(int e : circuit){
			color[e] = (c == 1) ? 'r' : 'b';
			int u = X[e],v = Y[e];
			cnt[u] += c;
			cnt[v] += c;
			c *= -1;
		}
	}
	for(int e : killed) {
		int u = X[e],v = Y[e],c = 1;
		if(cnt[u] > 0 || cnt[v] > 0) c = -1;
//		fprintf(stderr,"cnt[%d] = %d ,cnt[%d] = %d .. c = %d ,e = %d\n",u,cnt[u],v,cnt[v],c,e);
		color[e] = (c == 1) ? 'r' : 'b';
		cnt[u] += c;
		cnt[v] += c;
	}
	puts(color);
	return 0;
}
