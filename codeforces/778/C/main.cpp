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

const int MAX = 300'010;
vi P{1000000007, 999999937, 999999929, 999999893, 999999883, 999999797, 999999761, 999999757, 999999751, 999999739};
ll base[3],mod[3],HASH[3][MAX],mul[3][MAX];
vi G[MAX];
int siz[MAX],pref_child[MAX],ord[MAX],dfs_in[MAX],dfs_out[MAX],dfs_time;
int cnt[MAX],n;
int cnt2[MAX],cnt3[MAX];
char link[MAX];
map<pair<ll,pl>,int> M;

void dfs(int u,int depth){
	siz[u] = 1;
	pref_child[u] = -1;
	ord[dfs_time] = u;
	dfs_in[u] = dfs_time++;
	for(int v : G[u]){
		loop(i,3) HASH[i][v] = (HASH[i][u] + link[v]*mul[i][depth + 1])%mod[i]; 
		dfs(v,depth + 1);
		siz[u] += siz[v];
		if(pref_child[u] == -1 || siz[v] > siz[pref_child[u]])
			pref_child[u] = v;
	}
	dfs_out[u] = dfs_time - 1;
	cnt2[depth] += siz[u];
	cnt3[depth + 1]++;
}

void dfs(int u,bool keep,int depth){
	for(int v : G[u]) if(v != pref_child[u]) dfs(v,0,depth + 1);
	if(pref_child[u] != -1) dfs(pref_child[u],1,depth + 1);
	M[mp(HASH[0][u],mp(HASH[1][u],HASH[2][u]))]++;
	vector<char> used;
	if(pref_child[u] != -1) used.pb(link[pref_child[u]]);
	int ctr = (pref_child[u] == -1) ? 1 : siz[pref_child[u]];

	for(int v : G[u]) if(v != pref_child[u]){
		for(int i = dfs_in[v];i <= dfs_out[v];i++){
			int t = ord[i],cond = 0;
			for(char c : used)	{
				int h[3];
				loop(i,3) {
					h[i] = HASH[i][t] + (c - link[v])*mul[i][depth + 1];
					h[i] = (h[i]%mod[i] + mod[i])%mod[i];
				}
				if(M.find(mp(h[0],mp(h[1],h[2]))) != M.end()) cond = 1;
			}
			ctr += !cond;
		}
		for(int i = dfs_in[v];i <= dfs_out[v];i++){
			int t = ord[i];
			auto p = mp(HASH[0][t],mp(HASH[1][t],HASH[2][t]));
			M[p]++;
		}
		used.pb(link[v]);
	}

	cnt[depth] += ctr;
	if(!keep) {
		for(int i = dfs_in[u];i <= dfs_out[u];i++){
			int t = ord[i];
			auto p = mp(HASH[0][t],mp(HASH[1][t],HASH[2][t]));
			M[p]--;
			if(!M[p]) M.erase(p);
		}
	}
}

int main(){
	srand(time(0));
	loop(i,3) base[i] = 26 + rand()%20;
	loop(i,3) mod[i] = P[3*i+rand()%(3 + (i == 2))];
	loop(i,3) mul[i][0] = 1;
	loop(i,3) HASH[i][1] = rand()%mod[i];
	loop(i,MAX - 1){
		loop(j,3)
			mul[j][i + 1] = (mul[j][i] *1LL*base[j])%mod[j];
	}
	scanf("%d",&n);
	loop(i,n-1){
		int a,b; char c;
		scanf("%d %d %c",&a,&b,&c);
		G[a].pb(b);
		link[b] = c;
	}
	dfs(1,0);
	assert(siz[1] == n);
	assert(dfs_time == n);
//	prArr(ord,n,int);
//	prArr(cnt2,n-1,int);
	loop(i,n-1) cnt3[i + 1] += cnt3[i];
//	prArr(cnt3,n-1,int);	
	dfs(1,1,0);
//	prArr(cnt,n-1,int);
	int p = 0;
	for(int i = 0;i < n - 1;i++)
		if(cnt3[i] + cnt[i] < cnt3[p] + cnt[p])
			p = i;
	cout << cnt[p] + cnt3[p] << endl;
	cout << p + 1 << endl;	
	//cerr << cnt[p] + cnt3[p] << endl;
	//cerr << p + 1 << endl;	
	return 0;
}
