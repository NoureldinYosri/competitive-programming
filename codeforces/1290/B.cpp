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
 
const int MAXN = 300*1000 + 10;
char S[MAXN];
int n, m;
vi IDX[128];
int F[MAXN][26];



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%s", S);
	n = strlen(S);
	loop(i, n){
		loop(j, 26) F[i+1][j] = F[i][j];
		F[i+1][S[i]-'a']++;
		IDX[S[i] - 'a'].pb(i+1);
	}
	int f[26];
	scanf("%d",&m);
	while(m--){
		int l, r; scanf("%d %d", &l, &r);
		if(l==r) puts("YES");
		else {
			int cnt = 0;			
			loop(j, 26) {
				f[j] = F[r][j] - F[l-1][j];
				cnt += f[j] > 0;
			}
			if(cnt == 1) puts("NO");
			else if(cnt > 2) puts("YES");
			else {
				puts((S[l-1] != S[r-1]) ? "YES" : "NO");
			}
		}
	}
	return 0;
}
