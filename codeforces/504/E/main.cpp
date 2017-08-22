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

const int MAX = 300*1000 + 10,MAXLG = 20;
vi G[MAX];
char label[MAX];

int depth[MAX],Hash[MAX][2],parent[MAX][MAXLG],parent_hash[MAX][MAXLG][2];
int dfs_in[MAX],dfs_out[MAX],dfs_time;

int base[2],mod[2];
int base_power[2][MAX];
int n,m;

vi cand_base {26,29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139};
vi cand_mod {999999151,999999739,1000000321,1000000861,999999163,999999751,1000000349,1000000871,999999181,999999757,1000000363,1000000891,999999191,999999761,1000000403,1000000901,999999193,999999797,1000000409,1000000919,999999197,999999883,1000000411,1000000931,999999223,999999893,1000000427,1000000933,999999229,999999929,1000000433,1000000993,999999323,999999937,1000000439,1000001011,999999337,1000000007,1000000447,1000001021,999999353,1000000009,1000000453,1000001053,999999391,1000000021,1000000459,1000001087,999999433,1000000033,1000000483,1000001099,999999487,1000000087,1000000513,1000001137,999999491,1000000093,1000000531,1000001161,999999503,1000000097,1000000579,1000001203,999999527,1000000103,1000000607,1000001213,999999541,1000000123,1000000613,1000001237,999999587,1000000181,1000000637,1000001263,999999599,1000000207,1000000663,1000001269,999999607,1000000223,1000000711,1000001273,999999613,1000000241,1000000753,1000001279,999999667,1000000271,1000000787,1000001311,999999677,1000000289,1000000801,1000001329,999999733,1000000297,1000000829,1000001333};

inline int mul(int a,int b,int mod){
	return (a*1LL*b)%mod;
}
inline int add(int a,int b,int mod){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}


ostream& operator << (ostream & st,const pi & a){
	st << "(" << a.xx << " ," << a.yy << ")";
	return st;
}

void init(){
	srand(0);
	srand(time(0));
	random_shuffle(all(cand_base));
	random_shuffle(all(cand_mod));
	loop(i,2) base[i] = cand_base[i];
	loop(i,2) mod[i] = cand_mod[i];
	loop(i,2) base_power[i][0] = 1;
	for(int i= 0;i < 2;i++)
		for(int j = 0;j < MAX-1;j++)
			base_power[i][j + 1] = mul(base_power[i][j],base[i],mod[i]);
}

void dfs(int u,int p){
	dfs_in[u] = dfs_time++;
	depth[u] = depth[p] + 1;

	loop(k,2) Hash[u][k] = add(mul(Hash[p][k],base[k],mod[k]),label[u] - 'a' + 1,mod[k]);


	parent[u][0] = p;
	parent_hash[u][0][0] = label[u] - 'a' + 1;
	parent_hash[u][0][1] = label[u] - 'a' + 1;
	loop(i,MAXLG-1) {
		int p = parent[u][i];
		parent[u][i + 1] = parent[parent[u][i]][i];
		for(int k = 0;k < 2;k++) {
			parent_hash[u][i + 1][k] = mul(parent_hash[u][i][k],base_power[k][1 << i],mod[k]);
			parent_hash[u][i + 1][k] = add(parent_hash[u][i+1][k],parent_hash[p][i][k],mod[k]);
		}
	}
	for(int v : G[u]) if(v != p) dfs(v,u);
	dfs_out[u] = dfs_time - 1;
}

bool inSubTree(int a,int b){
	return dfs_in[b] <= dfs_in[a] && dfs_in[a] <= dfs_out[b];
}

int lca(int a,int b){
	if(depth[a] > depth[b]) swap(a,b);
	if(inSubTree(b,a)) return a;
	int k = MAXLG - 1;
	while(a != b){
		if(depth[a] > depth[b]) swap(a,b);
		while(k && inSubTree(a,parent[b][k])) k--;
		b = parent[b][k];
	}
	return a;
}


int get_distance(int a,int b){
	return depth[a] + depth[b] - 2*depth[lca(a,b)];
}

pi get_up(int a,int d,int & p){
	pi ret {0,0};
	int k = 0;
	p = a;
	for(;d;){
		while(LSOne(d) != (1 << k)) k++;
		int i = 0;
		ret.xx = mul(ret.xx,base_power[i][1 << k],mod[i]);
		ret.xx = add(ret.xx,parent_hash[a][k][i],mod[i]);
		i = 1;
		ret.yy = mul(ret.yy,base_power[i][1 << k],mod[i]);
		ret.yy = add(ret.yy,parent_hash[a][k][i],mod[i]);
		d ^= LSOne(d);
		p = a = parent[a][k];
	}
	return ret;
}


pi get_hash(int a,int b,int l){
	int p = lca(a,b),aux;
	if(l <= depth[a] - depth[p]) return get_up(a,l,aux);
	pi ret = get_up(a,depth[a] - depth[p],aux);
	l -= depth[a] - depth[p];
	//cerr << ret.xx << " " << ret.yy << endl;
	ret.xx = mul(ret.xx,base_power[0][l],mod[0]);
	ret.yy = mul(ret.yy,base_power[1][l],mod[1]);
	int diff = depth[b] - depth[p];
	diff = diff + 1 - l;
	get_up(b,diff,aux);
	b = aux;
	pi B = mp(Hash[b][0],Hash[b][1]);
	p = parent[p][0];
	pi A = mp(Hash[p][0],Hash[p][1]);
	A.xx = mul(A.xx,base_power[0][l],mod[0]);
	A.yy = mul(A.yy,base_power[1][l],mod[1]);
	B.xx = add(B.xx,-A.xx,mod[0]);
	B.yy = add(B.yy,-A.yy,mod[0]);
	ret.xx = add(ret.xx,B.xx,mod[0]);
	ret.yy = add(ret.yy,B.yy,mod[1]);
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	init();
	scanf("%d",&n);
	scanf("%s",label + 1);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1,0);
	dfs_out[0] = n;
	scanf("%d",&m);
	while(m--){
		int a,b,c,d;
		scanf("%d %d %d %d",&a,&b,&c,&d);
		if(label[a] != label[c]) puts("0");
		else {
			int s = 1,e = min(get_distance(a,b),get_distance(c,d)) + 1;
			while(s < e) {
				int m = s + (e - s + 1)/2;
				if(get_hash(a,b,m) == get_hash(c,d,m)) s = m;
				else e = m - 1;
			}
			printf("%d\n",s);
		}
	}
	return 0;
}
