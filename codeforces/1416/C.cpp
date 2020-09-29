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

const int MAXB = 30, MAXN = 300*1000 + 10;
ll cnt[MAXB][2];
int A[MAXN], n;
vector<array<int, 2>> trie(1, array<int, 2>{-1, -1});
vector<vi> content(1, vi());

void insert(int x, int i){
	int cur = 0;
	for(int b = MAXB-1; b >= 0; b--){
		int c = (x >> b) & 1;
		if(trie[cur][c] == -1){
			trie[cur][c] = sz(trie);
			trie.emplace_back();
			fill(all(trie.back()), -1);
			content.emplace_back();
		}
		cur = trie[cur][c];
		content[cur].push_back(i);
	}
	
}

ll getInv(const vi & L, const vi & R){
	assert(is_sorted(all(L)));
	assert(is_sorted(all(R)));
	int i = 0;
	ll ret = 0;
	for(int l : L){
		while(i < sz(R) && R[i] < l) i++;
		ret += i;
	}
	return ret;
}

void dfs(int cur, int b){
	if(cur == -1 || b == -1) return;
	dfs(trie[cur][0], b - 1);
	dfs(trie[cur][1], b - 1);
	int l = trie[cur][0], r = trie[cur][1];
	if(min(l, r) == -1) return;
	ll tmp = getInv(content[l], content[r]);
	ll tot = sz(content[l])*(ll)sz(content[r]);
	cnt[b][0] += tmp;
	cnt[b][1] += tot - tmp;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif

	scanf("%d", &n);
	loop(i, n) {
		scanf("%d", A + i);
		insert(A[i], i);
	}
	dfs(0, MAXB-1);
	ll res = 0;
	int x = 0;
	loop(b, MAXB){
		int c = cnt[b][1] < cnt[b][0];
		res += cnt[b][c];
		x |= c << b;
	}
	cout << res << " " << x << endl;
	return 0;
}
