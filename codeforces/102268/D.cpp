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

const int MAX = 300*1000 + 10;
int n, m;
int A[MAX];
ll pref[MAX];
int L[MAX], R[MAX], value[MAX], ord[MAX];
map<int, pi> LeftEnd;
int BIT[MAX];

void add(int p, int v){
	for(; p <= m; p += LSOne(p))
		BIT[p] += v;
}
int get(int p){
	int ret = 0;
	for(; p; p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}

int getContainer(int x){
	auto ptr = LeftEnd.lower_bound(x);
	if(ptr == LeftEnd.end()) return -1;
	if(x < (ptr->second.first)) return -1;
	return ptr->first;
}





int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	for(int d = 1; d <= m; d++) {
		scanf("%d", A + d);
		pref[d] = A[d] + pref[d-1];
	}
	loop(i, n){
		scanf("%d %d %d", L + i, R + i, value + i);
		ord[i] = i;
	}
	sort(ord, ord + n, [](const int & a, const int & b){
		if(value[a] != value[b]) return value[a] > value[b];
		return a < b;
	});
	static vi aux;
	ll ans = 0;
	loop(q, n){
		int i = ord[q];
		int l = L[i], r = R[i];
		int R1 = getContainer(l);
		int R2 = getContainer(r);
		if(R2 == -1) R2 = r;
		ll have = pref[R2];
		if(R1 == -1) R1 = R2;
		
		if(LeftEnd.count(R1)) have -= pref[LeftEnd[R1].first - 1];
		
		int c = get(R2) - get(R1 - 1);
		if(have > c){
			int L = l;
			if(LeftEnd.count(R1)) L = LeftEnd[R1].first;
			
			for(auto ptr = LeftEnd.lower_bound(R1); ptr != LeftEnd.end() && ptr->first <= R2; ptr++)
				aux.pb(ptr->first);
			for(int x : aux) {
				add(x, -LeftEnd[x].second);
				LeftEnd.erase(x);
			}
			aux.clear();
			
			c++;
			LeftEnd[R2] = pi(L, c);
			add(R2, c);
			ans += value[i];
		}
		cerr << "after " << L[i] << " " << R[i] << " " << value[i] << endl;
		for(auto p : LeftEnd) cerr << p << " ";
		cerr << endl;
	}
	printf("%lld\n", ans);
	return 0;
}
