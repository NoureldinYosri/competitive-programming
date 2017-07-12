#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
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

struct pi{
	int x,y;
};

const int MAXN = 50010,MAXQ = 250000,MAXM = 150000,MAXB = 500;
int cnt[MAXN],is_heavy[MAXN],online[MAXN];
int n,m,q,blkSize;
char type[MAXQ];
pi Q[MAXQ];
pi E[MAXM];
int deg[MAXN],mx_deg[MAXN];
int are_connected[MAXB][MAXB];
int h_name[MAXN],rev[MAXB];
vi G[MAXN];


int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&n,&m,&q);
	blkSize = sqrt(max(n,m));
	int o; scanf("%d",&o);
	loop(i,o){
		int u ; scanf("%d",&u);
		online[u] = 1;
	}
	loop(i,m){
		int a,b; scanf("%d %d",&a,&b);
		E[i] = pi({a,b});
		deg[a]++;
		deg[b]++;
		mx_deg[a] = deg[a];
		mx_deg[b] = deg[b];
	}
	loop(i,q){
		scanf(" %c %d",&type[i],&Q[i].x);
		if(type[i] == 'A' || type[i] == 'D') {
			scanf("%d",&Q[i].y);
			int a = Q[i].x,b = Q[i].y;
			if(type[i] == 'A') {
				deg[a]++;
				deg[b]++;
				if (mx_deg[a] < deg[a]) mx_deg[a] = deg[a];
				if (mx_deg[b] < deg[b]) mx_deg[b] = deg[b];
			}
			else if(type[i] == 'B') {
				deg[a]--;
				deg[b]--;
			}
		}
	}
	int h_cnt = min(MAXB,n);
	vi ord; ord.reserve(n);
	range(i,1,n) ord.pb(i);
	sort(all(ord),[](const int & a,const int & b){
		return mx_deg[a] > mx_deg[b];
	});
	loop(i,h_cnt) {
		is_heavy[ord[i]] = 1;
		rev[i] = ord[i];
		h_name[ord[i]] = i;
	}
	loop(i,m){
		int a = E[i].x,b = E[i].y;
		if(is_heavy[a] && is_heavy[b]) {
			cnt[a] += online[b];
			cnt[b] += online[a];
			a = h_name[a];
			b = h_name[b];
			are_connected[a][b] = are_connected[b][a] = 1;
		}
		else if(is_heavy[a] || is_heavy[b]){
			if(is_heavy[a]) swap(a,b);
			cnt[b] += online[a];
			G[a].pb(b);
		}
		else {
			G[a].pb(b);
			G[b].pb(a);
		}
	}
	loop(i,q){
		if(type[i] == 'A'){
			int a = Q[i].x,b = Q[i].y;
			if(is_heavy[a] && is_heavy[b]) {
				cnt[a] += online[b];
				cnt[b] += online[a];
				a = h_name[a];
				b = h_name[b];
				are_connected[a][b] = are_connected[b][a] = 1;
			}
			else if(is_heavy[a] || is_heavy[b]){
				if(is_heavy[a]) swap(a,b);
				cnt[b] += online[a];
				G[a].pb(b);
			}
			else{
				G[a].pb(b);
				G[b].pb(a);
			}
		}
		else if(type[i] == 'D'){
			int a = Q[i].x,b = Q[i].y;
			if(is_heavy[a] && is_heavy[b]) {
				cnt[a] -= online[b];
				cnt[b] -= online[a];
				a = h_name[a];
				b = h_name[b];
				are_connected[a][b] = are_connected[b][a] = 0;
			}
			else if(is_heavy[a] || is_heavy[b]){
				if(is_heavy[a]) swap(a,b);
				cnt[b] -= online[a];
				G[a].erase(find(all(G[a]),b));
			}
			else {
				G[a].erase(find(all(G[a]),b));
				swap(a,b);
				G[a].erase(find(all(G[a]),b));
			}
		}
		else if(type[i] == 'O'){
			int u = Q[i].x;
			assert(!online[u]);
			online[u] = 1;
			if(is_heavy[u]) {
				u = h_name[u];
				loop(v,h_cnt)
						if(are_connected[v][u])
							cnt[rev[v]]++;
			}
			else{
				for(int v : G[u])
					if(is_heavy[v])
						cnt[v]++;
			}
		}
		else if(type[i] == 'F'){
			int u = Q[i].x;
			assert(online[u]);
			online[u] = 0;
			if(is_heavy[u]) {
				u = h_name[u];
				loop(v,h_cnt)
						if(are_connected[v][u])
							cnt[rev[v]]--;
			}
			else{
				for(int v : G[u])
					if(is_heavy[v])
						cnt[v]--;
			}
		}
		else {
			int u = Q[i].x,ans;
			//cerr << u << " -> ";
			//print(G[u],int);
			if(is_heavy[u]) ans = cnt[u];
			else{
				ans = 0;
				for(int v : G[u]) ans += online[v];
			}
			printf("%d\n",ans);
			//cerr <<  ans << endl;
		}
	}


	return 0;
}
