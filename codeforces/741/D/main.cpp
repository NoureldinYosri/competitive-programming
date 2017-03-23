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

const int MAX = 500'010;
vi G[MAX];
char ch[MAX];
int color[MAX],aux[MAX],n,k;
int siz[MAX],dfs_in[MAX],dfs_out[MAX],dfs_time,pref_child[MAX],ord[MAX],cnt[MAX];
ll ans[MAX];

int dfs(int u){
	siz[u] = 1;
	pref_child[u] = -1;
	ord[dfs_time] = u;
	dfs_in[u] = dfs_time++;
	for(int v : G[u]){
		color[v] = color[u] ^ (1 << (ch[v] - 'a'));
		siz[u] += dfs(v);
		if(pref_child[u] == -1 || siz[v] > siz[pref_child[u]])
			pref_child[u] = v; 
	}
	dfs_out[u] = dfs_time - 1;
	return siz[u];
}

string conv(int msk){
	string s;
	loop(i,26) s += (msk & (1 << i)) ? '1' : '0';
	return s;
}

void add(int c,int u,int t){
	ans[u] += cnt[c];
	int x = aux[c];
	for(int tmp = x;tmp;tmp ^= LSOne(tmp)){
		int y = x ^ LSOne(tmp);
		if(!binary_search(aux,aux + k,y)) continue;
		ans[u] += cnt[lower_bound(aux,aux + k,y) - aux];
		if(cnt[lower_bound(aux,aux + k,y) - aux]){
			cerr << "add " << cnt[lower_bound(aux,aux + k,y) - aux] << " to " << u << " from " << t << " and " << conv(y) << " and " << conv(x) << endl;
		}
	}
}

void dfs(int u,bool keep){
	for(int v : G[u]) if(v != pref_child[u]) dfs(v,0);
	if(pref_child[u] != -1) dfs(pref_child[u],1);
	for(int v : G[u]) ans[u] += ans[v];
	add(color[u],u,u);
	cnt[color[u]]++;
	for(int v : G[u]) if(v != pref_child[u]){
		for(int i = dfs_in[v];i <= dfs_out[v];i++){
			int t = ord[i];
			add(color[t],u,t);
		}
		for(int i = dfs_in[v];i <= dfs_out[v];i++)
			++cnt[color[ord[i]]];
	}
	if(!keep){
		for(int i = dfs_in[u];i <= dfs_out[u];i++)
			cnt[color[ord[i]]]--;
	}
}

int main(){
	scanf("%d",&n);
	range(i,2,n){
		int p;  scanf(" %d %c",&p,ch + i);
		G[p].pb(i);
	}
	dfs(1);
	range(i,1,n) aux[i] = color[i];
	sort(aux,aux + n);
	k = unique(aux,aux + n) - aux;
	range(i,1,n) color[i] = lower_bound(aux,aux + k,color[i]) - aux;
	
	dfs(1,1);
	prArr(ans+1,n,ll);
	
	
	return 0;
}
