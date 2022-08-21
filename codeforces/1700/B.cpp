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

char S[1 << 20];
string ans;
int n;

void inc() {
	int i = n - 1;
	while(i >= 0 && ans[i] == '9') {
		ans[i] = '0';
		i--;
	}
	assert(i >= 0);
	ans[i]++;
}

bool check() {
	static vi aux;
	aux.clear();
	int r = 0;
	for(int i = n-1; i >= 0; i--) {
		int a = S[i] - '0', b = ans[i] - '0';
		r += a + b;
		aux.push_back(r%10);
		r = r / 10;
	}
	if(r) {
		aux.push_back(r);
	}
	for(int i = 0; 2*i < sz(aux); i++) {
		if(aux[i] != aux[sz(aux) - 1 - i]) {
			return false;
		}
	}
	return true;
}

void tc() {
	scanf("%d %s", &n, S);
	ans.clear();
	ans.resize(n, '0');
	for(int i = 0; 2*i < n; i++) {
		if(S[i] == S[n - 1 - i]) continue;

		if(S[i] < S[n - 1 - i]) {
			ans[i] = S[n - 1 - i] - S[i] + '0';
		} else {
			ans[n - 1 - i] = S[i] - S[n - 1 - i] + '0';
		}
	}
	if(ans[0] == '0') {
		if(S[n - 1] == '9') {
			if(n == 2) {
				ans = "32";
			} else {
				ans[sz(ans) - 2]--;
			}
		}
		int i = n-1;
		do{
			if(ans[0] == '9') {
				ans[0] = '1';
			} else {
				ans[0]++;
			}
			inc();
		} while(!check());
	}
	puts(ans.c_str());
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
