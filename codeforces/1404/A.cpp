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

int n, k;
char txt[1 << 20];

void tc(){
	scanf("%d %d %s", &n, &k, txt);
	if(k & 1){
		puts("NO");
		return;
	}
	int cnt[2] = {0};
	for(int i = 0; i < k; i++){
		bool has[2] = {false, false};
		for(int j = i; j < n; j += k){
			if(txt[j] != '?') {
				has[txt[j] - '0'] = true;
			}
		}
		if(has[0] && has[1]) {
			puts("NO");
			return;
		}
		loop(c, 2) cnt[c] += has[c];
	}
	puts(max(cnt[0], cnt[1]) <= (k >> 1) ? "YES" : "NO");	
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
