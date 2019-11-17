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

const int B = 6;
const int MAX = B*100*1000 + 10;
int A[MAX],n;
int dp[MAX];

int getLow(int x) {
	int low = x/2;
	if(x%2 == 0) low--;
	return low;
}

map<int,int> M;

void insert(int x,int i) {
	while(!M.empty() && M.rbegin()->first >= x) M.erase(M.rbegin()->first);
	M[x] = i;
}

int get(int x) {
	auto ptr = M.upper_bound(x);
	if(ptr == M.begin()) return B*n;
	--ptr;
	return ptr->second;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
//	freopen("out.out","w",stdout);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	loop(i,(B-1)*n) A[i + n] = A[i%n];

	vi ST1,ST2;
	int m = B*n;

	dp[m] = m;

	for(int i = m-1;i >= 0;i--) {
		dp[i] = i+1;
		while(!ST1.empty() && A[i] >= A[ST1.back()]) ST1.pop_back();


		int mxi = (!ST1.empty()) ? ST1.back() : m;
		int mni = get(getLow(A[i]));


		if(mni <= mxi) dp[i] = mni;
		else dp[i] = dp[mxi];

		ST1.push_back(i);
		ST2.push_back(i);
		insert(A[i],i);
	}
//	prArr(A,m,int);
//	prArr(dp,m,int);
	loop(i,n) {
		int c = dp[i] - i;
		if(c >= 2*n) c = -1;
		printf("%d%c",c," \n"[i==n-1]);
	}
	return 0;
}
#endif
