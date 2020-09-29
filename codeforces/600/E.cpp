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

const int MAX = 100'010;
vi G[MAX];
int n,color[MAX];
ll ans [MAX];
map<int,int> *cnt[MAX];
map<int,ll> *sum[MAX];
void dfs(int u,int p){
	int mx = 0;
	for(int v : G[u]) if(v != p) {
		dfs(v,u);
		mx = max(mx,(int)cnt[v]->size());
	}
	for(int v : G[u]) if(v != p) {
		if(mx == cnt[v]->size()) {
			cnt[u] = cnt[v];
			sum[u] = sum[v];
		}
	}
	if(!cnt[u]){
		cnt[u] = new map<int,int>();
		sum[u] = new map<int,ll>();
		(*cnt[u])[color[u]] = 1;
		(*sum[u])[1] = color[u];
		ans[u] = color[u];
		return;
	}
	map<int,int> & cnt = *::cnt[u];
	map<int,ll> & sum = *::sum[u]; 
	int c = color[u];
	if(cnt.find(c) == cnt.end()) {
		cnt[c] = 1;
		sum[1] += c;
	}
	else{
		sum[cnt[c]] -= c;
		if(!sum[cnt[c]]) sum.erase(cnt[c]);
		sum[++cnt[c]] += c;
	}
	for(int v : G[u]) if(v != p) {
		if(::cnt[u] == ::cnt[v]) continue;
		for(auto & p : *::cnt[v]){
			int c = p.xx; int ctr = p.yy;
			if(cnt.find(c) == cnt.end()){
				cnt[c] = ctr;
				sum[ctr] += c;
			}
			else{
				sum[cnt[c]] -= c;
				if(!sum[cnt[c]]) sum.erase(cnt[c]);				
				cnt[c] += ctr;
				sum[cnt[c]] += c;
			}
		}
	}
	ans[u] = sum.rbegin()->yy;
}

int main(){
	scanf("%d",&n);
	range(i,1,n) scanf("%d",color + i);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1,0);

	range(i,1,n) printf("%lld%c",ans[i]," \n"[i==n]);
//	prArr(ans+1,n,ll);	
	return 0;
}
