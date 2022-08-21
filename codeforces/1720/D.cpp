#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using vp = std::vector<pi>;
using ll = long long;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
void tc();
auto test_cases = [](){
	int T; scanf("%d", &T);
	while(T--) tc();
};
using namespace std;


const int MAXD = 32;
int A[1 << 20], n;

int check[4] = {1, 3, 0, 2};

struct node{
	int vals[4];
	node *child[2];
};


int formVal(int i, int ai, int d) {
	i = (i >> d) & 1;
	ai = (ai >> d) & 1;
	return (ai << 1) | i;
}


int getClass(int v) {
	return v == 1 || v == 2;
}

int dfs(node *root, int i, int ai, int d) {
	if(!root) return 0;
	if(d == -1) return 0;
	int v = formVal(i, ai, d);
	return max(root->vals[check[v]], dfs(root->child[getClass(v)], i, ai, d - 1));
}

node* insert(node *root, int i, int ai, int val, int d) {
	if(d == -1) return 0;
	if(!root) root = new node();
	int v = formVal(i, ai, d);
	root->vals[v] = max(root->vals[v], val);
	root->child[getClass(v)] = insert(root->child[getClass(v)], i, ai, val, d - 1);
	return root;
}

void tc() {
	scanf("%d", &n);
	loop(i, n)  {
		scanf("%d", A + i);
	}
	int ans = 0;
	node *root = 0;
	loop(i, n) {
		int v = dfs(root, i, A[i], MAXD - 1) + 1;
		ans = max(ans, v);
		root = insert(root, i, A[i], v, MAXD - 1);
	}
	printf("%d\n", ans);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
