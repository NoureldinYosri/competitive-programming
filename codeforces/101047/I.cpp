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

vi id, W;
vi fr, to, cost, used;
int N, M, Q;
vector<pair<int*, int>> hist;

void init(){
	fr.clear(); to.clear(); cost.clear();
	used.clear();
	used.resize(M + Q);
	fr.resize(M + Q);
	to.resize(M + Q);
	cost.resize(M + Q);
	
	
	id.clear(); W.clear();
	id.resize(N);
	W.resize(N);
	fill(all(W), 1);
	iota(all(id), 0);
}

void replace(int *ptr, int v){
	hist.emplace_back(ptr, *ptr);
	*ptr = v;
}

int find(int a){
	if(id[a] == a) return a;
	int p = find(id[a]);
	replace(&id[a], p);
	return id[a];
}
void join(int a, int b){
	a = find(a) , b = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a, b);
	replace(&id[b], a);
	replace(&W[a], W[a] + W[b]);
}
bool areConnect(int a, int b){
	return find(a) == find(b);
}
void revert(int checkpoint){
	while(sz(hist) > checkpoint){
		auto [ptr, v] = hist.back(); hist.pop_back();
		*ptr = v;
	}
}

void init(const vi & E){
	for(int e : E) {
		int a = fr[e] , b = to[e];
		id[a] = a, id[b] = b;
		W[a] = W[b] = 1;
		used[e] = 0;
	}
}

ll kruskal(const vi & A, const vi & B, vi *R){
	if(R) {
		hist.clear();
		R->clear();
	}
	ll ret = 0;
//	print(A, int);
//	print(B, int);
	for(int i = 0, j = 0; i < sz(A) || j < sz(B); ){
		int e = -1;
		if(i < sz(A) && j < sz(B)){
			if(cost[A[i]] <= cost[B[j]]){
				e = A[i++];
			} else {
				e = B[j++];
			}
		} else if(i < sz(A)){
			e = A[i++];
		} else {
			e = B[j++];
		}
		if(!areConnect(fr[e], to[e])){
//			cerr << mp(e, mp(pi(fr[e], to[e]), cost[e])) << " ";
			join(fr[e], to[e]);
			used[e] = 1;
			ret += cost[e];
			if(R) R->push_back(e);
		}
	}
//	cerr << endl;
	return ret;
}


void tc(){
	static vi ord;
	scanf("%d %d %d", &N, &M, &Q);
	init();
	ord.clear();
	loop(e, M) {
		ord.pb(e);
		scanf("%d %d %d", &fr[e], &to[e], &cost[e]);
		fr[e]--, to[e]--;
	}
	loop(q, Q){
		int e = q + M;
		scanf("%d %d %d", &fr[e], &to[e], &cost[e]);		
		fr[e]--, to[e]--;
	}
	
	
	sort(all(ord), [](const int & a, const int & b){
		return cost[a] < cost[b];
	});
	static vi MST, aux, newMST, empty, classes[2]; 
	MST.clear(); aux.clear(), newMST.clear();
	
	init(ord);
	kruskal(ord, empty, &MST);
		
	int B = sqrt(Q + M + N);
	for(int b = 0; b*B < Q; b++) {
		aux.clear();
		for(int s = b*B, e = min(Q, b*B + B); s < e; s++){
			aux.pb(s + M);
		}
		sort(all(aux), [](const int & a, const int & b){
			return cost[a] < cost[b];
		});
		init(MST);
		init(aux);
		kruskal(MST, aux, &newMST);
		loop(c, 2) classes[c].clear();
		for(int e : MST) classes[used[e]].pb(e);
		init(MST);
		init(aux);
		hist.clear();
		ll tot = kruskal(classes[1], empty, NULL);
		aux.clear();
		for(int s = b*B, e = min(Q, b*B + B); s < e; s++){
			aux.pb(s + M);
			sort(all(aux), [](const int & a, const int & b){
				return cost[a] < cost[b];
			});
			int checkpoint = sz(hist);
			ll ans = tot + kruskal(classes[0], aux, NULL);
			revert(checkpoint);
			printf("%lld\n", ans);
		}
		MST.swap(newMST);
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
