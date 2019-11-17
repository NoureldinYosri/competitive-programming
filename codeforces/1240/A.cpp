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
ll price[MAX];
int n;
int x,a,y,b;
ll K;
int ctr[4][MAX];

bool can(int m) {
	int ab = ctr[3][m-1];
	int a = ctr[1][m-1];
	int b = ctr[2][m-1];
	ll k = 0;
	int s = 0;
	loop(i,ab) k += price[s++] * (x+y);
	loop(i,a) k += price[s++]*x;
	loop(i,b) k += price[s++]*y;
	return k >= K;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int Q; scanf("%d",&Q);
	while(Q--) {
		scanf("%d",&n);
		loop(i,n) {
			scanf("%lld",price + i);
			assert(price[i]%100 == 0);
			price[i] /= 100;
		}
		sort(price,price + n);
		reverse(price,price + n);
		scanf("%d %d",&x,&a);
		scanf("%d %d",&y,&b);
		scanf("%lld",&K);
		if(x < y) {
			swap(a,b);
			swap(x,y);
		}
		loop(i,n) {
			int h = 0;
			if(i%a == a-1) h |= 1;
			if(i%b == b-1) h |= 2;
			loop(j,4) ctr[j][i] = i ? ctr[j][i-1] : 0;
			ctr[h][i]++;
		}
		if(!can(n)) puts("-1");
		else {
			int s = 1,e = n;
			while(s < e) {
				int m = (s+e) >> 1;
				if(can(m)) e = m;
				else s = m+1;
			}
			printf("%d\n",s);
		}
	}
	return 0;
}
#endif
