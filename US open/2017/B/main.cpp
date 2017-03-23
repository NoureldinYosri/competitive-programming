#pragma GCC optimize("O3")
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#include <ext/hash_map>
#include <vector>
#include <utility>
#include <map>
#include <climits>
#define xx first
#define yy second
#define pb push_back
#define sz(X) ((int)X.size())
using namespace std;
using namespace __gnu_cxx;

const int MAX = 200000 + 10,MAXB = 700;
vector<pair<int,int> > G[MAX],hG[MAX],lG[MAX];
int N,M,K,Q,mx;
hash_map<int,map<int,int> > colors[MAXB];
map<int,int> heavy_cnt[MAXB],light_cnt;
int color[MAX],id[MAX],r[MAX];
bool is_heavy[MAX];
/*
inline void add_color(int u,int c,int w){
	u = id[u];
	if(colors[u].find(c) != colors[u].end()){
		assert(!colors[u][c].empty());
		int o = colors[u][c].begin() ->xx;
		heavy_cnt[u][o]--;
		if(!heavy_cnt[u][o]) heavy_cnt[u].erase(o);
	}
	colors[u][c][w]++;
	heavy_cnt[u][colors[u][c].begin()->xx]++;
}

inline void erase_color(int u,int c,int w){
	u = id[u];
	assert(colors[u].find(c) != colors[u].end() && !colors[u][c].empty());
	int o = colors[u][c].begin()->xx;
	heavy_cnt[u][o]--;
	if(!heavy_cnt[u][o]) heavy_cnt[u].erase(o);

	colors[u][c][w]--;
	if(!colors[u][c][w]) colors[u][c].erase(w);
	if(!colors[u][c].empty()) heavy_cnt[u][colors[u][c].begin()->xx]++;
	else colors[u].erase(c);
}
*/
int main(){
	freopen("grass.in","r",stdin);
	freopen("grass.out","w",stdout);
	scanf("%d %d %d %d",&N,&M,&K,&Q);
	loop(i,M){
		int a,b,c; scanf("%d %d %d",&a,&b,&c);
		G[a].emplace_back(b,c);
		G[b].emplace_back(a,c);
	}	
	mx = sqrt(M) + 5;
	range(i,1,N) scanf("%d",color + i);
	range(i,1,N) is_heavy[i] = G[i].size() > mx;
	range(u,1,N) {
		for(auto & e : G[u])	{
			if(is_heavy[e.xx]) hG[u].pb(e);
			else lG[u].pb(e);
		}
	}	
	range(u,1,N) if(!is_heavy[u]) for(auto & e : lG[u]) if(e.xx < u && color[e.xx] != color[u]) light_cnt[e.yy]++;
	int ctr = 0;
	range(i,1,N) if(is_heavy[i]) {
		id[i] = ctr++;
		int u = id[i];
		r[u] = i;
		for(auto e : G[i]){
			int u = i,c = color[e.xx],w = e.yy;
			u = id[u];
			if(colors[u].find(c) != colors[u].end()){
				int o = colors[u][c].begin() ->xx;
				heavy_cnt[u][o]--;
				if(!heavy_cnt[u][o]) heavy_cnt[u].erase(o);
			}
			colors[u][c][w]++;
			heavy_cnt[u][colors[u][c].begin()->xx]++;
		}
	}
	//prArr(is_heavy+1,N,int);
	for(int q = 0;q < Q;q++){
		int field,nc; scanf("%d %d",&field,&nc);
		if(!is_heavy[field]){
			for(auto & e : lG[field]){
				if(color[field] != color[e.xx]) {
					int w = e.yy;
					light_cnt[w]--;
					if(!light_cnt[w]) light_cnt.erase(w);
				}
			}
			for(auto & e : lG[field])
				if(nc != color[e.xx]) 
					light_cnt[e.yy]++;
		}
		for(auto & e : hG[field]) {
			int u = e.xx,c = color[field],w = e.yy;
			u = id[u];
			int o = colors[u][c].begin()->xx;
			heavy_cnt[u][o]--;
			if(!heavy_cnt[u][o]) heavy_cnt[u].erase(o);

			colors[u][c][w]--;
			if(!colors[u][c][w]) colors[u][c].erase(w);
			if(!colors[u][c].empty()) heavy_cnt[u][colors[u][c].begin()->xx]++;
			else colors[u].erase(c);
		}
		color[field] = nc;
		for(auto & e : hG[field]) {
			int u = e.xx,c = color[field],w = e.yy;
			u = id[u];
			if(colors[u].find(c) != colors[u].end()){
				int o = colors[u][c].begin() ->xx;
				heavy_cnt[u][o]--;
				if(!heavy_cnt[u][o]) heavy_cnt[u].erase(o);
			}
			colors[u][c][w]++;
			heavy_cnt[u][colors[u][c].begin()->xx]++;
		}		
		int x = light_cnt.empty() ? INT_MAX : light_cnt.begin()->xx ;
		loop(i,ctr) {
			if(heavy_cnt[i].empty()) continue;
			int o = INT_MAX,myc = color[r[i]];
			if(colors[i].find(myc) != colors[i].end()) o = colors[i][myc].begin()->xx; 
			if(heavy_cnt[i].begin()->xx == o){
				if(heavy_cnt[i].begin()->yy > 1) x = min(x,heavy_cnt[i].begin()->xx);
				else if(sz(heavy_cnt[i]) > 1){
					auto p = heavy_cnt[i].begin(); ++p;
					x = min(x,p->xx);
				}
			}
			else x = min(x,heavy_cnt[i].begin()->xx);
		}
		printf("%d\n",x);
//		cerr << x << endl;
	}
	return 0;
}

