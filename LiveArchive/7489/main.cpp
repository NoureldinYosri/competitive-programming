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

const int MAX = 100*1000 + 10,MAXLG = 20;
vi G[MAX];
int dfs_in[MAX],dfs_out[MAX],dfs_time;
int depth[MAX],P[MAX][MAXLG],n;

void clean(){
	dfs_time = 0;
	range(i,1,n) G[i].clear();
}

void dfs(int u,int p){
	depth[u] = depth[p] + 1;
	dfs_in[u] = dfs_time++;
	P[u][0] = p;
	loop(i,MAXLG-1) P[u][i + 1] = P[P[u][i]][i];
	for(int v : G[u]) if(v != p) dfs(v,u);
	dfs_out[u] = dfs_time - 1;
}

struct cmp{
public:
	bool operator () (const int & a,const int & b){
		return dfs_in[a] < dfs_in[b];
	}
};
set<int,cmp> S;

bool inSubTree(int a,int b){
	return dfs_in[b] <= dfs_in[a] && dfs_in[a] <= dfs_out[b];
}

int lca(int a,int b){
	if(depth[a] > depth[b]) swap(a,b);
	if(inSubTree(b,a)) return a;
	int k = MAXLG - 1;
	while(a != b){
		if(depth[a] > depth[b]) swap(a,b);
		while(k && inSubTree(a,P[b][k])) k--;
		b = P[b][k];
	}
	return a;
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	range(t,1,T){
		scanf("%d",&n);
		loop(i,n-1){
			int a,b; scanf("%d %d",&a,&b);
			a++,b++;
			G[a].pb(b);
			G[b].pb(a);
		}
		dfs(1,0);
		dfs_out[0] = n;
		int m; scanf("%d",&m);
		while(m--) {
			char c; int x; scanf(" %c %d",&c,&x);
			x++;
			if(c == '+') S.insert(x);
			else S.erase(x);
			if (S.empty()) puts("-1");
			else {
				int a = *S.begin(),b = *S.rbegin();
				printf("%d\n",lca(a,b)-1);
			}
		}
		clean();
		S.clear();
	}
	return 0;
}
