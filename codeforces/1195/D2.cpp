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

const int MAX = 100*1000 + 10,mod = 998244353;
int A[MAX],n;

int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b) {
	return (a*(ll)b)%mod;
}

int B[20];

int conv(int x) {
	if(!x) {
		B[0] = 0;
		return 1;
	}
	int m = 0;
	while(x) {
		B[m] = x%10;
		x /= 10;
		m++;
	}
	return m;
}

int freq[20];


int solve(){
	memset(freq,0,sizeof freq);
	int mx = 0;
	loop(i,n){
		int len = conv(A[i]);
		freq[len]++;
		mx = max(mx,len);
	}
	int ans = 0;
	loop(i,n) {
		int m = conv(A[i]);
		int contrib = 0;
		for(int len = 1;len <= mx;len++) {
			int p10 = 1,f = 0,g = 0;
			for(int j = 0;j < m;j++){
				int d = B[j];
				f = add(f,mul(d,p10));
				p10 = mul(p10,10);
				if(j < len) p10 = mul(p10,10);
			}

			p10 = 10;
			for(int j = 0;j < m;j++){
				int d = B[j];
				g = add(g,mul(d,p10));
				p10 = mul(p10,10);
				if(j+1 < len) p10 = mul(p10,10);
			}

			f = mul(f,freq[len]);
			g = mul(g,freq[len]);
			contrib = add(contrib,add(f,g));
		}
		ans = add(ans,contrib);
	}
	return ans;
}

ll merge(int x,int y) {
	char A[20],B[20];
	sprintf(A,"%d",x);
	sprintf(B,"%d",y);
	reverse(A,A + strlen(A));
	reverse(B,B + strlen(B));
	int a = strlen(A),b = strlen(B);
	char C[50];
	int m = 0;
	for(int i = 0,j = 0;i < a || j < b;) {
		if(j < b) C[m++] = B[j++];
		if(i < a) C[m++] = A[i++];
	}
	C[m] = 0;
	reverse(C,C + m);
	ll ret;
	sscanf(C,"%lld",&ret);
	return ret;
}

int bf(){
	int res = 0;
	loop(i,n) loop(j,n) {
		ll v = merge(A[i],A[j]);
//		cerr << A[i] << " " << A[j] << " -> " << v << endl;
		res = (res + v)%mod;
	}
	return res;
}

void test(){
	for(int t = 0;t < 100;t++) {
		n = rand()%1000 + 1;
		loop(i,n) A[i] = rand()%1000000000 + 1;
		int correct = bf();
		int ans = solve();
		if(correct != ans) {
			cerr << "failed on " << endl;
			cerr << n << endl;
			prArr(A,n,int);
			exit(0);
		}
	}
	cout << "AC :)" << endl;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	cout << solve() << endl;
	cout << bf() << endl;
	test();
	return 0;
}
#endif
