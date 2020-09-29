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


const int MAXN = 1000*1000 + 10;
int A[MAXN], B[MAXN], n, L;
bool done[MAXN];
vi P;

map<int, list<vi>> cycles;
int f[MAXN];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &L);
	for(int i = 1; i <= n;i++) scanf("%d", B + i);
	for(int i = 1; i <= n;i++) if(!done[i]){
		P.clear();
		for(int j = i; !done[j]; j = B[j]){
			P.push_back(j);
			done[j] = 1;
		}
		cycles[sz(P)].emplace_back(P);
	}
	
	vi divs;
	for(int x = 1; x*x <= L; x++)
		if(L%x == 0){
			divs.pb(x);
			if(x != L/x)
				divs.pb(L/x);
		}
	sort(all(divs));
	
	for(auto & [len, Cs] : cycles) {
		int m = sz(Cs);
		f[0] = 0;
		// len = M/g .. g = gcd(L, M)
		for(int i = 1; i <= m; i++){
			f[i] = -1;
			for(int g : divs) if(g <= i && g <= n/len){
				int M = g*len;
				if(__gcd(M, L) != g) continue;
				if(f[i - g] != -1) {
					f[i] = g;
					break;
				}
			}
		}
		assert(f[m] != -1);
		for(;m; m -= f[m]){
			int g = f[m], M = g*len;
			P.resize(M);
			fill(all(P), -1);
			int i = 0;
			while(g){
				vi & C = Cs.back();
				while(P[i] != -1) i++;
				int j = i;
				for(int x : C){
					P[j] = x;
					j = (j + L)%M;
				}
				g--;
				Cs.pop_back();
			}
//			print(P, int);
			loop(k, M) A[P[k]] = P[(k+1)%M];
		}
	}
	
	for(int i = 1;i <= n;i++) printf("%d\n", A[i]);
	return 0;
}
