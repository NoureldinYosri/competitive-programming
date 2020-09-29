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

char txt[1 << 20];
int n, K;
map<char, int> cnt;
string ans;

void solve(){
	static string aux;
	ans.clear();
	aux.clear();
	for(auto [c, s] : cnt){
		if(s%K == 0){
			s /= K;
			loop(i, s) ans.pb(c);
		}
		else break;
	}
	for(char c : ans) cnt.erase(c);
	
	if(cnt.empty()) return;
	
	static vp tmp;
	tmp.clear();
	int sum = 0;
	for(auto [c, s] : cnt){
		sum += s;
		tmp.emplace_back(c, s);
		if(sum >= K) break;
	}
	
	int ctr = 1;
	if(sz(tmp) == 1){
		if(sz(ans) > 1){
			loop(i, K-1) ans.pb(ans.back());
		}
		else ctr = (tmp.back().second + K - 1)/K;

	}
	else {
		
	}
		
	loop(i, ctr)
		ans.pb(tmp.back().first);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		cnt.clear();
		scanf("%d %d %s", &n, &K, txt);
		loop(i, n) cnt[txt[i]]++;
		solve();
		printf("%s\n", ans.c_str());
	}
	return 0;
}
