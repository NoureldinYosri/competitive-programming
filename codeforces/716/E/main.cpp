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
int mod,n,m,k;
vi E[MAX];
int UP[MAX],DOWN[MAX];
int color[MAX],aux[MAX];
int p10[MAX],inv[MAX];
int fr[MAX],to[MAX],digit[MAX];
int siz[MAX],pref_child[MAX],dfs_in[MAX],dfs_out[MAX],dfs_time,ord[MAX];
int cnt[MAX],depth[MAX],cnt2[MAX],aux2[MAX];
ll ans = 0;


int mul(int x,int y){
	return (x*1LL*y)%mod;
}
int add(int x,int y){
	x += y;
	if(x >= mod) x -= mod;
	if(x < 0) x += mod;
	return x;
}

int pow_mod(int x,int p){
	if(!p) return x%mod;
	int y = 1;
	for(;p > 1;p >>= 1){
		if(p & 1) y = mul(y,x);
		x = mul(x,x);
	}
	return mul(x,y);
}

int get_phi(){
	int ret = mod;
	int n = mod;
	for(int i = 2;i*i <= n;i++)
		if(n%i == 0){
			ret -= ret/i;
			while(n%i == 0) n /= i;
		}
	if(n != 1) ret -= ret/n;
	return ret;
}

int dfs(int u,int p){
	pref_child[u] = -1;
	siz[u] = 1;
	dfs_in[u] = dfs_time;
	ord[dfs_time++] = u;
	depth[u] = u ? (depth[p] + 1) : 0;
	int d = depth[u];
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p) continue;
		DOWN[v] = add(mul(DOWN[u],10),digit[e]);
		UP[v] = add(UP[u],mul(digit[e],p10[d]));
		siz[u] += dfs(v,u);
		if(pref_child[u] == -1 || siz[v] > siz[pref_child[u]])
			pref_child[u] = v; 
	}
	dfs_out[u] = dfs_time - 1;
	return siz[u];
}

void dfs(int u,int p,bool keep){
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p || v == pref_child[u]) continue;
		dfs(v,u,0);
	}
	if(pref_child[u] != -1) {
		int v = pref_child[u];	
		dfs(v,u,1);
		for(int i = dfs_in[v];i <= dfs_out[v];i++){
			int t = ord[i];
			if(DOWN[u] == DOWN[t]){
				cerr << "special " << u << " to " << t << endl;
				ans++;
			}
		}
	}
	cnt[DOWN[u]]++;
	cnt2[UP[u]]++;
	for(int e : E[u]){
		int v = fr[e] + to[e] - u;
		if(v == p || v == pref_child[u]) continue;
		for(int i = dfs_in[v];i <= dfs_out[v];i++){
			int t = ord[i];
			int x = add(UP[t], - UP[u]);
			x = mul(x,inv[depth[u]]);
			x = add(aux[DOWN[u]],-x);
			if(!binary_search(aux,aux + m,x)) continue;
			cerr << "from " << t << " up to " << u << endl;
			ans += cnt[lower_bound(aux,aux + m,x) - aux];
		}
		
		for(int i = dfs_in[v];i <= dfs_out[v];i++){
			int t = ord[i];
			cnt[DOWN[t]]++;
		}
	}

	if(!keep){
		for(int i = dfs_in[u];i <= dfs_out[u];i++){
			int t = ord[i];
			cnt[DOWN[t]]--;
		}
	}
		
}

int main(){
	scanf("%d %d",&n,&mod);
	if(mod == 1){
		cout << n*(n - 1LL) << endl;
		return 0;
	}
	loop(e,	n-1){
		scanf("%d %d %d",fr + e,to + e,digit + e);
		E[fr[e]].pb(e);
		E[to[e]].pb(e);
	}
	p10[0] = 1;
	loop(i,n) p10[i+1] = mul(p10[i],10);
	int phi = get_phi();
	loop(i,n+1) inv[i] = pow_mod(p10[i],phi-1);

	dfs(0,-1);
	loop(i,n) aux[i] = DOWN[i],aux2[i] = UP[i];
	sort(aux,aux + n);
	m = unique(aux,aux + n) - aux;
	sort(aux2,aux2 + n);
	k = unique(aux2,aux2 + n) - aux;
	loop(i,n) {
		DOWN[i] = lower_bound(aux,aux + m,DOWN[i]) - aux;
		UP[i] = lower_bound(aux2,aux2 + k,UP[i]) - aux2;
	}	
	dfs(0,-1,1);
	cout << ans << endl;
	cerr << ans << endl;	
	return 0;
}
