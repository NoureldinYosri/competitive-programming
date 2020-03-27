#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;


const int MAX = 1 << 10, MAXT = 400*1000 + 10;
char Patt[MAX], txt [MAXT];
int trie[MAX][14], siz;
int n, m;
ll cost[MAX];

void insert(int c){
	int cur = 0;
	for(char *p = Patt; *p; p++){
		int chr = *p - 'a';
		if(!trie[cur][chr]) trie[cur][chr] = ++siz;
		cur = trie[cur][chr];
	}
	cost[cur] += c;
}

int go_to[MAX][14], fail[MAX];

int follow(int u, int c){
	int & ret = go_to[u][c];
	if(ret != -1) return ret;
	if(trie[u][c]) return ret = trie[u][c];
	else if(!u) return ret = 0;
	else return ret = follow(fail[u], c);
}

void aho_corasick(){
	queue<int> q;
	memset(go_to, -1, sizeof go_to);
	for(int c = 0; c < 14; c++)
		if(trie[0][c]){
			int u = trie[0][c];
			q.push(u);
			fail[u] = 0;
		}
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int c = 0; c < 14; c++) if(trie[u][c]){
			int v = trie[u][c];
			fail[v] = follow(fail[u], c);
			cost[v] += cost[fail[v]];
			q.push(v);
		}
	}
}


map<int, pair<pi, ll> > mem[MAXT];

pair<pi, ll> walk(int i, int u){
	if(mem[i].count(u)) return mem[i][u];
	int j = i, v = u;
	ll res = 0;
	while(i < n && txt[i] != '?'){
		u = follow(u, txt[i] - 'a');
		res += cost[u];
		i++;
	}
//	cerr << j << " " << v << " -> " << i << " " << u << " " << res << endl;
	return mem[j][v] = mp(pi(i, u), res);
}


vi I;
ll dp[1 << 14][MAX];
bool vis[1 << 14][MAX];

ll solve(int msk, int u){
	int cur = msk ? popcnt(msk) : 0;
	if(cur == sz(I)) return walk(I.back()+1, u).second;
	ll & ret = dp[msk][u];
	if(vis[msk][u]) return ret;
	vis[msk][u] = 1;
	
	int i = (cur ? I[cur-1] : -1) + 1;
	auto aux = walk(i, u);
	u = aux.first.second;
	
	ret = -(1LL << 60);
	loop(c, 14) if(!((msk >> c) & 1)){
		int v = follow(u, c);
		ll tmp = solve(msk ^ (1 << c), v) + aux.second + cost[v];
		//if(msk == ((1 << sz(I)) - 1)) 
		//	cerr << u << " -" << (char)(c + 'a') << "- " << v << " " << tmp << " " << aux.second << " " << cost[v] << endl; 
		ret = max(ret, tmp);
	}	
//	cerr << msk << " " << u << " || " << ret << " " << aux.second << endl;
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &m);
	while(m--){
		int c; scanf("%s %d", Patt, &c);
		insert(c);
	}
	aho_corasick();
	scanf("%s", txt);
	n = strlen(txt);

	loop(i, n) if(txt[i] == '?') I.pb(i);
	
	if(I.empty()) {
		cout << walk(0, 0).second << endl;
		return 0;
	}

	cout << solve(0, 0) << endl;
	
	
	return 0;
}
