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

const int MAX = 1 << 20;
int BIT[MAX], n, q;

void add(int p, int v){
	for(; p < MAX; p += LSOne(p))
		BIT[p-1] += v;
	
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &q);
	loop(i, n){
		int x; scanf("%d", &x);
		add(x, 1);
	}
	loop(i, q){
		int k; scanf("%d", &k);
		if(k >= 1) add(k, 1), n++;
		else{
			n--;
			k = -k;
			int s = 0;
			int m = 1 << 19;
			while (m) {
				if (BIT[s + m - 1] < k)
				k -= BIT[(s += m) - 1];
				m >>= 1;
			}
			s++;
//			cerr << "erase " << s << endl;
			add(s, -1);
		}
	}
	if(n) {
		for(int i = 1; i < MAX; i++)
			if(BIT[i-1]){
				printf("%d\n", i);
				return 0;
			}
	}
	else puts("0");
	return 0;
}
