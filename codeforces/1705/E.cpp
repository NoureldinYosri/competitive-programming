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

const int MAX = 200000;
int n, m;
int A[1 << 20];
map<int, int> M;

void insert(int x) {
	auto ptr = M.lower_bound(x);
	if(ptr == M.end() || ptr->second > x) {
		M[x] = x;
		return;
	}
	int r = ptr->first;
	int l = ptr->second;
	M.erase(ptr);
	if(l < x) M[x - 1] = l;
	insert(r + 1);
}

void erase(int x) {
	auto ptr = M.lower_bound(x);
	assert(ptr != M.end());
	int r = ptr->first;
	int l = ptr->second;
	M.erase(r);
	if(l <= x) {
		if(x < r) M[r] = x + 1;
		if(l < x) M[x - 1] = l;
		return;
	}
	if(l < r) M[r] = l + 1;
	M[l - 1] = x;
}

int solve() {
	return M.rbegin()->first + 1;
}

void tc() {
	scanf("%d %d", &n, &m);
	M.clear();
	loop(i, n) {
		scanf("%d", A + i);
		insert(A[i] - 1);
	}
	while(m--) {
		int i, v; scanf("%d %d", &i, &v); i--;
		erase(A[i] - 1);
		A[i] = v;
		insert(A[i] - 1);
		printf("%d\n", solve());
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	tc();
	return 0;
}
