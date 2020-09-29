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


const int MAX = 500*1000 + 10;
int L[MAX], R[MAX];
int n;
vi BIT;

void add(int p, int v){
	for(; p < sz(BIT); p += LSOne(p))
		BIT[p] += v;
}

int query(int p){
	int ret = 0;
	for(; p; p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}

struct dsu{
	vi id, W;
	int m;
	dsu(){}
	dsu(int k){
		m = k;
		id.resize(m);
		W.resize(m);
		iota(all(id), 0);
		fill(all(W), 1);
	}
	int find(int a){
		return id[a] = (a == id[a]) ? a : find(id[a]);
	}
	void join(int a, int b){
		a = find(a), b = find(b);
		if(a == b) return;
		if(W[a] < W[b]) swap(a, b);
		W[a] += W[b];
		id[b] = a;
		m--;
	}
};



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	vp events;
	loop(i, n) {
		scanf("%d %d", L + i, R + i);
		events.emplace_back(L[i], i);
		events.emplace_back(R[i], i);
	}
	BIT.resize(*max_element(R, R + n) + 1);
	
	sort(all(events));

	ll tot = 0;
	for(auto [x, i] : events){
		if(x == L[i]){
			tot += query(R[i] - 1);
			add(R[i], 1);
		} else {
			add(R[i], -1);
		}
	}

	if(tot != n-1){
		puts("NO");
		return 0;
	}
	
	dsu DS(n);
	set<pi> S;
	for(auto [x, i] : events){
		if(x == L[i]){
			for(auto [y, j] : S){
				if(y >= R[i]) break;
				DS.join(i, j);
			}
			S.emplace(R[i], i);
		} else {
			S.erase(pi(R[i], i));
		}
	}
	
	cout << ((DS.m == 1) ? "YES" : "NO") << endl;
	return 0;
}
