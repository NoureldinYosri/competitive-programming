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

const int MAX = 200*100*1000;
bool is_prime[MAX];


void sieve(){
	fill(is_prime+2,is_prime+MAX,1);
	for(int i = 2;i < MAX;i++)
		if(is_prime[i]) {
			for(ll j = i*(ll)i;j < MAX;j += i)
				is_prime[j] = 0;
		}
}

int read(){
	static char buf[20];
	scanf("%s",buf);
	int a,b = 0;
	sscanf(buf,"%d",&a);
	int L = strlen(buf),h = 100*1000;
	int i = find(buf,buf + L,'.') - buf;
	if(i == L) return a*h;
	string s (buf+i+1);
	while(!s.empty() && !isdigit(s.back())) s.pop_back();
	while(sz(s) < 5) s.push_back('0');
	sscanf(s.c_str(),"%d",&b);
	return a*h + b;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	sieve();
	int n; scanf("%d",&n);
	while(n--) {
		int a = read(),b = read();
//		cout << a << " " << b << endl;
		int g = __gcd(a,b);
		a /= g;
		b /= g;
		if(is_prime[a] && is_prime[b]) printf("%d %d\n",a,b);
		else if(a == 1 && b == 1) puts("2 2");
		else puts("impossible");
	}
	return 0;
}
#endif
