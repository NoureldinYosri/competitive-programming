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

const int MAX = 300*1000 + 10, oo = MAX;
int n, m;
list<int> which[MAX], who[MAX];
char S[MAX];
bool alive[MAX];
int id[MAX], W[MAX], cnt[MAX];
vi G[MAX];
int visID[MAX], visNum;

int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}

void join(int a, int b){
	a = find(a), b = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a, b);
	W[a] += W[b];
	cnt[a] = min(cnt[a] + cnt[b], oo);
	id[b] = a;
	who[a].splice(who[a].end(), who[b]);
}

void dfs(int u, int c, int *ctr){
	if(visID[u] == visNum) return;
	visID[u] = visNum;
	ctr[c] += cnt[u];
	ctr[c] = min(ctr[c], oo);
	for(int v : G[u]) {
		int t = find(v);
		if(visID[t] == visNum) continue;
		dfs(t, c^1, ctr);
	//	cerr << u << " " << t << endl;
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	scanf("%s", S);
	loop(i, m) {
		int k; scanf("%d", &k);
		while(k--){
			int x; scanf("%d", &x);
			x--;
			who[i].pb(x);
			which[x].pb(i);
		}
		id[i] = i;
		W[i] = 1;
		cnt[i] = 1;
	}
	loop(i, n){
		if(S[i] == '1'){
			if(!which[i].empty()){
				int a = *which[i].begin();
				int b = *which[i].rbegin();
				if(a == b) cnt[find(a)] = oo;
				else join(a, b);
			}
		}
		for(int k : which[i]) alive[find(k)] |= S[i] == '0';
//		if(sz(which[i]) == 1) which[i].pb(m);
		if(sz(which[i]) == 2){
			int a = find(*which[i].begin());
			int b = find(*which[i].rbegin());
			if(a != b){
				G[a].pb(b);
				G[b].pb(a);				
			}
		}
		visNum++;
		int ans = 0;
		loop(j, m) if(j == find(j) && alive[j] && visID[j] != visNum){
			int ctr [] = {0, 0};
			dfs(j, 0, ctr);
		//	prArr(ctr, 2, int);
			int a = min(ctr[0], ctr[1]);
			int b = max(ctr[0], ctr[1]);
			if(a) ans += a;
			else ans += b;
		}
		printf("%d\n", ans);
	}
	return 0;
}
