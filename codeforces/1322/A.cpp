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

int n;
char S[1 << 20];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %s", &n, S);
	int ans = 0;
	map<char, int> f;
	f['('] = 1;
	f[')'] = -1;
	
	loop(i, n){
		int s = f[S[i]];
		int j = i;
		bool wrong = s < 0;
		while(j+1 < n && s) {
			s += f[S[++j]];
			wrong |= s < 0;
		}
		if(s) {
			puts("-1");
			return 0;
		}
		ans += (j - i + 1)*wrong;
		i = j;
	}


	cout << ans << endl;
	
	return 0;
}
