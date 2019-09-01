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


string s;

int lst[128];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> s;
	int n = sz(s);
	pi best(-1,-1);
	for(int c = '0';c <= '9';c++) lst[c] = n;
	bool f = 0;
	for(int i = n-1;i >= 0 && !f;i--) {
		for(int c = s[i] - 1;c >= '0' + (i==0);c--){
			if(lst[c] < n) {
				best = pi(i,lst[c]);
				f = 1;
				break;
			}
		}
		lst[s[i]] = i;
	}
	if(!f) puts("-1");
	else {
		swap(s[best.first],s[best.second]);
		cout << s << endl;
	}
	return 0;
}
#endif
