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


string S;

int cnt[26];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> S;
	for(char c : S) cnt[c - 'a']++;
	int odd_cnt = 0, even_cnt = 0;
	loop(c, 26) {
		odd_cnt += cnt[c] & 1;
		if(cnt[c]) even_cnt += 1 - (cnt[c] & 1);
	}
	if(odd_cnt > 1 || even_cnt == 1 || sz(S) == 1) {
		puts("Impossible");
		return 0;
	}
	
	string Z(S);
	reverse(all(Z));
	if(S == Z){
		printf("%d\n", 1 + (sz(S)%2));
		return 0;
	}
	
	int odd_char = -1;
	loop(c, 26) if(cnt[c]&1) odd_char = c;
	
	if(odd_char != -1){
		
	}
	
	return 0;
}
