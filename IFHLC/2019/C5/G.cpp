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


char A[1 << 20];
char B[1 << 20];
int n,m;


vi f(26,0),g(26,0);


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	tc(){
		scanf("%s %s",A,B);
		n = strlen(A);
		m = strlen(B);
		pi ans(0,0);
		map<vi,int> mem;
		for(int len = min(n,m);len > 0;len--) {
			mem.clear();
			fill(all(f),0);
			for(int i = 0;i < len;i++)
				f[A[n-1-i]-'a']++;
			for(int i = n-len;i >= 0;i--) {
				mem[f] = i;
				int j = i+len-1;
				f[A[j]-'a']--;
				if(i) f[A[i-1]-'a']++;
			}
			fill(all(g),0);
			for(int i = 0;i < len;i++)
				g[B[m-1-i]-'a']++;
			int c = n;
			for(int i = m-len;i >= 0;i--) {
				if(mem.count(g)) c = min(c,mem[g]);
				int j = i+len-1;
				g[B[j]-'a']--;
				if(i) g[B[i-1]-'a']++;
			}
//			cerr << "here" << endl;
			if(c != n) {
				ans = mp(c,len);
				break;
			}
		}

		if(ans.second == 0) puts("NONE");
		else {
			for(int i = 0,s = ans.first,len = ans.second;i < len;i++,s++)
				putchar(A[s]);
			puts("");
		}
	}
	return 0;
}
#endif
