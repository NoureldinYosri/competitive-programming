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

const int MAXN = 300*1000 + 10;
const int mod = 998244353;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}
vi Fact(MAXN, 1), InvInt(MAXN, 1), InvFact(MAXN, 1);
vi lg(1 << 20);
void init(){
	for(int i = 2; i < MAXN; i++) InvInt[i] = mod - mul(mod/i, InvInt[mod%i]);
	for(int i = 1; i < MAXN; i++) {
		Fact[i] = mul(Fact[i-1], i);
		InvFact[i] = mul(InvFact[i-1], InvInt[i]);
	}
	loop(i, 20) lg[1 << i] = i;
}
int C(int n, int k){
	if(k > n) return 0;
	return mul(Fact[n], mul(InvFact[k], InvFact[n-k]));
} 

int n, sn;
int f[MAXN], L[MAXN], R[MAXN], id[MAXN];
bool isSpecial[MAXN], isVis[MAXN];
vi hateList[MAXN];
vi special;

void dfs(int u){
	special.pb(u);
	isVis[u] = true;
	for(int v : hateList[u]) if(!isVis[v]) dfs(v);
}

map<pair<int, pi>, int> work(){
	int m = sz(special);
	vi hate(m, 0);
	loop(i, m) id[special[i]] = i;
	loop(i, m){
		int a = special[i];
		for(int b : hateList[a]) hate[i] |= 1 << id[b];
	}
	map<pair<int, pi>, int> res;
	loop(msk, (1 << m)){
		int bad = 0, l = 1, r = n, s = 0;
		loop(i, m) if((msk >> i) & 1) {
			s++;
			int a = special[i];
			l = max(l, L[a]);
			r = min(r, R[a]);
			bad |= hate[i];
		}
		if(l <= r && (bad & msk) == 0) {
			res[mp(s, pi(l, r))]++;
		}
	}
	return res;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	int q; scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++) scanf("%d %d", L + i, R + i);
	for(int r = 0; r < q; r++){
		int a, b; scanf("%d %d", &a, &b);
		hateList[a].pb(b);
		hateList[b].pb(a);
		isSpecial[a] = isSpecial[b] = true;
	}
	map<pair<int, pi>, int> tot;
	tot[mp(0, pi(1, n))] = 1;
	for(int i = 1; i <= n; i++) if(isSpecial[i] && !isVis[i]) {
		special.clear();
		dfs(i);
		map<pair<int, pi>, int> aux;
		tot.swap(aux);
		for(auto [one, c1] : work()){
//			cerr << "{" << one << ": " << c1 << "} ";
			for(auto [another, c2] : aux){
				auto [s1, p] = one;
				auto [s2, q] = another;
				int l = max(p.first, q.first);
				int r = min(p.second, q.second);
				if(l > r) continue;
				pair<int, pi> info(s1 + s2, pi(l, r));
				tot[info] = add(tot[info], mul(c1, c2));
			}
		}
//		cerr << endl;
	}
	vi In(n + 1, 0), Out(n + 1, 0);
	for(int i = 1; i <= n; i++) if(!isSpecial[i]) {
		In[L[i]]++;
		Out[R[i]]++;
	}
	vector<vector<int>> I(n + 1, vi(41, 0)), O(n + 1, vi(41, 0));
	for(auto [info, cnt] : tot){
		auto [s, p] = info;
		auto [l, r] = p;
		I[l][s] = add(I[l][s], cnt);
		O[r][s] = add(O[r][s], cnt);
	}
//	print(In, int);
//	print(Out, int);
	int ans = 0;
	vi freq(41, 0);
	for(int s = 1, ctr = 0; s <= n; s++){
		for(int k = 0; k <= 40; k++) freq[k] = add(freq[k], I[s][k]);
		ctr += In[s];
		int tmp = 0;
		for(int k = 0; k <= 40 && k <= s; k ++){
			tmp = add(tmp, mul(freq[k], C(ctr, s - k)));
		}
//		cerr << s << ": " << tmp << endl;
		ans = add(ans, tmp);
		ctr -= Out[s];
		for(int k = 0; k <= 40; k++) freq[k] = add(freq[k], -O[s][k]);
	}
	cout << ans << endl;
	return 0;
}
