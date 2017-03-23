#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 100*1000 + 10;
int id[MAX],W[MAX],name[MAX],vis[MAX];
int color[MAX],n;
vi G[MAX];

int get(int a){
	return id[a] = (a == id[a]) ? a : get(id[a]);
}

void join(int a,int b){
	a = get(a),b = get(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
}

int main(){
	scanf("%d",&n);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	range(i,1,n) scanf("%d",color + i);
	range(u,1,n) id[u] = u,W[u] = 1;
	range(u,1,n) for(int v : G[u]) if(color[u] == color[v]) join(u,v);
	int cnt = 0;
	range(u,1,n) if(get(u) == u) name[u] = cnt++;
	range(u,1,n) {
		int ctr = 0;
		for(int v : G[u]) {
			if(!vis[get(v)]) ctr++;
			vis[get(v)] = 1;
		}
		if(ctr == cnt){
			printf("YES\n%d\n",u);
			return 0;
		}
		if(ctr == cnt - 1 && !vis[get(u)]){
			printf("YES\n%d\n",u);
			return 0;			
		}
		for(int v : G[u]) {
			vis[get(v)] = 0;
		}		
	}
	puts("NO");	
	return 0;
}
