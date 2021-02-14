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

const int MAXM = 1e5, MAXB = 18;
vector<vector<array<int, 2>>> tries(MAXM);
vector<vi> vals(MAXM);

void insert(int x, vector<array<int, 2>> & trie, vi & val){
	if(trie.empty()){
		trie.push_back(array<int, 2>({-1, -1}));
		val.push_back(1 << 29);		
	}
	int cur = 0;
	val[cur] = min(val[cur], x);
	for(int b = MAXB-1; b >= 0; b--){
		int v = (x >> b) & 1;
		if(trie[cur][v] == -1) {
			trie[cur][v] = sz(trie);
			trie.push_back(array<int, 2>({-1, -1}));
			val.push_back(1 << 29);
		}
		cur = trie[cur][v];
		val[cur] = min(val[cur], x);
	}
}

int get(int x, int s, const vector<array<int, 2>> & trie, const vi & val){
	if(trie.empty()) return -1;
	if(val[0] + x > s) return -1;
	int cur = 0, y = 0;
	for(int b = MAXB-1; b >= 0; b--){
		int v = (x >> b) & 1;
		int o = v ^ 1;
		int w = v;
		if(trie[cur][o] != -1 && val[trie[cur][o]] + x <= s){
			w = o;
		} 
		y |= w << b;
		cur = trie[cur][w];
		if(cur == -1) return -1;
	}
	if(x + y <= s) return y;
	return -1;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int Q; scanf("%d", &Q);
	while(Q--){
		int t; scanf("%d", &t);
		if(t == 1){
			int x; scanf("%d", &x);
			for(int k = 1; k*k <= x; k++)
				if(x%k == 0){
					insert(x, tries[k], vals[k]);
					if(k*k != x) insert(x, tries[x/k], vals[x/k]);
				}
		} else {
			int x, k, s; scanf("%d %d %d", &x, &k, &s);
			if(x%k){
				puts("-1");
				continue;
			}
			int y = get(x, s, tries[k], vals[k]);
			printf("%d\n", y);
		}
	}
	
	return 0;
}
