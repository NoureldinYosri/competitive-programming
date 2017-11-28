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


#define rep(i,a,b) for(int i = a;i < b;i++)

const int maxn = 6*100*1000 + 10, maxlg = 20;
pair<pair<int,int>, int> L[maxn];
int P[maxlg+1][maxn], stp, cnt, sa[maxn];
int LCP[maxn],inv_pos[maxn];
struct suffix_array {
	int n;
	suffix_array(){n = 0;}
	suffix_array(const string s) : n(s.size()) {
		rep(i,0,n) P[0][i] = s[i];
		sa[0] = 0;
		for (stp = 1, cnt = 1; cnt < n; stp++, cnt <<= 1) {
			rep(i,0,n) L[i] = {{P[stp-1][i], i + cnt < n ? P[stp-1][i+cnt] : -1}, i};
			std::sort(L, L + n);
			rep(i,0,n)
				P[stp][L[i].second] = i>0 && L[i].first == L[i-1].first ? P[stp][L[i-1].second] : i;
		}
		rep(i,0,n) {
			sa[i] = L[i].second;
			inv_pos[sa[i]] = i;
		}
		loop(i,n - 1) LCP[i] = this->lcp(sa[i],sa[i + 1]);
	}
	int lcp(int x, int y) { // time log(n); x, y = indices into string, not SA
		int k, ret = 0;
		if (x == y) return n - x;
		for (k = stp - 1; k >= 0 && x < n && y < n; k --)
			if (P[k][x] == P[k][y])
				x += 1<<k, y += 1<<k, ret += 1<<k;
		return ret;
	}

};





const int MAX = 300*1000 + 10;
char label[MAX],euler_str[MAX*2];

vi G[MAX];
int depth[MAX],siz[MAX],pref_child[MAX],parent[MAX],n;
int dfs_in[MAX],dfs_out[MAX],dfs_time,forward_dir,backward_dir,backward_memo[MAX];
int heavy_id[MAX],heavy_head[MAX],heavy_siz[MAX],heavy_name;

pi A[40],B[40],C[40];
int lenA,lenB,lenC;


void dfs(int u,int p){
	siz[u] = 1;
	pref_child[u] = -1;
	parent[u] = p;
	depth[u] = depth[p] + 1;

	for(int v : G[u]) if(v != p) {
		dfs(v,u);
		siz[u] += siz[v];
		if(pref_child[u] == -1 || siz[pref_child[u]] < siz[v]) pref_child[u] = v;
	}
}


void hld(int u,int p){
	dfs_in[u] = dfs_time;
	dfs_time++;

	heavy_id[u] = heavy_name;
	if(heavy_siz[heavy_name] == 0) heavy_head[heavy_name] = u;
	heavy_siz[heavy_name]++;

	euler_str[forward_dir++] = label[u];
	if(pref_child[u] != -1) hld(pref_child[u],u);
	int id = heavy_id[u],head = heavy_head[id];
	int offset = dfs_in[u] - dfs_in[head];
	int END = dfs_in[head] + heavy_siz[id] - 1;
	backward_memo[u] = n + END - offset;
	//cerr << u << "th place in backward is " << backward_memo[u] - n << " and in forward is " << dfs_in[u] << "heavy id = " << heavy_name << endl;
	euler_str[backward_memo[u]] = label[u];

	for(int v : G[u]) if(v != p && v != pref_child[u]) {
		heavy_name++;
		hld(v,u);
	}
	dfs_out[u] = dfs_time - 1;
}


int sparse_table[maxn][maxlg],lg[maxn];

void build_sparse_table(){
	int m = 2*n - 1;
	lg[0] = -1;
	loop(i,m) lg[i + 1] = lg[i] + ((i+1) == LSOne(i+1));
	loop(i,m) sparse_table[i][0] = LCP[i];
	for(int k = 0;k + 1 < maxlg;k++)
		for(int i = 0;i < m;i++){
			int j = i + (1 << k);
			if(j >= m) j = i;
			sparse_table[i][k + 1] = min(sparse_table[i][k],sparse_table[j][k]);
		}
}

int get_lcp(int a,int b){
	if(a == b) return 2*n - a;
	a = inv_pos[a];
	b = inv_pos[b];
	if(a > b) swap(a,b);
	b -= 1;
	int l = lg[b - a + 1];
	return min(sparse_table[a][l],sparse_table[b - (1 << l) + 1][l]);
}

ostream& operator << (ostream & st,const pi & a){
	st << "(" << a.xx << " ," << a.yy << ")";
	return st;
}


void get_path(int a,int b,pi *A,int & len){
	len = lenC = 0;
	while(heavy_id[a] != heavy_id[b]) {
		if(heavy_id[a] > heavy_id[b]) {
			int id = heavy_id[a],head = heavy_head[id];
			int from = backward_memo[a],to = backward_memo[head];
			assert(from <= to);
			A[len++] = mp(from,to);
			a = parent[head];
		}
		else{
			int id = heavy_id[b],head = heavy_head[id];
			int from = dfs_in[head],to = dfs_in[b];
			assert(from <= to);
			C[lenC++] = mp(from,to);
			b = parent[head];
		}
	}
	if(a == b) {
		A[len++] = mp(dfs_in[a],dfs_in[a]);
	}
	else if(depth[a] < depth[b]){
		int from = dfs_in[a],to = dfs_in[b];
		assert(from <= to);
		C[lenC++] = mp(from,to);
	}
	else {
		int from = backward_memo[a],to = backward_memo[b];
		assert(from <= to);
		A[len++] = mp(from,to);
	}
	reverse(C,C + lenC);
	loop(i,lenC) A[len++] = C[i];
}

inline int solve(int a,int b,int c,int d){
	int ret = 0;
	int LENGTHA ,LENGTHB;
	get_path(a,b,A,LENGTHA);
	get_path(c,d,B,LENGTHB);
	reverse(A,A + LENGTHA);
	reverse(B,B + LENGTHB);
	while(LENGTHA && LENGTHB){
		int lenA = A[LENGTHA - 1].yy - A[LENGTHA - 1].xx + 1;
		int lenB = B[LENGTHB - 1].yy - B[LENGTHB - 1].xx + 1;
		int len = get_lcp(A[LENGTHA - 1].xx,B[LENGTHB - 1].xx);
		len = min(len,min(lenA,lenB));
		ret += len;
		if(len < lenA && len < lenB) break;
		if(len == lenA) LENGTHA--;
		else A[LENGTHA-1].xx += len;
		if(len == lenB) LENGTHB--;
		else B[LENGTHB-1].xx += len;
	}
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	scanf("%s",label+1);
	loop(i,n-1){
		int a,b;
		scanf("%d %d",&a,&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(1,0);
	hld(1,0);
	/*prArr(heavy_head,heavy_name+1,int);
	prArr(parent+1,n,int);
	prArr(heavy_id+1,n,int);
	prArr(dfs_in+1,n,int);
	prArr(backward_memo+1,n,int);
	*/
	suffix_array(string(euler_str));
	build_sparse_table();

	int m ; scanf("%d",&m);
	while(m--){
		int a,b,c,d;
		scanf("%d %d %d %d",&a,&b,&c,&d);
		printf("%d\n",solve(a,b,c,d));
		//solve(a,b,c,d);
	}

	return 0;
}
