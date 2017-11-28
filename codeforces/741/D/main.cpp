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

const int MAX = 500*1000 + 10;
vi children[MAX],lookFor[MAX];
int compressionArray[MAX],m;
int parent[MAX],siz[MAX],pref_child[MAX],depth[MAX],euler[MAX],dfs_in[MAX],dfs_out[MAX],dfs_time,n;
char ch[MAX];
int MASK[MAX],cMASK[MAX],maxDepth[MAX],ans[MAX];

string b2s(int msk) {
	string res ;
	loop(i,26) res += (msk & (1 << i)) ? '1' : '0';
	return res;
}

void dfs(int u) {
	siz[u] = 1;
	depth[u] = depth[parent[u]] + 1;
	dfs_in[u] = dfs_time;
	euler[dfs_time] = u;
	dfs_time++;
	for(int v : children[u]) {
		MASK[v] = MASK[u] ^ (1 << (ch[v] - 'a'));
		dfs(v);
		siz[u] += siz[v];
		if(siz[v] > siz[pref_child[u]])
			pref_child[u] = v;
	}
	dfs_out[u] = dfs_time;
}


void compress(){
	copy(MASK,MASK + n + 1,compressionArray);
	sort(compressionArray,compressionArray + n + 1);
	m = unique(compressionArray,compressionArray + n + 1) - compressionArray;
	loop(i,n+1){
//		assert(binary_search(compressionArray,compressionArray + m,MASK[i]));
		cMASK[i] = lower_bound(compressionArray,compressionArray + m,MASK[i]) - compressionArray;
	}
	loop(i,m){
		int x = compressionArray[i];
		lookFor[i].pb(i);
		loop(j,26) {
			int y = x ^ (1 << j);
			if(binary_search(compressionArray,compressionArray + m,y))
				lookFor[i].pb(lower_bound(compressionArray,compressionArray + m,y) - compressionArray);
		}
	}
}

void dsu(int u,bool keep) {
	for(int v : children[u]) if(v != pref_child[u]) dsu(v,0);
	if(pref_child[u]) dsu(pref_child[u],1);

	for(int v : children[u]) ans[u] = max(ans[u],ans[v]);
//	cerr << u << " " << depth[u] << " " ;
//	prArr(maxDepth,m,int);

	for(int x : lookFor[cMASK[u]]) ans[u] = max(ans[u],maxDepth[x] - depth[u]);
	int cumsk = cMASK[u];
	maxDepth[cumsk] = max(maxDepth[cumsk],depth[u]);
//	cerr << cumsk << " ";
//	prArr(maxDepth,m,int);

	for(int v : children[u])
		if(v != pref_child[u]) {
			for(int i = dfs_in[v];i < dfs_out[v];i++) {
				int t = euler[i],cmsk = cMASK[t];
				for(int x : lookFor[cmsk])
					ans[u] = max(ans[u],maxDepth[x] + depth[t] - 2*depth[u]);
			}
			for(int i = dfs_in[v];i < dfs_out[v];i++) {
				int t = euler[i],cmsk = cMASK[t];
				maxDepth[cmsk] = max(maxDepth[cmsk],depth[t]);
			}
		}

	if(!keep){
//		cerr << "erasing " << u << endl;
		for(int i = dfs_in[u];i < dfs_out[u];i++) {
			int t = euler[i];
			maxDepth[cMASK[t]] = -2*MAX;
		}
	}
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	range(i,2,n) {
		scanf("%d %c",parent + i,ch + i);
		children[parent[i]].pb(i);
	}
	dfs(1);
	compress();
	fill(maxDepth,maxDepth + m,-2*MAX);
	dsu(1,0);
	range(i,1,n) printf("%d%c",ans[i]," \n"[i==n]);
	return 0;
}
