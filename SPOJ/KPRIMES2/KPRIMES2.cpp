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

int floor_sqrt(int n){
	int u = sqrt(n) + 2;
	while(u*u > n) u--;
	return u;
}

int prime_count(int n){
	static vi V;
	static map<int, int> S;
	V.clear();
	S.clear();
	
	int r = floor_sqrt(n);
	for(int i = 1; i <= r; i++) V.push_back(n/i);
	for(int i = V.back() - 1; i > 0; i--) V.push_back(i);
	loop(j, sz(V)) {
		int i = V[j];
		S[i] = i-1;
	}
	for(int p = 2; p <= r; p++){
		if(S[p] > S[p-1]){
			int sp = S[p-1];
			ll p2 = p*(ll)p;
			loop(j, sz(V)){
				int v = V[j];
				if(v < p2) break;
				S[v] -= S[v/p] - sp;
			}
		}
	}
	return S[n];
}


const int MAX = 100000 + 10;
int A[MAX], ord[MAX], ans[MAX];

bool cmp(const int & i, const int & k){
	return A[i] < k;
};

void BS(int s, int e, int *l, int *r){
	if(l >= r) return;
	if(s == e){
		for(; l != r; l++)
			ans[*l] = s;
		return;
	}
	int m = s + (e-s)/2;
	int C = prime_count(m);
	
	int* ptr = lower_bound(l, r, C+1, cmp);
	

	
	BS(s, m, l, ptr);
	BS(m+1, e, ptr, r); 
}

bool cmp2 (const int &a, const int &b){
	return A[a] < A[b];
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
//	int m; scanf("%d", &m);
//	loop(i, m) scanf("%d", A + i), ord[i] = i;
	/*sort(ord, ord + m, cmp2);
	
	BS(2, 1000000000, ord, ord + m);
	
	loop(i, m) printf("%d\n", ans[i]);
	*/
	
	cout << prime_count(1000000000) << endl;
	return 0;
}
