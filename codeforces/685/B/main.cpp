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

const int MAX = 300'000 + 10;
vi G[MAX];
int P[MAX],n,m;
int siz[MAX],mx[MAX],ans[MAX];
int ord[MAX],dfs_time;
int in_time[MAX],out_time[MAX],cnt;
pair<int,pi> event[MAX*3];

struct cmp{
	bool operator () (const int & a,const int & b){
		return in_time[a] < in_time[b];
	}
};

void dfs(int u){
	in_time[u] = dfs_time++;
	siz[u] = 1;
	for(int v : G[u]){
		dfs(v);
		siz[u] += siz[v];
		mx[u] = max(mx[u],siz[v]);
	}
	out_time[u] = dfs_time - 1;
}

int main(){
	scanf("%d %d",&n,&m);
	range(i,2,n) scanf("%d",P + i),G[P[i]].pb(i) ;	
	dfs(1);
	range(u,1,n){
		event[cnt++] = mp(2*mx[u],mp(0,u));
		event[cnt++] = mp(siz[u],mp(1,u));
		event[cnt++] = mp(2*siz[u] + 1,mp(2,u));
	}
	sort(event,event + cnt);
	set<int,cmp> S;
	loop(i,cnt){
		int type = event[i].yy.xx,u = event[i].yy.yy;
		if(type == 0) S.insert(u);
		else if(type == 1){
			auto p = S.lower_bound(u);
			if(p != S.end() && out_time[*p] <= out_time[u]) ans[u] = *p; 
		}
		else S.erase(u);
	}
	loop(i,m){
		int u; scanf("%d",&u);
		printf("%d\n",ans[u]);
	}
	return 0;
}
