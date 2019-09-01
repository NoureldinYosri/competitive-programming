#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (int)(n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAXN = 2e5 + 1e2,MAXA = 1 << 20;

unsigned L[MAXN],R[MAXN],order[MAXN];
unsigned A[MAXN],CTR[MAXA];
unsigned ll ans[MAXN],H[MAXN];
int n,m;

inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%u",A + i + 1);
	loop(i,m) {
		scanf("%u %u",L + i,R + i);
		order[i] = i;
		H[i] = hilbertOrder(L[i],R[i],20,0);
	}
	sort(order,order + m,[](const int & a,const int & b){
		return H[a] < H[b];
	});
	int l = 0,r = -1;
	unsigned ll tmp = 0;
	for(int j = 0;j < m;j++){
		int i = order[j];
		for(int k = R[i];r < k;r++) tmp += (2*CTR[A[r + 1]] + 1LL)*A[r + 1],CTR[A[r + 1]]++;
		for(int k = L[i];l > k;l--) tmp += (2*CTR[A[l - 1]] + 1LL)*A[l - 1],CTR[A[l - 1]]++;
		for(int k = L[i];l < k;l++) {
			tmp -= (2*CTR[A[l]] - 1LL)*A[l],CTR[A[l]]--;
		}
		for(int k = R[i];r > k;r--) {
			tmp -= (2*CTR[A[r]] - 1LL)*A[r],CTR[A[r]]--;
		}
		ans[i] = tmp;
	}
	loop(i,m) printf("%llu\n",ans[i]);
	return 0;
}
