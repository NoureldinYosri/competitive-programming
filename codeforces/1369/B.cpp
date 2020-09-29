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
string ans;

void solve(){
	int n = strlen(txt);
	reverse(txt, txt + n);
	ans.clear();
	loop(i, n){
		char c = txt[i];
		if(c == '0') ans.push_back(c);
		else {
			if(ans.empty() || ans.back() == '1') ans.pb(c);
			else {
				while(!ans.empty() && ans.back() == '0') ans.pop_back();
				ans.pb('0');
			}
		}
	}
	reverse(all(ans));
	printf("%s\n", ans.c_str());
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		int n; scanf("%d", &n);
		scanf("%s", txt);
		solve();
	}
	return 0;
}
