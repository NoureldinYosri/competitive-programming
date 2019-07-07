#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int MAX = 1 << 20;
int trie[MAX][26],E[MAX],siz = 0;
char buffer[MAX];

int createNode(){
	int u = siz++;
	loop(i,26) trie[u][i] = 0;
	E[u] = 0;
	return u;
}

void insert() {
	int L = strlen(buffer);
	reverse(buffer,buffer + L);
	int cur = 0;
	for(int i = 0;i < L;i++) {
		E[cur]++;
		int c = buffer[i] - 'A';
		if(!trie[cur][c]) trie[cur][c] = createNode();
		cur = trie[cur][c];
	}
	E[cur]++;
}


int dfs(int u) {
	int ans = 0;
	loop(c,26) if(trie[u][c]) ans += dfs(trie[u][c]);
	if(u) {
		int r = E[u] - ans;
		if(r >= 2) ans += 2;
	}
	return ans;
}
int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++) {
		siz = 0;
		createNode();
		int n; scanf("%d",&n);
		loop(i,n) {
			scanf("%s",buffer);
			insert();
		}
		printf("Case #%d: %d\n",t,dfs(0));
	}

	return 0;
}
