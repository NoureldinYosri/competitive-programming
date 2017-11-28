#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

//int n;
//int A[1 << 10];
//int g;
//
//bool valid(){
//	g = A[0];
//	loop(i,n)
//		if(A[i]%g)
//			return 0;
//	return 1;
//}
//
//int main(){
//	#ifdef HOME
//		freopen("in.in", "r", stdin);
//	#endif
//	scanf("%d",&n);
//	loop(i,n) scanf("%d",A + i);
//	if(!valid()) return puts("-1"),0;
//	printf("%d\n",2*n);
//	loop(i,n) printf("%d %d ",A[i],g);
//	return 0;
//}

int getK(int msk,int n,int m) {
	vi row(n,1),col(m,1);
	loop(i,n*m) {
		int x = i/m,y = i%m;
		if(msk & (1 << i))
			row[x] *= -1,col[y] *= -1;
	}
	int k = row[0];
	for(int x : row) if(x != k) return 0;
	for(int x : col) if(x != k) return 0;
	return k;
}

void get(int n,int m,int & one,int & mone) {
	one = mone = 0;
	int N = n*m;
	loop(msk,1 << N) {
		int k = getK(msk,n,m);
		one += k == 1;
		mone += k == -1;
	}
}

void sim(){
	for(int n = 1;n <= 20;n++){
		for(int m = 1;n*m <= 20;m++){
			int one,mone;
			get(n,m,one,mone);
			prp(mp(one,mone));
		}
		cerr << endl;
	}
}

int mod = 1000000007;
int powmod(int x,ll p) {
	if(!p) return 1;
	x %= mod;
	int y = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) y = (x*1LL*y)%mod;
		x = (x*1LL*x)%mod;
	}
	return (x*1LL*y)%mod;
}


int main(){
	ll n,m;
	int k;
	cin >> n >> m >> k;
	if(k == 1) cout << powmod(powmod(2,m-1),n-1) << endl;
	else {
		int res = 0;
		ll N = n + m;
		if(N&1) res = 0;
		else res = powmod(powmod(2,m-1),n-1);
		cout << res << endl;
	}
	//(2^(m-1))^(n-1)
//	sim();
}
