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

struct node{
	int val;
	node *l,*r;
	node():val(0),l(0),r(0){}
	node(int x):val(x),l(0),r(0){}
};

node* insert(node *root,int v){
	if(!root) return new node(v);
	if(v < root->val) root->l = insert(root->l,v);
	else root->r = insert(root->r,v);
	return root;
}

int get_depth(node *root){
	if(!root) return 0;
	return max(get_depth(root->l),get_depth(root->r)) + 1;
}

int get_cnt(int n){
	vi V(n);
	loop(i,n) V[i] = i;
	int depth = 0,cnt = 0;
	while((n + 1) > (1 << depth)) depth++;
	//cerr << depth << endl;
	do{
		node *root = 0;
		loop(i,n) root = insert(root,V[i]);
	//	print(V,int);
	//	cerr << get_depth(root) << endl;
		cnt += get_depth(root) <= depth;
	}while(next_permutation(all(V)));
	return cnt;
}

const int MAX = (1 << 20) + 10;
int dp[23][MAX];
int lg[MAX],clg[MAX],mod = 1e9 + 9;
int fact[MAX],rev[MAX];


int C(int n,int k) {
	if(n < k) return 0;
	int ret = fact[n];
	ret = (ret*1LL*rev[k])%mod;
	ret = (ret*1LL*rev[n-k])%mod;
	return ret;
}

int powmod(int x,int p) {
	if(!p) return x%mod;
	int y = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) y = (x*1LL*y)%mod;
		x = (x*1LL*x)%mod;
	}
	return (x*1LL*y)%mod;
}

void preprocess(){
	lg[0] = -1;
	for(int i = 1; i < MAX;i++){
		lg[i] = lg[i - 1] + (i == LSOne(i));
		clg[i] = lg[i];
		if(i != (1 << lg[i])) clg[i]++;
	}
	fact[0] = rev[0] = 1;
	for(int i = 1;i < MAX;i++){
		fact[i] = (fact[i-1] * 1LL * i)%mod;
		rev[i] = powmod(fact[i],mod-2);
		assert((fact[i]*1LL*rev[i])%mod == 1);
	}
	memset(dp,-1,sizeof dp);
}

int getMin(int k) {
	return lower_bound(clg,clg + MAX,k) - clg;
}
int getMax(int k) {
	return upper_bound(clg,clg + MAX,k) - clg;
}


int solve(int k,int n) {
	if(k == -1) return 0;
	if(n == 0) return 1;
	if(n == 1) return k > 0;
	if(k < clg[n+1]) return 0;
//	if(k > clg[n+1]) return dp[k][n] = solve(k-1,n);
	if(dp[k][n] != -1) return dp[k][n];
	int & ret = dp[k][n];
	ret = 0;
	for(int r = 1,L = getMax(k-1);r <= n && r < L ;r++){
		int tmp = (solve(k-1,r-1) *1LL* solve(k-1,n-r))%mod;
		tmp = (tmp * 1LL * C(n-1,r-1))%mod;
		ret += tmp;
		if(ret >= mod) ret -= mod;
	}
	return dp[k][n];
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	preprocess();
/*	for(int i = 1;i <= 10;i++)
		cout << get_cnt(i) << " " << solve(clg[i+1],i) << endl;
*/
	for(int n = 1;n <= 100;n++){
		int m = n + 1;
		if(m == LSOne(m)) cout << n << " " << solve(clg[n+1],n) << endl;
		m++;
		if(m == LSOne(m)) cout << n << " " << solve(clg[n+1],n) << endl;
	}
	return 0;
}
