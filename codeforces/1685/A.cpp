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


int n;
int A[1 << 20], B[1 << 20];

void no() {		
	puts("NO");
}

bool check() {
	loop(i, n) {
		int l = i - 1, r = i + 1;
		if(l < 0) l += n;
		if(r >= n) r -= n;
		bool correct = false;
		if(B[l] < B[i] && B[i] > B[r]) correct = true;
		if(B[l] > B[i] && B[i] < B[r]) correct = true;
		if(!correct) return false;
	}
	return true;
}


bool solveEven() {
	sort(A, A + n);
	multiset<int> MS{A, A + n};
	for(int i = 0; i < n; i += 2) {
		B[i] = *MS.begin();
		MS.erase(MS.begin());
		int low = A[i];
		if(i + 2 < n && *MS.begin() > low) low = *MS.begin();
		auto ptr = MS.upper_bound(low);
		if(ptr == MS.end()) return false;
		B[i + 1] = *ptr;
		MS.erase(ptr);
	}
	return true;
}

bool solveOdd() {
	return false;
}


void tc() {
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	sort(A, A + n);
	if(n & 1) {
		if(!solveOdd()) return no();
	} else {
		if(!solveEven()) return no();
	}
	
	if(!check()) return no();
	puts("YES");
	loop(i, n) printf("%d ", B[i]);
	puts("");
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
