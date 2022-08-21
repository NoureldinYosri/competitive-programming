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

bool vis[1 << 20];
int P[2][1 << 20];
int idx[2][1 << 20], n;

void tc() {
	scanf("%d", &n);
	loop(j, 2) loop(i, n) {
		scanf("%d", &P[j][i]);
		P[j][i]--;
		idx[j][P[j][i]] = i;
	}
	fill(vis, vis + n, false);
	static vi cycles;
	cycles.clear();
	loop(u, n) if(!vis[u]) {
		int v = u;
		int len = 0;
		while(!vis[v]) {
			len++;
			vis[v] = true;
			int i = idx[0][v];
			v = P[1][i];
		}
		cycles.push_back(len);
	}
	sort(cycles.rbegin(), cycles.rend());
	while(!cycles.empty() && cycles.back() == 1) cycles.pop_back();
	reverse(all(cycles));
	int s = 1, e = n;
	static vector<vi> aux;
	aux.clear();
	for(int len : cycles) {
		aux.emplace_back();
		int m = len - (len & 1);
		loop(i, m) {
			if(i & 1) aux.back().push_back(s++);
			else aux.back().push_back(e--);
		}
	}
	loop(i, sz(cycles)) if(cycles[i] & 1) aux[i].emplace_back(s++);
	ll ans = 0;
	for(const vi & p : aux) {
		int prv = p.back();
		for(int x : p) {
			ans += abs(x - prv);
			prv = x;
		}
	}
	printf("%lld\n", ans);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
