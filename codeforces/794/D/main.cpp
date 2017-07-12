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

const int MAX = 300*1000 + 10;
vi G[MAX],UG[MAX];
int n;
int ord[MAX];
int color[MAX];
int id[MAX];

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int m; scanf("%d %d",&n,&m);
	loop(i,m){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	range(i,1,n) {
		G[i].pb(i);
		sort(all(G[i]));
		ord[i - 1] = i;
	}
	sort(ord,ord + n,[](const int & a,const int & b){
		return G[a] < G[b];
	});
	m = 0;
	for(int i = 0;i < n;){
		int j = i;
		while(j < n && G[ord[i]] == G[ord[j]]) j++;

		++m;
		for(;i < j;i++){
			int u = ord[i];
			id[u] = m;
		}
	}
	range(u,1,n){
		for(int v : G[u])
			if(id[u] != id[v])
				UG[id[u]].pb(id[v]);
	}

	int cnt = 0,root = 1;
	range(u,1,m){
		sort(all(UG[u]));
		UG[u].resize(unique(all(UG[u])) - UG[u].begin());
		if(sz(UG[u]) > 2){
			puts("NO");
			return 0;
		}
		if(sz(UG[u]) == 1) root = u;
		cnt += sz(UG[u]);
	}
	if(cnt != 2*m - 2) {
		puts("NO");
		return 0;
	}
	for(int c = 1;root != -1;c++){
		color[root] = c;
		int new_root = -1;
		for(int v : UG[root])
			if(!color[v]){
				new_root = v;
				break;
			}
		root = new_root;
	}

	puts("YES");
	range(i,1,n) printf("%d%c",color[id[i]]," \n"[i==n]);
	return 0;
}
