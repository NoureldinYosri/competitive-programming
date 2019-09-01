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

const int MAX = 4 << 20;
int p,p2;
int n;
int A[50];

int add(int a,int b,int m) {
	a += b;
	if(a >= m) a -= m;
	return a;
}
int mul(int a,int b,int m) {
	return (a*(ll)b)%m;
}

int f(int x) {
	x %= p2;
	int r = 0;
	loop(i,n) r = add(mul(r,x,p2),A[i],p2);
	return r;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> p >> n;
	p2 = p*p;
	n++;
	loop(i,n) {
		cin >> A[i];
		A[i] = (A[i]%p2 + p2)%p2;
	}
	for(int x = 0;x < MAX;x++)
		if(f(x) == 0) {
			cout << x << endl;
			return 0;
		}
	cout << -1 << endl;
	return 0;
}

#endif
