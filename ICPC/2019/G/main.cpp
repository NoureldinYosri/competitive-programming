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
int n,Q;
int fr[MAX],to[MAX];
char letter[MAX];
vi E[MAX];
char buffer[MAX];
int trie[MAX][26],fail[MAX],cnt[MAX],m;
vi G[MAX];
int End[MAX],ans[MAX];
int match[MAX];
vi fchild[MAX];



int insert() {
	int L = strlen(buffer);
	reverse(buffer,buffer + L);
//	cerr << "insert " << buffer << endl;
	int cur = 0;
	loop(i,L){
		int c = buffer[i] - 'A';
		if(!trie[cur][c]) {
			trie[cur][c] = ++m;
			G[cur].push_back(c);
		}
		cur = trie[cur][c];
	}
	return cur;
}

int mem[MAX][26];

int getNxt(int f,int c){
	int & ret = mem[f][c];
	if(ret != -1) return ret;
	ret = 0;
	if(trie[f][c]) return ret = trie[f][c];
	else if(f != fail[f]) return ret = getNxt(fail[f],c);
	else return ret = 0;
}

void AhoCorasick(){
	queue<int> q;
	for(int c : G[0]) {
		int v = trie[0][c];
		q.push(v);
		fail[v] = 0;
	}
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int c : G[u]) {
			int v = trie[u][c];
			fail[v] = getNxt(fail[u],c);
			q.push(v);
		}
	}
}

void solve(int txt,int patt) {
	match[patt]++;
	for(int e : E[txt]) {
		int v = to[e],c = letter[e] - 'A';
		int t = getNxt(patt,c);
		solve(v,t);
	}
}

void dfs(int u) {
	for(int v : fchild[u]){
		dfs(v);
		match[u] += match[v];
	}
}

void getAnswer(){
	for(int i = 0;i <= m;i++)
		if(fail[i] != i)
			fchild[fail[i]].push_back(i);
	dfs(0);
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	memset(mem,-1,sizeof mem);
	scanf("%d %d",&n,&Q);
	for(int i = 1;i <= n;i++) {
		scanf(" %c %d",letter + i,fr + i);
		to[i] = i;
		E[fr[i]].push_back(i);
//		cerr << "\t" << fr[i] << " " << i << " " << letter[i] << endl;
	}
	loop(i,Q) {
		scanf("%s",buffer);
		End[i] = insert();
	}
	AhoCorasick();
	solve(0,0);
	getAnswer();
	loop(q,Q) printf("%d\n",match[End[q]]);
	return 0;
}
