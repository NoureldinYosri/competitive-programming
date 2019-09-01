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

const int MAX = 1 << 20;
char S[MAX];
int n;

int starting[MAX][2];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%s",S);
	n = strlen(S);

	for(int i = n-1;i >= 0;i--) {
		loop(j,2) starting[i][j] = starting[i+1][j];
		if(S[i] == '0') {
			starting[i][0] = max(starting[i][0],starting[i][1]) + 1;
		}
		else {
			starting[i][1]++;
		}
	}
	int e0 = 0,e1 = 0;
	loop(i,n){
		if(S[i] == '0') {
			e0++;
			continue;
		}
		int len = max(e0,e1) + starting[i][1];
		len = max(len,e0 + starting[i][0]);

		int g = e0 + 1 + max(starting[i+1][1],starting[i+1][0]);
		if(g == len) {
			e0++;
			S[i] = '0';
		}
		else {
			e1 = max(e0,e1)+1;
		}
	}
	puts(S);
	return 0;
}
#endif
