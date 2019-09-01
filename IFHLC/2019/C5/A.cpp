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


int n;
pair<int,string> A[1 << 20];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	PRESTDIO();
	int T;
	cin >> T;
	while(T--) {
		cin >> n;
		map<string,int> M;
		loop(i,n) {
			string s;
			int c;
			cin >> s >> c;
			M[s] += c;
		}
		n = 0;
		for(auto p : M) A[n++] = mp(-p.second,p.first);
		sort(A,A + n);
		cout << n << "\n";
		loop(i,n) cout << A[i].second << " " << -A[i].first << "\n";
	}
	return 0;
}
#endif
