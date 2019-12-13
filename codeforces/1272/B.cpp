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


char S[1 << 20];
int n;

int cnt[4];
string dir = "LRUD";

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%s",S);
		n = strlen(S);
		loop(i,4) cnt[i] = 0;
		loop(i,n){
			int j = find(all(dir),S[i]) - dir.begin();
			cnt[j]++;
		}
		int h = min(cnt[0],cnt[1]);
		int v = min(cnt[2],cnt[3]);
		if(h == 0) v = min(v,1);
		else if(v == 0) h = min(h,1);
		printf("%d\n",2*(h+v));
		loop(i,h) putchar('R');
		loop(i,v) putchar('U');
		loop(i,h) putchar('L');
		loop(i,v) putchar('D');
		puts("");
	}
	return 0;
}
