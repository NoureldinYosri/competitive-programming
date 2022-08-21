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


vi nums[4];
vp ans;

int pop(vi & V) {
	int r = V.back();
	V.pop_back();
	return r;
}

void no() {
	puts("NO");
}

void yes() {
	puts("YES");
	for(auto [a, b] : ans) 
		printf("%d %d\n", a, b);
}

void solve0(int n, int _) {
	while(sz(nums[2]) > 1) {
		int a = pop(nums[2]);
		int b = pop(nums[2]);
		ans.emplace_back(a, b);
	}
	for(int r = 1; r < 4; r++) {
		while(!nums[r].empty()){
			if(nums[0].empty()) return no();
			int a = pop(nums[0]);
			int b = pop(nums[r]);
			ans.emplace_back(a, b);
		}
	}
	while(!nums[0].empty()) {
		int a = pop(nums[0]);
		int b = pop(nums[0]);
		ans.emplace_back(a, b);
	}
	yes();
}

void solve1(int n, int k) {
	cerr << "k = " << k << endl;
	int r = (6 - k)%4;
	if(r == 2) {
		while(sz(nums[r]) > 1) {
			ans.emplace_back(pop(nums[r]), pop(nums[r]));
			// cerr << ans.back() << endl;
		}

	} else if(r) {
		while(!nums[r].empty() && !nums[2].empty()) {
			ans.emplace_back(pop(nums[r]), pop(nums[2]));
		}
	}
	r = 4 - k;
	loop(r2, 4) if(r2 && r2 != r) {
		while(!nums[r].empty() && !nums[r2].empty()) {
			ans.emplace_back(pop(nums[r]), pop(nums[r2]));
		}
	}
	while(sz(nums[r]) > 1) {
		ans.emplace_back(pop(nums[r]), pop(nums[r]));
	}
	for(r = 1; r < 4; r++) {
		while(!nums[r].empty() && !nums[0].empty()) {
			ans.emplace_back(pop(nums[r]), pop(nums[0]));
		}
	}
	while(sz(nums[0]) > 1) {
		ans.emplace_back(pop(nums[0]), pop(nums[0]));
	}
	if(sz(ans) != (n >> 1)) return no();
	yes();
}


function<void(int, int)> solver[] = {solve0, solve1};


void tc() {
	int n, k; scanf("%d %d", &n, &k);
	loop(r, 4) nums[r].clear();
	ans.clear();
	for(int i = 1; i <= n; i++)
		nums[i%4].push_back(i);
	return solver[k%4 != 0](n, k%4);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
