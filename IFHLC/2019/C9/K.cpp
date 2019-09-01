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


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> s;
	int n = sz(s);
	int ans = 0;
	for(int lenA = 1;lenA < n;lenA++)
		for(int lenB = 1;lenA + lenB < n;lenB++) {
			for(int s = 0;s < n;s++) {
				string a,b,c;
				int p = s;
				for(int i = 0;i < lenA;i++,p = (p+1)%n)
					a.push_back(::s[p]);
				for(int i = 0;i < lenB;i++,p = (p+1)%n)
					b.push_back(::s[p]);
				int lenC = n - lenA - lenB;
				for(int i = 0;i < lenC;i++,p = (p+1)%n)
					c.push_back(::s[p]);
				if(a+b > c && b+c > a && c+a > b){
					cout << a << " " << b << " " << c << endl;
					ans++;
				}
			}
		}
	cout << ans << endl;
	return 0;
}
#endif
