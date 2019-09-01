#ifdef ACTIVE
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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

string E(string s) {
	string res;
	for(int i = 0;i < sz(s);) {
		int j = i;
		while(j < sz(s) && s[i] == s[j]) j++;
		res.pb(s[i]);
		res += to_string(j - i);
		i = j;
	}
	return res;
}

string D(string s) {
	string res;
	for(int i = 0;i < sz(s);i += 2) {
		char c = s[i];
		int ctr = s[i + 1] - '0';
		loop(j,ctr) res.pb(c);
	}
	return res;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	string c,s;
	cin >> c >> s;
	if(c[0] == 'E') cout << E(s) << endl;
	else cout << D(s) << endl;
	return 0;
}
#endif
