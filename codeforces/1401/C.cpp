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

int n;
int A[1 << 20];

struct DS{
	vi id, W;
	DS(){}
	DS(int m){
		id.resize(m);
		W.resize(m);
		fill(all(W), 1);
		iota(all(W), 0);
	}
	int find(int a) {return id[a] = (a == id[a]) ? a : find(id[a]);};
	void join(int a, int b){
		a = find(a), b = find(b);
		if(a == b) return;
		if(W[a] < W[b]) swap(a, b);
		W[a] += W[b];
		id[b] = a;
	}
};

bool tc(){
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	if(is_sorted(A, A + n)) return true;
	int d = *min_element(A, A + n);
	static vi D;
	loop(i, n) if(A[i]%d == 0){
		D.pb(A[i]/d);
	}
	sort(all(D));
	D.resize(unique(all(D)) - D.begin());
	
	
	DS dsu(sz(D));
	vi B{A, A + n};
	sort(all(B));
	
	
	loop(i, n) if(A[i]%d == 0 && B[i]%d == 0 && __gcd(A[i], B[i]) == d) {
		int a = A[i]/d, b = B[i]/d;
		a = lower_bound(all(D), a) - D.begin();
		b = lower_bound(all(D), b) - D.begin();
		dsu.join(a, b);
	}


	
	vector<list<int>> IDX(sz(D));
	loop(i, n) if(A[i]%d == 0){
		int k = A[i]/d;
		k = lower_bound(all(D), k) - D.begin();
		k = dsu.find(k);
		IDX[k].pb(i);
	}
	
	
	
	loop(i, sz(D)){
		vi aux{all(IDX[i])};
		for(int & x : aux) x = A[x];
		sort(all(aux));
		int j = 0;
		for(int pos : IDX[i])
			A[pos] = aux[j++];
	}
	
	return is_sorted(A, A + n);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) puts(tc() ? "YES" : "NO");
	return 0;
}
