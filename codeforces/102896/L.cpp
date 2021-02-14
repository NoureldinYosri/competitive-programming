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

const int MAXN = 2e5 + 10, MAXM = MAXN;
int n, m;
int leftChild[MAXN], rightChild[MAXN], val[MAXN];
int min_val[MAXN], max_val[MAXN];
int L[MAXM], R[MAXM], ans[MAXM];
vector<vi> beg, queries;

void dfs(int u){
	if(!u) return;
	dfs(leftChild[u]);
	dfs(rightChild[u]);
	min_val[u] = max_val[u] = val[u];
	if(leftChild[u]) min_val[u] = min_val[leftChild[u]];
	if(rightChild[u]) max_val[u] = max_val[rightChild[u]];
//	cerr << u << ": " << min_val[u] << " " << max_val[u] << endl;
}

vi BIT;

void add(int p, int v){
	for(++p; p < sz(BIT); p += LSOne(p))
		BIT[p] += v;
}
int get(int p){
	int ret = 0;
	for(++p; p > 0; p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	vi aux;
	for(int i = 1; i <= n; i++){
		scanf("%d %d %d", leftChild + i, rightChild + i, val + i);
		aux.push_back(val[i]);
	}
	scanf("%d", &m);
	loop(q, m) {
		scanf("%d %d", L + q, R + q);
		aux.push_back(L[q]);
		aux.push_back(R[q]);
	}
	sort(all(aux));
	aux.resize(unique(all(aux)) - aux.begin());
	for(int i = 1; i <= n; i++) val[i] = lower_bound(all(aux), val[i]) - aux.begin();
	loop(q, m){
		L[q] = lower_bound(all(aux), L[q]) - aux.begin();
		R[q] = lower_bound(all(aux), R[q]) - aux.begin();
	}
	beg.resize(sz(aux));
	queries.resize(sz(aux));
//	prArr(L, m, int);
//	prArr(R, m, int);

	dfs(1);
	vi mins, maxs;
	for(int i = 1; i <= n; i++){
		beg[max_val[i]].push_back(min_val[i]);
		mins.push_back(min_val[i]);
		maxs.push_back(max_val[i]);
	}
	sort(all(mins));
	sort(all(maxs));
	
	loop(q, m){
		ans[q] = n;
		ans[q] -= lower_bound(all(maxs), L[q]) - maxs.begin();
		ans[q] -= mins.end() - upper_bound(all(mins), R[q]);
		queries[R[q]].push_back(q);
	}
	
	BIT.resize(2*sz(aux), 0);
	int cnt = 0;
	loop(x, sz(aux)) {
		for(int b : beg[x]){
//			cerr << "insert " << b << " " << x << endl;
			add(b, 1);
			cnt++;
		}
		for(int q : queries[x]) {
//			cerr << "there are " << cnt - get(L[q] - 1) << " in range " << L[q] << " " << R[q] << " ... " << get(L[q] - 1) << endl;
			ans[q] -= cnt - get(L[q] - 1);
		}
	}
	loop(q, m) {
		ans[q] = 2*ans[q] + 1;
		printf("%d\n", ans[q]);
	}
	return 0;
}
