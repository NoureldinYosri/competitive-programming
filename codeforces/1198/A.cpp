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

const int MAX = 400*1000 + 10;
int A[MAX],f[MAX],n,m,L;

void compress(){
	sort(A,A + n);
	m = 0;
	for(int i = 0;i < n;) {
		int j = i;
		while(j < n && A[i] == A[j]) j++;
		A[m] = A[i];
		f[m] = j-i;
		m++;
		i = j;
	}
}


int pref[1 << 20];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&n,&L);
	loop(i,n) scanf("%d",A + i);
	compress();
	int k = min((8*L)/n,20),ans = n;
	int K = 1 << k;
//	cout << "K = " << K << endl;
	loop(i,m) pref[i] = f[i] + (i ? pref[i - 1] : 0);
//	prArr(A,m,int);
//	prArr(f,m,int);
//	prArr(pref,m,int);
	for(int i = 0;i < m;i++) {
		int S = pref[min(m,i + K) - 1] - (i ? pref[i-1] : 0);
//		cout << "[" << A[i] << ", " << A[min(m,i+K)-1] << "]: " << S << endl;
		ans = min(ans,n - S);
	}
	printf("%d\n",ans);
	return 0;
}
#endif
