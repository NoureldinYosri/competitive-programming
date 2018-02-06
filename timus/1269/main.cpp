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

vector<map<char,int> > trie,memo;
vector<short> isCTerminal,isTerminal,fail,depth;

int createNewNode(){
	int u = trie.size();
	trie.emplace_back();
	memo.emplace_back();
	isCTerminal.pb(0);
	isTerminal.pb(0);
	fail.pb(0);
	depth.pb(0);
	return u;
}


void insert(char *iS) {
	string S(iS);
	int cur = 0;
	for (char c : S) {
		if (trie[cur].find(c) == trie[cur].end()) {
			int v = createNewNode();
			depth[v] = depth[cur] + 1;
			trie[cur][c] = v;
//			cerr << cur << " " << v << " " << c << endl;
		}
		cur = trie[cur][c];
	}
	isCTerminal[cur] = 1;
	isTerminal[cur] = 1;
}

int follow(int u,char c) {
	if (memo[u].find(c) != memo[u].end()) return memo[u][c];
	int v = 0;
	if (trie[u].find(c) != trie[u].end())
		v = trie[u][c];
	else if (u > 0)
		v = follow(fail[u],c);
	return memo[u][c] = v;
}


void AhoCorasick(){
	queue<int> q ;
	q.push(0);
	for(;!q.empty();q.pop()) {
		int u = q.front();
		for (auto & p : trie[u])  {
			char c = p.yy;
			int v = trie[u][c];
			int f = follow(fail[u],c);
			if (trie[f][c] != v) f = trie[f][c];
			fail[v] = f;
			isCTerminal[v] = isCTerminal[v] || isCTerminal[f] || isCTerminal[u];
			q.push(v);
		}
	}
}

const int MAX = 1 << 20;
char buffer[MAX];

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	createNewNode();
	fgets(buffer,MAX,stdin);
	int n; sscanf(buffer,"%d",&n);
	loop(i,n){
		fgets(buffer,MAX,stdin);
		buffer[strlen(buffer)-1] = 0;
		insert(buffer);
	}

	fgets(buffer,MAX,stdin);
	int m,u = 0; sscanf(buffer,"%d",&m);
	for(int i = 1;i <= m;i++) {
		u = 0;
		fgets(buffer,MAX,stdin);
		int L = strlen(buffer);
		buffer[--L] = 0;
		for(int j = 1;j <= L;j++) {
			char c = buffer[j - 1];
			u = follow(u,c);
			if(isCTerminal[u]) {
				while(!isTerminal[u]) u = fail[u];
				printf("%d %d\n",i,j - depth[u] + 1);
				return 0;
			}
		}
	}
	puts("Passed");
	return 0;
}
