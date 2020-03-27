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

const int MAX = 1 << 20;
const string alphabet = "ACGT";
vector<pi> ans;
ll tot;
int trie[MAX][4], siz;
int E[MAX];
char buffer[MAX];

void insert(int id){
	int cur = 0;
	for(char *p = buffer; *p; p++){
		int c = find(all(alphabet), *p) - alphabet.begin();
		if(!trie[cur][c]) trie[cur][c] = ++siz;
		cur = trie[cur][c];
	}
	if(E[cur]){
		ans.emplace_back(id, E[cur]);
		tot += strlen(buffer);
		E[cur] = 0;
	}
	else E[cur] = id;
}

int dfs(int cur, int d){
	int v = E[cur];
	loop(c, 4) if(trie[cur][c]) {
		int t = dfs(trie[cur][c], d+1);
		if(t && v){
			ans.emplace_back(t, v);
			tot += d;
			v = 0;
		}
		else if(!v) v = t;
	}
	return v;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n; scanf("%d", &n);
	loop(i, n){
		scanf("%s", buffer);
		insert(i+1);
	}
	dfs(0, 0);
	printf("%lld\n", tot);
	for(auto [a, b] : ans) printf("%d %d\n", a, b);
	return 0;
}
