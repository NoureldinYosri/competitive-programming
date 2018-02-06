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

const int MAX = 1 << 20;
int trie[MAX][128],id[MAX],siz;
vector<char> children[MAX];
char txt[40];
bool isTerminal[MAX];
bool vis[MAX];
map<vi,int> M;

void clean(){
	M.clear();
	loop(i,siz + 1){
		for(char c : children[i])
			trie[i][c] = 0;
		children[i].clear();
		isTerminal[i] = 0;
	}
	siz = 0;
}

void insert() {
	int cur = 0;
	for(char *p = txt;*p;p++) {
		if(!trie[cur][*p]) {
			children[cur].pb(*p);
			trie[cur][*p] = ++siz;
			id[siz] = siz;
		}
		cur = trie[cur][*p];
	}
	isTerminal[cur] = 1;
}

int solve(int root = 0){
	vi V(27,-1);
	V.back() = isTerminal[root];
	for(int i = 0;i < 26;i++)
		if(trie[root][i + 'a'])
			V[i] = solve(trie[root][i + 'a']);
	if(M.find(V) == M.end()) {
		int s = sz(M);
		M[V] = s;
	}
	return M[V];
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int n;
	while(scanf("%d",&n) == 1){
		loop(i,n){
			scanf("%s",txt);
			insert();
		}
		solve();
		printf("%d\n",sz(M));
		clean();
	}
	return 0;
}
