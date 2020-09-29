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

int n, m, Q;
vi perm, id, W, timestamp;
vi fr, to, usable;
vp queries;
vi readFrom, dead;
vector<vp> cand;

void read(){
	scanf("%d %d %d", &n, &m, &Q);
	readFrom.resize(Q);
	timestamp.resize(n);
	dead.resize(n+1);
	cand.resize(n);
	perm.resize(n);
	id.resize(n);
	W.resize(n);
	fr.resize(m);
	to.resize(m);
	usable.resize(m);
	queries.resize(Q);
	readFrom.resize(Q);
	loop(i, n) {
		scanf("%d", &perm[i]);
		id[i] = i, W[i] = 1;
	}
	loop(e, m){
		scanf("%d %d", &fr[e], &to[e]);
		usable[e] = 1;
		fr[e]--, to[e]--;
	}
	loop(q, Q){
		auto & [t, v] = queries[q];
		scanf("%d %d", &t, &v);
		v--;
		if(t == 1){
		} else {
			usable[v] = 0;
		}
	}
}

int find(int a){
	return (id[a] == a) ? a : find(id[a]);
}

void join(int a, int b, int t){
	a = find(a), b = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a, b);
	W[a] += W[b];
	id[b] = a;
	timestamp[b] = t;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	read();
	fill(all(timestamp), Q);
	loop(e, m) if(usable[e]) join(fr[e], to[e], Q);
	
	for(int q = Q - 1; q >= 0; q--){
		int t = queries[q].first;
		if(t == 1){
			int v = queries[q].second;
			readFrom[q] = find(v);
		} else {
			int e = queries[q].second;
			join(fr[e], to[e], q);
		}
	}
	loop(i, n){
		int a = i;
		int t = Q;
		while(true){
			cand[a].emplace_back(perm[i], t);
			if(a == id[a]) break;
			t = min(t, timestamp[a]);
			a = id[a];
		}
	}
	loop(i, n) sort(all(cand[i]));
	
	loop(q, Q){
		int t = queries[q].first;
		if(t != 1) continue;
		int v = readFrom[q];
		while(!cand[v].empty() && (dead[cand[v].back().first] || cand[v].back().second < q)) cand[v].pop_back();
		int ans = cand[v].empty() ? 0 : cand[v].back().first;
		printf("%d\n", ans);
		dead[ans] = 1;
	}
	return 0;
}
