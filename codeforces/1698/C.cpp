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

ll A[1 << 20];
int n;

void no() {
	puts("NO");
}

bool check(const vector<ll> & B) {
	loop(k, sz(B)) loop(j, k) loop(i, j) {
		ll v = B[i] + B[j] + B[k];
		if(!binary_search(all(B), v))
			return false;
	}
	return true;
}

void tc() {
	scanf("%d", &n);
	loop(i, n) scanf("%lld", A + i);
	sort(A, A + n);
	int cnt[3] = {0, 0, 0};
	loop(i, n) {
		if(A[i] < 0) cnt[0]--;
		else if(A[i] == 0) cnt[1]++;
		else cnt[2]++;
	}
	if(max(cnt[0], cnt[2]) >= 3) return no();
	if(max(cnt[0], cnt[2]) == 2 && cnt[1]) return no();
	static vector<ll> B;
	B.clear();
	loop(i, n) if(A[i] != 0) B.push_back(A[i]);
	for(int i = 0; i < 3 && i < cnt[1]; i++) B.push_back(0);
	sort(all(B));
	puts(check(B) ? "YES" : "NO");
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
